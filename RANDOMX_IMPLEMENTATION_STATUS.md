# RandomX implementation status

## Implemented in this stage

- Pinned RandomX v2.0.1 dependency metadata.
- RandomX C API integration wrapper.
- Per-thread cache/VM reuse keyed by the consensus RandomX key.
- Canonical Bitcoin block-header serialization is passed as the RandomX input.
- Block identifier remains separate from the PoW digest during this incremental migration.

## Not yet switched into consensus

The existing Bitcoin Core PoW call sites still use the Bitcoin header hash. They must be switched together with the consensus key-selection mechanism, mining path, and test vectors. This is intentional: a partial consensus switch would create a node that can compile while disagreeing with the intended network rules.

## Required next source changes

1. Wire `GetRandomXPoWHash()` into header/block PoW validation.
2. Implement the final deterministic 2048-block / 64-block-delayed key schedule with chain context.
3. Wire the same key and digest into mining/template generation.
4. Add consensus known-answer tests and a cross-platform verification test.
5. Only then activate RandomX as the chain's PoW rule.
