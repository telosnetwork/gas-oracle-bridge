#include "../include/gas.bridge.hpp";

namespace orc_bridge
{
    //======================== admin actions ==========================
    // initialize the contract
    ACTION gasbridge::init(eosio::checksum160 evm_contract, string version){
        // authenticate
        require_auth(get_self());

        // validate
        check(!config_bridge.exists(), "contract already initialized");

        // Get the scope for accountstates for lookup later
        account_table accounts(EVM_SYSTEM_CONTRACT, EVM_SYSTEM_CONTRACT.value);
        auto accounts_byaddress = accounts.get_index<"byaddress"_n>();
        auto account = accounts_byaddress.require_find(pad160(evm_contract), "EVM bridge contract not found in eosio.evm Account table");

        // initialize
        auto stored = config_bridge.get_or_create(get_self(), config_row);

        stored.version            = version;
        stored.evm_contract       = evm_contract;
        stored.evm_contract_scope = account->index;

        config_bridge.set(stored, get_self());
    };

    // set the contract version
    ACTION gasbridge::setversion(string new_version){
        // authenticate
        require_auth(get_self());

        auto stored = config_bridge.get();
        stored.version = new_version;

        // modify
        config_bridge.set(stored, get_self());
    };

    // set the bridge evm address
    ACTION gasbridge::setevmctc(eosio::checksum160 new_contract){
        // authenticate
        require_auth(get_self());

        // Get the scope for accountstates for lookup later
        account_table accounts(EVM_SYSTEM_CONTRACT, EVM_SYSTEM_CONTRACT.value);
        auto accounts_byaddress = accounts.get_index<"byaddress"_n>();
        auto account = accounts_byaddress.require_find(pad160(new_contract), "EVM bridge contract not found in eosio.evm Account table");

        // Save
        auto stored = config_bridge.get();
        stored.evm_contract = new_contract;
        stored.evm_contract_scope = account->index;

        config_bridge.set(stored, get_self());
    };


    //======================== Gas Oracle actions ========================

    ACTION gasbridge::verify()
    {
        // open config singletons
        const auto conf = config_bridge.get();
        config_singleton_evm config_evm(EVM_SYSTEM_CONTRACT, EVM_SYSTEM_CONTRACT.value);
        const auto evm_conf = config_evm.get();

        // Define EVM tables
        account_state_table account_states(EVM_SYSTEM_CONTRACT, conf.evm_contract_scope);
        account_table _accounts(EVM_SYSTEM_CONTRACT, EVM_SYSTEM_CONTRACT.value);

        // find EVM account for this contract (if does not exist, you can create it via eosio.evm create action)
        const auto accounts_byaccount = _accounts.get_index<"byaccount"_n>();
        const auto account = accounts_byaccount.require_find(get_self().value, "Account not found");

        // Get gas price from the eosio.evm table
        const auto antelope_evm_gas_price = evm_conf.gas_price;
        const auto antelope_evm_gas_price_bs = toBin(antelope_evm_gas_price);

        // Get gas price stored in EVM state
        const auto storage_key = toChecksum256(uint256_t(EVM_STORAGE_INDEX));
        const auto account_states_bykey = account_states.get_index<"bykey"_n>();
        const auto gas_price_checksum = account_states_bykey.find(storage_key);
        const uint256_t gas_price = (gas_price_checksum == account_states_bykey.end()) ? uint256_t(0) : gas_price_checksum->value;
        
        if(antelope_evm_gas_price != gas_price){ // If different update price on EVM
            // Get "to" address from config singleton
            const auto evm_contract = conf.evm_contract.extract_as_byte_array();
            std::vector<uint8_t> to;
            to.insert(to.end(),  evm_contract.begin(), evm_contract.end());
            // Prepare data (function sig + arguments)
            std::vector<uint8_t> data;
            const auto function_signature = toBin(FUNCTION_SIGNATURE);
            data.insert(data.end(), function_signature.begin(), function_signature.end());
            data.insert(data.end(), antelope_evm_gas_price_bs.begin(), antelope_evm_gas_price_bs.end());
            // send back to EVM using eosio.evm
            action(
                permission_level {get_self(), "active"_n},
                EVM_SYSTEM_CONTRACT,
                "raw"_n,
                std::make_tuple(get_self(), rlp::encode(account->nonce, antelope_evm_gas_price, GAS_LIMIT, to, uint256_t(0), data, CURRENT_CHAIN_ID, 0, 0),  false, std::optional<eosio::checksum160>(account->address))
            ).send();    
        }
    };
}