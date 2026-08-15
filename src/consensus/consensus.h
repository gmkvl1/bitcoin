// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-present The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <cstddef>
#include <cstdint>

/** The maximum allowed serialized block size, including witness data. */
inline constexpr unsigned int MAX_BLOCK_SERIALIZED_SIZE{1'000'000};
/**
 * Block weight remains an internal compatibility/validation metric. Since the
 * serialized block limit above is the consensus size ceiling, it cannot permit
 * a block larger than 1,000,000 serialized bytes.
 */
inline constexpr unsigned int MAX_BLOCK_WEIGHT{4'000'000};
/** The maximum allowed number of signature check operations in a block (network rule) */
inline constexpr int64_t MAX_BLOCK_SIGOPS_COST{80'000};
/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
inline constexpr int COINBASE_MATURITY = 100;

inline constexpr int WITNESS_SCALE_FACTOR = 4;

inline constexpr size_t MIN_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 60; // 60 is the lower bound for the size of a valid serialized CTransaction
inline constexpr size_t MIN_SERIALIZABLE_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 10; // 10 is the lower bound for the size of a valid serializable CTransaction

/** Flags for nSequence and nLockTime locks */
/** Interpret sequence numbers as relative lock-time constraints. */
inline constexpr unsigned int LOCKTIME_VERIFY_SEQUENCE = (1 << 0);

/**
 * Maximum number of seconds that the timestamp of the first
 * block of a difficulty adjustment period is allowed to
 * be earlier than the last block of the previous period (BIP94).
 */
inline constexpr int64_t MAX_TIMEWARP = 600;

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
