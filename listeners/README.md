# Gas Oracle Bridge - Listeners

This script checks and compares the gas price on `eosio.evm` and `GasOracleBridge.sol` contracts, if they do not match it calls `gas.bridge.ccp` contract `verify()` action.

## Configuration

Copy the sample `.env.sample` file into a proper `.env` file

`cp .env.sample .env`

Fill the values in the file as needed

## Usage

Use it directly with node using

`node index.js`

Or run it using pm2
