# Project network parameters

`CMainParams` now commits to the project's deterministic genesis block and
does not bootstrap from any Bitcoin checkpoint, DNS seed, fixed seed, or UTXO
snapshot.

The following values must be selected together before a public network launch:

- P2P message-start bytes and default P2P/RPC/Tor ports;
- Base58, extended-key, and Bech32/Bech32m address prefixes;
- DNS and fixed seed operators;
- activation policy for inherited Bitcoin script features and deployments;
- RandomX genesis/bootstrap behavior, including a valid genesis PoW proof and
  the key schedule for the first non-genesis block.

Until these choices are made, the inherited message-start, port, and address
prefix values remain intentionally unchanged for source compatibility only.
They are not a public-network configuration and must not be used for launch.
