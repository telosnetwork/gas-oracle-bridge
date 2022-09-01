# GasOracleBridge - Antelope

This is the gas.bridge.ccp contract for the Gas Oracle Bridge.

## Build

You can build the contract using

`bash build.sh`

## Deploy

First you must create the build directory, you can do so using

`mkdir build`

You can then deploy the contract using cleos 

`cleos --url http://testnet.telos.caleos.io set contract YOUR_ACCOUNT_NAME /full/path/to/folder/antelope build/gas.bridge.wasm`

## Configure

You then need to configure the EVM address of the EVM contract that is part of the bridge (see the [evm](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/evm) folder)

Use cleos to do so with

`cleos --url http://testnet.telos.caleos.io push action YOUR_ACCOUNT_NAME init '{"evm_contract": "THE_EVM_CONTRACT_ADDRESS_NO_0X", "version": "1"}'`

Please note that the address musn't have `0x` in it