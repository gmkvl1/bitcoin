// Copyright (c) 2026 The Bitcoin-RandomX project contributors
// Distributed under the MIT software license.

#ifndef BITCOIN_RANDOMX_POW_H
#define BITCOIN_RANDOMX_POW_H

#include <uint256.h>

class CBlockHeader;
class CBlockIndex;

/**
 * Return the RandomX key block for a block at block_height.
 *
 * The key changes every 2048 blocks with a 64-block delay. Therefore blocks
 * [0, 2111] use the genesis block as their key block, blocks [2112, 4159]
 * use height 2048, and so on.
 */
const CBlockIndex* GetRandomXKeyBlock(const CBlockIndex* pindexPrev, int block_height);

/** Return the 32-byte RandomX key derived from the key block hash. */
uint256 GetRandomXPoWKey(const CBlockIndex* pindexPrev, int block_height);

/**
 * Calculate the RandomX proof-of-work digest for a serialized Bitcoin block
 * header using the consensus-selected key.
 */
uint256 GetRandomXPoWHash(const CBlockHeader& header, const uint256& key);

#endif // BITCOIN_RANDOMX_POW_H
