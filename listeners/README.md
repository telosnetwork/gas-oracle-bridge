# GasOracleBridge - Listeners

This script checks and compares the gas price on `eosio.evm` and `GasOracleBridge.sol` contracts, if they do not match it calls `gas.bridge.ccp` contract `verify()` action.

Use it directly with node using

`node index.js`

Or run it using pm2