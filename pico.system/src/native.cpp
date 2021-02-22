#include <pico.system/native.hpp>

#include <picoio/check.hpp>

namespace picoiosystem {

   void native::onerror( ignore<uint128_t>, ignore<std::vector<char>> ) {
      picoio::check( false, "the onerror action cannot be called directly" );
   }

}
