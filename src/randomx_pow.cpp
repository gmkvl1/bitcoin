// Copyright (c) 2026 The Bitcoin-RandomX project contributors
// Distributed under the MIT software license.

#include <randomx_pow.h>

#include <primitives/block.h>
#include <serialize.h>

#include <randomx.h>

#include <array>
#include <cstring>
#include <stdexcept>

namespace {

class RandomXContext
{
public:
    RandomXContext() = default;
    RandomXContext(const RandomXContext&) = delete;
    RandomXContext& operator=(const RandomXContext&) = delete;

    ~RandomXContext()
    {
        Reset();
    }

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

        // Consensus verification uses RandomX light mode. Mining can use a
        // full-memory/JIT context without changing the resulting digest.
        const randomx_flags flags = RANDOMX_FLAG_DEFAULT;
        m_cache = randomx_alloc_cache(flags);
        if (!m_cache) {
            throw std::runtime_error("RandomX cache allocation failed");
        }

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
