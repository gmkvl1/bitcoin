# RandomX consensus validation

RandomX replaces SHA-256d only for proof-of-work. `CBlockHeader::GetHash()` remains the SHA-256d block identifier.

PoW is checked in `ContextualCheckBlockHeader()` because the RandomX key schedule requires the previous chain state and block height. The target calculation remains Bitcoin's 2016-block, 10-minute difficulty schedule.

Header batches whose first header does not connect to a known block index cannot resolve the RandomX key schedule yet; those headers are deferred to contextual validation rather than being incorrectly validated with SHA-256d.
