# Gas Oracle Bridge

This repository contains the Gas Oracle Bridge between Telos EVM and Telos Antelope. 

A listener script queries the gas price stored on the `eosio.evm` Antelope contract and the gas price stored inside the `GasOracleBridge.sol` EVM contract. 

If they do not match it then calls the `verify()` action of the `gas.bridge.cpp` contract which itself retreives the price from `eosio.evm` and `GasOracleBridge.sol`, compares them and if needed uses an `eosio.evm` contract action to call the `setPrice()` function of the `GasOracleBridge.sol` EVM contract

This repository is separated in 3 modules that each have to be setup for the bridge to work: evm, antelope & listeners

## Requirements

This repository uses NodeJS, NPM, cleos and various dependencies

## EVM

## Antelope

## Listeners
