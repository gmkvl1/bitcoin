// Copyright (c) 2026 The Bitcoin-RandomX project contributors
// Distributed under the MIT software license.

#ifndef BITCOIN_RANDOMX_POW_H
#define BITCOIN_RANDOMX_POW_H

#include <uint256.h>

#include <span>

class CBlockHeader;

/**
 * Calculate the RandomX proof-of-work digest for a serialized Bitcoin block
 * header using the consensus-selected key.
 *
 * The block identifier remains separate from the PoW digest. This lets the
 * consensus migration replace SHA-256d PoW without accidentally changing all
 * block-hash semantics at the same time.
 */
uint256 GetRandomXPoWHash(const CBlockHeader& header, const uint256& key);

#endif // BITCOIN_RANDOMX_POW_H
