# Gas Oracle Bridge - EVM

This is the `GasOracleBridge.sol` EVM contract for the bridge. It uses hardhat and hardhat-deploy.

It has a public `gasPrice` variable as well as a `getPrice()` view function

It has a restricted `setPrice(uint)` functional only callable by the Antelope contract EVM address.

## Test

You can test the contract using

`npx hardhat test`

## Deploy

You can test the deploy the contract using

`npx hardhat deploy --network testnet`

## Verify

You can verify the deploy the contract using

`npx hardhat sourcify --network testnet`

## Configure

You then need to call the `setOracleEvmAddress()` function to configure the evm address of the antelope contract that is part of the bridge (see [antelope](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/antelope) folder)

You can interact with the deployed contract using

`npx hardhat console --network testnet`

Then get an instance of the bridge using

```
let Bridge = await ethers.getContractFactory("GasOracleBridge")
let bridge = await Bridge.attach("THE_BRIDGE_ADDRESS");
```

And configure the Antelope contract's EVM address with

`await bridge.setOracleEvmAddress("THE_ANTELOPE_CONTRACT_EVM_ADDRESS")`
