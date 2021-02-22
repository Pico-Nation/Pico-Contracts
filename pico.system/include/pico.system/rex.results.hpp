#pragma once

#include <picoio/asset.hpp>
#include <picoio/picoio.hpp>
#include <picoio/name.hpp>

using picoio::action_wrapper;
using picoio::asset;
using picoio::name;

class [[picoio::contract("rex.results")]] rex_results : picoio::contract {
   public:

      using picoio::contract::contract;

      [[picoio::action]]
      void buyresult( const asset& rex_received );

      [[picoio::action]]
      void sellresult( const asset& proceeds );

      [[picoio::action]]
      void orderresult( const name& owner, const asset& proceeds );

      [[picoio::action]]
      void rentresult( const asset& rented_tokens );

      using buyresult_action   = action_wrapper<"buyresult"_n,   &rex_results::buyresult>;
      using sellresult_action  = action_wrapper<"sellresult"_n,  &rex_results::sellresult>;
      using orderresult_action = action_wrapper<"orderresult"_n, &rex_results::orderresult>;
      using rentresult_action  = action_wrapper<"rentresult"_n,  &rex_results::rentresult>;
};
