# Project consensus specification

This repository is a Bitcoin Core fork. The rule is: Bitcoin behavior is retained unless an explicit change is listed here.

## Explicit protocol changes

- Proof of Work: RandomX instead of SHA-256d.
- Target block interval: 10 minutes.
- Difficulty adjustment: Bitcoin's 2016-block retarget and target calculation.
- Issuance: Bitcoin schedule, subsidy and halvings unchanged.
- Maximum serialized block size: 1,000,000 bytes.
- General OP_RETURN payload: maximum 40 bytes.
- Drivechain support: BTC-denominated settlement layers may use the L1 without a separate native token or competing mining economy. The L1 validates only the minimum monetary/peg interface required by the Drivechain mechanism; its internal application logic is not part of L1 consensus.
- Transaction neutrality: no consensus classification by application or user; valid transactions compete for blockspace under the normal fee market.

## L1 principle

The L1 is money and settlement. Complexity, application logic, privacy systems, games, markets, VMs and other functionality belong above the L1 where possible.

## PoW implementation note

RandomX integration must use a pinned upstream RandomX implementation and deterministic consensus parameters. The exact key schedule must be implemented and tested before mainnet; it must not be left as an undocumented implementation choice.

Do not import Monero's difficulty algorithm, emission schedule, transaction model or block structure merely because RandomX is used.
