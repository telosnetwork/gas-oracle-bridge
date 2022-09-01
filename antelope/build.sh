#! /bin/bash
echo ">>> Building contract..."
eosio-cpp -I="./include/"  -I="./external/"  -o="./build/gas.bridge.wasm" -contract="gasbridge" -abigen ./src/gas.bridge.cpp