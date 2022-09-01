const ecc = require("eosjs-ecc");
const HyperionStreamClient = require("@eosrio/hyperion-stream-client").default;
const fetch = require("node-fetch");
const ethers = require("ethers");

const CONFIG_TABLE = "config";

class GasListener {
    constructor(
        contract,
        oracleName,
        oraclePermission,
        rpc,
        api,
    ) {
        this.contract = contract;
        this.oracleName = oracleName;
        this.oraclePermission = oraclePermission;
        this.rpc = rpc;
        this.api = api;
    }

    async start() {
        setInterval(function () {
            await this.doCheck();
        }, 1000)
    }



    async doCheck() {
        console.log(`Doing table check...`);
        const antelope_config = await this.rpc.get_table_rows({
            code: this.contract,
            scope: this.contract,
            table: CONFIG_TABLE,
            limit: 1,
        });

        const antelope_gas_price = antelope_config.gas_price;

        // TODO: Get EVM gas price from EVM bridge using ethers
        const evm_gas_price = 0;

        // TODO: Format values properly
        if(antelope_gas_price !== evm_gas_price){
            // TODO: Call antelope bridge verify() action
        }
        console.log(`Done doing table check!`);
    }

}

module.exports = RequestOracle;
