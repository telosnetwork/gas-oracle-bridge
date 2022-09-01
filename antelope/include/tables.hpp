#pragma once

using namespace std;
using namespace eosio;
using namespace orc_bridge;

namespace orc_bridge {
    //======================== eosio.evm tables =======================

      // Account
      struct [[eosio::table, eosio::contract("eosio.evm")]] Account {
        uint64_t index;
        eosio::checksum160 address;
        eosio::name account;
        uint64_t nonce;
        std::vector<uint8_t> code;
        bigint::checksum256 balance;

        Account () = default;
        Account (uint256_t _address): address(addressToChecksum160(_address)) {}
        uint64_t primary_key() const { return index; };

        uint64_t get_account_value() const { return account.value; };
        uint256_t get_address() const { return checksum160ToAddress(address); };
        uint256_t get_balance() const { return balance; };
        uint64_t get_nonce() const { return nonce; };
        std::vector<uint8_t> get_code() const { return code; };
        bool is_empty() const { return nonce == 0 && balance == 0 && code.size() == 0; };

        eosio::checksum256 by_address() const { return pad160(address); };

        EOSLIB_SERIALIZE(Account, (index)(address)(account)(nonce)(code)(balance));
      };
      typedef eosio::multi_index<"account"_n, Account,
        eosio::indexed_by<eosio::name("byaddress"), eosio::const_mem_fun<Account, eosio::checksum256, &Account::by_address>>,
        eosio::indexed_by<eosio::name("byaccount"), eosio::const_mem_fun<Account, uint64_t, &Account::get_account_value>>
      > account_table;

      // eosio.evm Config
      struct [[eosio::table, eosio::contract("eosio.evm")]] config {
        uint32_t trx_index = 0;
        uint32_t last_block = 0;
        bigint::checksum256 gas_used_block = 0;
        bigint::checksum256 gas_price = 1;

        EOSLIB_SERIALIZE(config, (trx_index)(last_block)(gas_used_block)(gas_price));
      };
      typedef eosio::singleton<"config"_n, config> config_singleton_evm;

    //======================== Tables ========================
    // Config
    TABLE bridgeconfig {
        eosio::checksum160 evm_contract;
        string version;

        EOSLIB_SERIALIZE(bridgeconfig, (evm_contract)(admin)(version));
    } config_row;

    typedef eosio::singleton<"bridgeconfig"_n, bridgeconfig> config_singleton_bridge;
}