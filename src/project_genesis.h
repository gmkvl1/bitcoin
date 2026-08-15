// Copyright (c) 2026 The Bitcoin-RandomX project contributors
// Distributed under the MIT software license.

#ifndef BITCOIN_PROJECT_GENESIS_H
#define BITCOIN_PROJECT_GENESIS_H

#include <cstdint>

namespace project_genesis {

// The project is a new monetary network. Its genesis is deliberately not the
// Bitcoin genesis block. These constants define the deterministic genesis
// candidate used by the chain-parameter implementation.
inline constexpr uint32_t TIME = 1786752000; // 2026-08-15 00:00:00 UTC
inline constexpr uint32_t NONCE = 0;
inline constexpr uint32_t NBITS = 0x1d00ffff;
inline constexpr int32_t VERSION = 1;
inline constexpr int64_t REWARD_SATS = 5'000'000'000;

inline constexpr char TIMESTAMP[] = "Bitcoin settlement layer - 2026";

// SHA256d(block header) of the deterministic genesis candidate.
inline constexpr char HASH[] = "70ae2891fbd8b0993b038a04a05c8c9170174d160f3683285f4113a890ee8177";

// SHA256d(genesis transaction), displayed in uint256 conventional order.
inline constexpr char MERKLE_ROOT[] = "390c578a69c1b10e109fc60907042ca23148f4d603e1390222d6a6affc4eca12";

} // namespace project_genesis

#endif // BITCOIN_PROJECT_GENESIS_H
