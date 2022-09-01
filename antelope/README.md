# GasOracleBridge - Antelope

This is the gas.bridge.ccp contract for the Gas Oracle Bridge.

## Build

First you must create the build directory, you can do so using

`mkdir build`

You can then build the contract using

`bash build.sh`

## Deploy

Next, you can deploy the contract using cleos 

`cleos --url http://testnet.telos.caleos.io set contract YOUR_ACCOUNT_NAME /full/path/to/folder/antelope build/gas.bridge.wasm`

## Add the code permission

You then have to add the code permission to your contract account using cleos

`cleos -u https://testnet.telos.net set account permission YOUR_ACCOUNT_NAME active --add-code`

## Configure

You then need to configure the EVM address of the EVM contract that is part of the bridge (see the [evm](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/evm) folder)

Use cleos to do so with

`cleos --url http://testnet.telos.caleos.io push action YOUR_ACCOUNT_NAME init '{"evm_contract": "THE_EVM_CONTRACT_ADDRESS_NO_0X", "version": "1"}'`

Please note that the address musn't have `0x` in it

## Create its linked EVM address

Finally you can create is linked EVM address using

`cleos --url http://testnet.telos.caleos.io push action eosio.evm create '{"account": "YOUR_ACCOUNT_NAME", "data": ""}' -p YOUR_ACCOUNT_NAME@active`

Don't forget to save it ! You will need it to configure the EVM contract (If you do, search for YOUR_ACCOUNT_NAME on [teloscan](https://testnet.teloscan.io/))
