# Gas Oracle Bridge

This repository contains the Gas Oracle Bridge between Telos EVM and Telos Antelope. 

A listener script queries the gas price stored on the `eosio.evm` Antelope contract and the gas price stored inside the `GasOracleBridge.sol` EVM contract. 

If they do not match it then calls the `verify()` action of the `gas.bridge.cpp` contract which itself retreives the price from `eosio.evm` and `GasOracleBridge.sol`, compares them and if needed uses an `eosio.evm` contract action to call the `setPrice()` function of the `GasOracleBridge.sol` EVM contract

This repository is separated in 3 modules that each have to be setup for the bridge to work: evm, antelope & listeners

## Requirements

This repository requires NodeJS, NPM and cleos

## EVM

This folder contains the `GasOracleBridge.sol` EVM contract for the bridge. It uses hardhat and hardhat-deploy.

For more, refer to the `README.md` inside the `evm` folder

## Antelope

This folder contains the `gas.bridge.cpp` Antelope contract for the bridge with bash scripts to easily build & deploy 

For more, refer to the `README.md` inside the `antelope` folder

## Listeners

This folder contains the GasListener which checks gas prices between `eosio.evm` and `GasOracleBridge.sol` and calls the `gas.bridge.cpp` contract  `verify()` action if needed

For more, refer to the `README.md` inside the `listeners` folder
