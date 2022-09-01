require('dotenv').config()
const GasListener = require('./src/GasListener')
const eosjs = require('eosjs')
const JsSignatureProvider = require('eosjs/dist/eosjs-jssig').JsSignatureProvider
const JsonRpc = eosjs.JsonRpc
const Api = eosjs.Api
const fetch = require('node-fetch')
const util = require('util')

const signatureProvider = new JsSignatureProvider([process.env.ORACLE_KEY]);
const rpc = new JsonRpc(process.env.RPC_ENDPOINT, { fetch })

const api = new Api({
    rpc,
    signatureProvider,
    textDecoder: new util.TextDecoder(),
    textEncoder: new util.TextEncoder()
});

const gasListener = new GasListener("eosio.evm", process.env.ORACLE_NAME, process.env.ORACLE_PERMISSION, rpc, api)
gasListener.start();