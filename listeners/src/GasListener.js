const ecc = require("eosjs-ecc");
const HyperionStreamClient = require("@eosrio/hyperion-stream-client").default;
const fetch = require("node-fetch");
const {BigNumber, ethers } = require("ethers");
const ABI = [{ "inputs": [], "name": "gasPrice", "outputs": [{ "internalType": "uint256",  "name": "", "type": "uint256"}],  "stateMutability": "view", "type": "function"}]

const CONFIG_TABLE = "config";

class GasListener {
    constructor(
        contract_account,
        evm_contract_address,
        oracleName,
        oraclePermission,
        rpc,
        api,
        evm_provider,
        evm_api,
        interval
    ) {
        this.contract_account = contract_account;
        this.oracleName = oracleName;
        this.oraclePermission = oraclePermission;
        this.evm_contract_address = evm_contract_address;
        this.rpc = rpc;
        this.api = api;
        this.evm_api = evm_api;
        this.evm_provider = evm_provider;
        this.interval = interval;
    }

    async start() {
        let ctx = this;
        setInterval(async function () {
            await ctx.doCheck();
        }, this.interval)
    }

    async doCheck() {
        let gas_price, evm_contract_gas_price = 0;
        try {
            gas_price = BigNumber.from(`0x${await this.evm_api.telos.getGasPrice()}`)
        } catch (e) {
            console.log(e);
            return false;
        }
        // TODO: Get EVM gas price from EVM bridge using ethers
        try {
            const evm_contract = new ethers.Contract(this.evm_contract_address, ABI, this.evm_provider);
            evm_contract_gas_price = await evm_contract.gasPrice();
        } catch (e) {
            console.log(e);
            return false;
        }
        console.log(gas_price, evm_contract_gas_price);
        if(gas_price !== evm_contract_gas_price){
            console.log(`Updating price...`);
            this.api.transact({
                actions: [{
                    account: "gasbridge",
                    name: 'verify',
                    authorization: [{ actor: this.oracleName, permission: this.oraclePermission }],
                    data: {},
                }]
            }, {
                blocksBehind: 3,
                expireSeconds: 30,
            }).then(result => {
                console.log('\nCalled verify()');
            }).catch(e => {
                console.log('\nCaught exception: ' + e);
            });
        }
    }

}

module.exports = GasListener;
