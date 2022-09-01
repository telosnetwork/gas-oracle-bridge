// @author Thomas Cuvillier
// @contract gas.bridge
// @version v1

#include <vector>

// EOSIO
#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <eosio/crypto.hpp>

// EXTERNAL
#include <intx/base.hpp>
#include <rlp/rlp.hpp>
#include <ecc/uECC.c>
#include <keccak256/k.c>
#include <boost/multiprecision/cpp_int.hpp>

// TELOS EVM
#include <constants.hpp>
#include <datastream.hpp>
#include <tables.hpp>

using namespace std;
using namespace eosio;
using namespace orc_bridge;

namespace orc_bridge
{
    class [[eosio::contract("gasbridge")]] gasbridge : public contract {
        public:
            config_singleton_bridge config_bridge;
            using contract::contract;
            gasbridge(name self, name code, datastream<const char*> ds) : contract(self, code, ds), config_bridge(self, self.value) { };
            ~gasbridge() {};

            //======================== Admin actions ========================
            // initialize the contract
            ACTION init(eosio::checksum160 evm_contract, string version);

            //set the contract version
            ACTION setversion(string new_version);

            //set the bridge evm address
            ACTION setevmctc(eosio::checksum160 new_contract);

            //======================== Bridge actions ========================
            ACTION verify();

    };
}