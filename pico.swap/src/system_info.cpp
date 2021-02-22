/**
 *  @copyright defined in pico/LICENSE.txt
 */

#include <pico.swap/pico.swap.hpp>
#include <pico.system/pico.system.hpp>

namespace picoio {

   using picoiosystem::system_contract;

   struct [[picoio::table("global"), picoio::contract("pico.system")]] picoio_global_state : picoio::blockchain_parameters {
      uint64_t free_ram()const { return max_ram_size - total_ram_bytes_reserved; }

      symbol               core_symbol;

      uint64_t             max_ram_size = 64ll*1024 * 1024 * 1024;
      uint64_t             min_account_stake = 1000000; // minimum stake for new created account 100'0000 REM
      uint64_t             total_ram_bytes_reserved = 0;
      int64_t              total_ram_stake = 0;
      //producer name and pervote factor
      std::vector<std::pair<picoio::name, double>> last_schedule;
      std::vector<std::pair<picoio::name, double>> standby;
      uint32_t last_schedule_version = 0;
      block_timestamp current_round_start_time;

      block_timestamp      last_producer_schedule_update;
      time_point           last_pervote_bucket_fill;
      int64_t              perstake_bucket = 0;
      int64_t              pervote_bucket = 0;
      int64_t              perblock_bucket = 0;
      uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
      int64_t              total_guardians_stake = 0;
      int64_t              total_activated_stake = 0;
      time_point           thresh_activated_stake_time;
      uint16_t             last_producer_schedule_size = 0;
      double               total_producer_vote_weight = 0; /// the sum of all producer votes
      double               total_active_producer_vote_weight = 0; /// the sum of top 21 producer votes
      block_timestamp      last_name_close;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      PICOLIB_SERIALIZE_DERIVED( picoio_global_state, picoio::blockchain_parameters, (core_symbol)(max_ram_size)(min_account_stake)
                                (total_ram_bytes_reserved)(total_ram_stake)(last_schedule)(standby)(last_schedule_version)
                                (current_round_start_time) (last_producer_schedule_update)(last_pervote_bucket_fill)
                                (perstake_bucket)(pervote_bucket)(perblock_bucket)(total_unpaid_blocks)(total_guardians_stake)
                                (total_activated_stake)(thresh_activated_stake_time)(last_producer_schedule_size)
                                (total_producer_vote_weight)(total_active_producer_vote_weight)(last_name_close) )
   };

   typedef picoio::singleton< "global"_n, picoio_global_state >   global_state_singleton;

   asset swap::get_min_account_stake() const
   {
      global_state_singleton global( system_account, system_account.value );
      auto _gstate = global.get();
      return { static_cast<int64_t>( _gstate.min_account_stake ), system_contract::get_core_symbol() };
   }

   asset swap::get_producers_reward(const name &chain_id) const
   {
      auto it = chains_table.find(chain_id.value);
      check(it != chains_table.end() && it->input, "not supported chain id");
      return asset{ it->in_swap_min_amount, system_contract::get_core_symbol() };
   }

   vector<name> swap::get_producers() const
   {
      global_state_singleton global( system_account, system_account.value );
      auto _gstate = global.get();
      vector<name> _producers;
      for(const auto &producer: _gstate.last_schedule)
         _producers.push_back(producer.first);
      for(const auto &producer: _gstate.standby)
         _producers.push_back(producer.first);
      return _producers;
   }

   bool swap::is_block_producer( const name& user ) const
   {
      vector<name> _producers = get_producers();
      return std::find(_producers.begin(), _producers.end(), user) != _producers.end();
   }

   bool swap::is_swap_confirmed( const vector<name>& provided_approvals ) const
   {
      vector<name> _producers = picoio::get_active_producers();
      uint8_t quantity_active_appr = 0;
      for (const auto& producer: provided_approvals) {
         auto prod_appr = std::find(_producers.begin(), _producers.end(), producer);
         if ( prod_appr != _producers.end() || producer == system_account ) {
            ++quantity_active_appr;
         }
      }
      const uint8_t majority = (_producers.size() * 2 / 3) + 1;
      if ( majority <= quantity_active_appr ) { return true; }
      return false;
   }

   void swap::check_pubkey_prefix(const string& pubkey_str) const
   {
      string pubkey_pre = pubkey_str.substr(0, 3);
      check(pubkey_pre == "PICO" || pubkey_pre == "REM", "invalid type of public key");
   }

} // namespace picoio
