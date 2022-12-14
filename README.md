# Gas Oracle Bridge

This repository contains the Gas Oracle Bridge between Telos EVM and Telos Antelope. 

This repository is separated in 3 modules that each have to be setup for the bridge to work: evm, antelope & listeners

## Rundown

A listener script, ideally ran by several actors, queries the gas price stored on the `eosio.evm` Antelope contract and the gas price stored inside the `GasOracleBridge.sol` EVM contract periodically. 

If they do not match it then calls the `verify()` action of the `gas.bridge.cpp` contract which itself retreives the price from `eosio.evm` and `GasOracleBridge.sol`, compares them and if needed uses an `eosio.evm` contract action to call the `setPrice(uint)` function of the `GasOracleBridge.sol` EVM contract with the gas price from `eosio.evm` as argument.

EVM contracts and users can then query the `gasPrice()` or `getPrice()` functions of the `GasOracleBridge.sol` contract on EVM to get the current gas price of Telos EVM.

## Requirements

This repository requires NodeJS, NPM and cleos

## EVM

This folder contains the `GasOracleBridge.sol` EVM contract for the bridge. It uses hardhat and hardhat-deploy.

For more, refer to the `README.md` inside the [`evm`](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/evm) folder

## Antelope

This folder contains the `gas.bridge.cpp` Antelope contract for the bridge with bash scripts to easily build & deploy 

For more, refer to the `README.md` inside the [`antelope`](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/antelope) folder

## Listeners

This folder contains the `GasListener` which checks gas prices between `eosio.evm` and `GasOracleBridge.sol` and calls the `gas.bridge.cpp` contract  `verify()` action if needed

For more, refer to the `README.md` inside the [`listeners`](https://github.com/telosnetwork/gas-oracle-bridge/tree/master/listeners) folder

## Using it

Follow the documentation available in Telos docs [here]() to learn how to query pair prices using our Gas Oracle Bridge.
