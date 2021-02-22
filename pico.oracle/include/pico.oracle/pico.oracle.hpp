/**
 *  @copyright defined in pico/LICENSE.txt
 */

#pragma once

#include <picoio/asset.hpp>
#include <picoio/singleton.hpp>
#include <picoio/picoio.hpp>

namespace picooracle {

   using picoio::asset;
   using picoio::block_timestamp;
   using picoio::check;
   using picoio::const_mem_fun;
   using picoio::current_time_point;
   using picoio::datastream;
   using picoio::indexed_by;
   using picoio::singleton;
   using picoio::seconds;
   using picoio::name;
   using picoio::time_point;
   using picoio::multi_index;
   using std::string;
   using std::vector;

   // A window in which producer can submit a new rate
   static constexpr uint32_t setprice_window_seconds = 3600;

   // Defines 'picoprice' to be stored market price to the specified pairs
   struct [[picoio::table, picoio::contract("pico.oracle")]] picoprice {
      name                    pair;
      double                  price = 0;
      vector<double>          price_points;
      block_timestamp         last_update;

      uint64_t primary_key()const { return pair.value; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      PICOLIB_SERIALIZE( picoprice, (pair)(price)(price_points)(last_update))
   };

   typedef multi_index< "picoprice"_n, picoprice> picoprice_idx;

   /**
    * @defgroup picoiooracle pico.oracle
    * @ingroup picoiocontracts
    *
    * pico.oracle contract
    *
    * @details pico.oracle contract defines the structures and actions that allow users and contracts set/get current
    * cryptocurrencies market price.
    * @{
    */

   class [[picoio::contract("pico.oracle")]] oracle : public picoio::contract {
   public:

      oracle(name receiver, name code,  datastream<const char*> ds);

      /**
       * Set the current market price of cryptocurrencies action.
       *
       * @details Set market price of supported cryptocurrencies.
       *
       * @param producer - the producer account to execute the setprice action for,
       * @param pairs_data - the rate of the pairs.
       */
      [[picoio::action]]
      void setprice(const name &producer, std::map<name, double> &pairs_data);

      /**
       * Add a new pair action.
       *
       * @details Add a new pair that will be supported, action permitted only for block producers.
       *
       * @param pair - the new pair name.
       */
      [[picoio::action]]
      void addpair(const name &pair);

   private:
      static constexpr name system_account = "pico"_n;

      struct [[picoio::table]] pricedata {
         name                    producer;
         std::map<name, double>  pairs_data;
         block_timestamp         last_update;

         uint64_t primary_key()const { return producer.value; }

         // explicit serialization macro is not necessary, used here only to improve compilation time
         PICOLIB_SERIALIZE( pricedata, (producer)(pairs_data)(last_update))
      };

      struct [[picoio::table]] pairstable {
         std::set<name> pairs {};

         // explicit serialization macro is not necessary, used here only to improve compilation time
         PICOLIB_SERIALIZE( pairstable, (pairs))
      };

      typedef multi_index< "pricedata"_n, pricedata>  pricedata_idx;
      typedef singleton< "pairstable"_n,  pairstable> pairs_idx;

      pricedata_idx    pricedata_tbl;
      picoprice_idx     picoprice_tbl;
      pairs_idx        pairs_tbl;
      pairstable       pairstable_data;

      void check_pairs(const std::map<name, double> &pairs);
      void to_rewards(const asset &quantity, const name &payer);

      uint8_t get_majority_amount() const;
      std::map<name, vector<double>> get_relevant_prices() const;
      bool is_producer( const name& user ) const;

      double get_subset_median(vector<double> points) const;
      double get_median(const vector<double>& sorted_points) const;
   };
   /** @}*/ // end of @defgroup picoioauth pico.oracle
} /// namespace picooracle
