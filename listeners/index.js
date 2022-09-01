require('dotenv').config()
const GasListener = require('./src/GasListener')
const eosjs = require('eosjs')
const JsSignatureProvider = require('eosjs/dist/eosjs-jssig').JsSignatureProvider
const JsonRpc = eosjs.JsonRpc
const Api = eosjs.Api
const fetch = require('node-fetch')
const util = require('util')
const ethers = require("ethers");
const  { TelosEvmApi } = require("@telosnetwork/telosevm-js");

const signatureProvider = new JsSignatureProvider([process.env.ORACLE_KEY]);
const rpc = new JsonRpc(process.env.RPC_ENDPOINT, { fetch })
const contract = "eosio.evm";

const evm_api = new TelosEvmApi({
    endpoint: process.env.EVM_API_ENDPOINT,
    chainId: process.env.CHAIN_ID,
    ethPrivateKeys: [],
    fetch: fetch,
    telosContract: contract,
    telosPrivateKeys: []
});
const evm_provider = new ethers.providers.JsonRpcProvider(process.env.EVM_RPC_ENDPOINT);

const api = new Api({
    rpc,
    signatureProvider,
    textDecoder: new util.TextDecoder(),
    textEncoder: new util.TextEncoder()
});

const gasListener = new GasListener(contract, process.env.EVM_BRIDGE_CONTRACT, process.env.ORACLE_NAME, process.env.ORACLE_PERMISSION, rpc, api, evm_provider, evm_api)
gasListener.start();