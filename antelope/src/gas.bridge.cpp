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

        // initialize
        auto stored = config_bridge.get_or_create(get_self(), config_row);

        stored.version            = version;
        stored.evm_contract       = evm_contract;

        config_bridge.set(stored, get_self());
    };

    // set the contract version
    ACTION gasbridge::setversion(string new_version){
        // authenticate
        require_auth(config_bridge.get().admin);

        auto stored = config_bridge.get();
        stored.version = new_version;

        // modify
        config_bridge.set(stored, get_self());
    };

    // set the bridge evm address
    ACTION gasbridge::setevmctc(eosio::checksum160 new_contract){
        // authenticate
        require_auth(config_bridge.get().admin);

        // Save
        auto stored = config_bridge.get();
        stored.evm_contract = new_contract;

        config_bridge.set(stored, get_self());
    };


    //======================== Gas Oracle actions ========================

    ACTION gasbridge::verify()
    {
    };
}