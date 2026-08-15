// Copyright (c) 2026 The Bitcoin-RandomX project contributors
// Distributed under the MIT software license.

#include <randomx_pow.h>

#include <chain.h>
#include <primitives/block.h>
#include <serialize.h>

#include <randomx.h>

#include <array>
#include <cstring>
#include <stdexcept>

namespace {

/**
 * Consensus key schedule.
 *
 * A new key epoch starts 64 blocks after the 2048-block boundary. The key is
 * the hash of the boundary block, so miners cannot know the next epoch key
 * until that boundary block exists. The first epoch uses genesis.
 */
constexpr int RANDOMX_EPOCH_LENGTH{2048};
constexpr int RANDOMX_KEY_DELAY{64};

class RandomXContext
{
public:
    RandomXContext() = default;
    RandomXContext(const RandomXContext&) = delete;
    RandomXContext& operator=(const RandomXContext&) = delete;

    ~RandomXContext() { Reset(); }

    void Reset()
    {
        if (m_vm) {
            randomx_destroy_vm(m_vm);
            m_vm = nullptr;
        }
        if (m_cache) {
            randomx_release_cache(m_cache);
            m_cache = nullptr;
        }
        m_key.fill(0);
        m_initialized = false;
    }

    randomx_vm* GetVM(const uint256& key)
    {
        if (m_initialized && std::memcmp(m_key.data(), key.begin(), m_key.size()) == 0) {
            return m_vm;
        }

        Reset();

        // Consensus verification deliberately uses the portable/default
        // RandomX mode. Mining may use a full-memory/JIT VM; the digest is
        // identical for a given key and input.
        const randomx_flags flags = RANDOMX_FLAG_DEFAULT;
        m_cache = randomx_alloc_cache(flags);
        if (!m_cache) throw std::runtime_error("RandomX cache allocation failed");

        randomx_init_cache(m_cache, key.begin(), key.size());
        m_vm = randomx_create_vm(flags, m_cache, nullptr);
        if (!m_vm) {
            Reset();
            throw std::runtime_error("RandomX VM allocation failed");
        }

        std::memcpy(m_key.data(), key.begin(), key.size());
        m_initialized = true;
        return m_vm;
    }

private:
    randomx_cache* m_cache{nullptr};
    randomx_vm* m_vm{nullptr};
    std::array<unsigned char, 32> m_key{};
    bool m_initialized{false};
};

thread_local RandomXContext g_randomx_context;

} // namespace

const CBlockIndex* GetRandomXKeyBlock(const CBlockIndex* pindexPrev, int block_height)
{
    if (!pindexPrev || block_height <= 0) return nullptr;

    // Heights 1..2111 use genesis. At 2112 the key changes to block 2048.
    // More generally, the key for height h is the most recent 2048-boundary
    // block whose age is at least 64 blocks.
    const int key_height = ((block_height - RANDOMX_KEY_DELAY) / RANDOMX_EPOCH_LENGTH) * RANDOMX_EPOCH_LENGTH;

    if (key_height <= 0) return pindexPrev->GetAncestor(0);
    if (pindexPrev->nHeight < key_height) return nullptr;
    return pindexPrev->GetAncestor(key_height);
}

uint256 GetRandomXPoWKey(const CBlockIndex* pindexPrev, int block_height)
{
    const CBlockIndex* key_block = GetRandomXKeyBlock(pindexPrev, block_height);
    if (!key_block) throw std::runtime_error("RandomX key block is unavailable");
    return key_block->GetBlockHash();
}

uint256 GetRandomXPoWHash(const CBlockHeader& header, const uint256& key)
{
    DataStream stream;
    stream << header;

    uint256 result;
    randomx_calculate_hash(
        g_randomx_context.GetVM(key),
        stream.data(),
        stream.size(),
        result.begin());
    return result;
}
