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
        auto account = accounts_byaddress.require_find(pad160(new_contract), "EVM bridge contract not found in eosio.evm Account table");

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
        // Get gas price from the eosio.evm table
        // Get gas price stored in EVM state
        // If different update price on EVM
    };
}