#pragma once

// Adds superpower testing functions (required for running cpp tests/clearing data in contract)
#define TESTING false

// Crypto
#define MBEDTLS_ASN1_OCTET_STRING 0x04

namespace orc_bridge
{
  struct ChainIDs
  {
    static constexpr size_t TELOS_MAINNET        = 40;
    static constexpr size_t TELOS_TESTNET        = 41;
  };

  static constexpr auto WORD_SIZE       = 32u;
  static constexpr auto EVM_SYSTEM_CONTRACT       = eosio::name("eosio.evm");
  static constexpr auto FUNCTION_SIGNATURE       = "abbbc0e0";
  static constexpr auto GAS_LIMIT       = 0x000000000000000000000000000000000000000000000000000000001e8480 ;
  // Constant chain ID determined at COMPILE time
  static constexpr size_t CURRENT_CHAIN_ID = ChainIDs::TELOS_TESTNET;
}