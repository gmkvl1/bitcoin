# RandomX implementation status

## Implemented in this stage

- Pinned RandomX v2.0.1 dependency metadata.
- RandomX C API integration wrapper.
- Per-thread cache/VM reuse keyed by the consensus RandomX key.
- Canonical Bitcoin block-header serialization is passed as the RandomX input.
- Block identifier remains separate from the PoW digest during this incremental migration.
- RandomX PoW verification derives the target from `nBits` and refuses to verify without the required previous-block context.
- The deterministic key schedule is currently 2048 blocks per epoch with a 64-block activation delay: heights 1-2111 use genesis, heights 2112-4159 use the block at height 2048, and so on.

## Consensus integration status

The RandomX verifier is implemented, but the consensus call sites have deliberately not yet been switched. Bitcoin Core currently performs some header PoW checks before the previous-block context required by the RandomX key schedule is available. Switching those call sites requires a coordinated change to contextual header validation, block validation/reindex paths, header synchronization/anti-DoS validation, and mining/RPC block generation. Leaving any of those paths on SHA-256d would create inconsistent validation rules.

## Required next source changes

1. Move the consensus PoW decision to a context-aware validation path and ensure headers, full blocks, and reindex validation all use the same RandomX digest/key.
2. Remove the remaining consensus-critical SHA-256d PoW checks once the context-aware path is complete.
3. Wire the same key and digest into mining/template generation and `generate*` RPC mining.
4. Add consensus known-answer tests and a cross-platform verification test.
5. Validate the 2048/64 key schedule at boundary heights and only then treat RandomX as the active chain PoW rule.
