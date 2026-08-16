# Project network parameters

`CMainParams` commits to the project's deterministic genesis block and does
not bootstrap from any Bitcoin checkpoint, DNS seed, fixed seed, or UTXO
snapshot. The selected mainnet identifiers are message-start `d30aa3da`, P2P
port `36660`, Tor inbound port `36661`, RPC port `36662`, and Bech32 HRP `w6`.

The following values must be selected together before a public network launch:

- DNS and fixed seed operators;
- RandomX genesis/bootstrap behavior, including a valid genesis PoW proof and
  the key schedule for the first non-genesis block.

The selected message-start value was generated with a cryptographic random
source and recorded here before publication. The mainnet applies the modern
Bitcoin script rules from genesis; only the deployment test dummy remains
disabled.
