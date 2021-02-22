/**
 *  @copyright defined in pico/LICENSE.txt
 */

#pragma once

#include <picoio/asset.hpp>
#include <picoio/picoio.hpp>

namespace picoio {

   using std::string;

   /**
    * @defgroup picoioutils pico.utils
    * @ingroup picoiocontracts
    *
    * pico.utils contract
    *
    * @details pico.utils contract defines the structures and actions that allow users and contracts to use helpful
    * tools. Implement validation address another blockchain.
    * @{
    */
   class [[picoio::contract("pico.utils")]] utils : public contract {
   public:
      using contract::contract;

      /**
       * Validate address action.
       *
       * @details Validation blockchain address.
       *
       * @param name - the chain id address validation for,
       * @param address - the address in the corresponding chain network.
       */
      [[picoio::action]]
      void validateaddr( const name& chain_id, const string& address );

      using validate_address_action = action_wrapper<"validateaddr"_n, &utils::validateaddr>;
   private:
      void validate_eth_address(string address);
      void validate_eth_address_checksum(string checksum_address);
      string bytetohex(unsigned char *data, int len);
      std::array<unsigned char, 32> sha3_256(const string& address);
      bool is_lower(const string &address);
   };
   /** @}*/ // end of @defgroup picoioutils pico.utils
} /// namespace picoio
