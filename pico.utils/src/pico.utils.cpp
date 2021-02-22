/**
 *  @copyright defined in pico/LICENSE.txt
 */

#include <pico.utils/pico.utils.hpp>

namespace picoio {

   void utils::validateaddr( const name& chain_id, const string& address ) {
      if (chain_id.to_string() == "ethropsten" || chain_id.to_string() == "eth") {
         validate_eth_address(address);
      }
   }
} /// namespace picoio

PICOIO_DISPATCH( picoio::utils, (validateaddr) )
