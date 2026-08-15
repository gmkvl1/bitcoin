# Project implementation notes

The `randomx-pow` work is being implemented incrementally from Bitcoin Core. Consensus-affecting changes must be kept separately reviewable. The first source step integrates the pinned RandomX dependency and exposes a deterministic PoW primitive without changing Bitcoin block IDs until all consensus call sites are switched together.
