
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
using namespace eosio;
using namespace std;
namespace activity {
    CONTRACT activity : public contract {
      public:
        activity( name receiver, name code, datastream<const char*> ds ): contract::contract(receiver, code, ds), _signers(receiver, receiver.value)
        {}
        ACTION clean();
        ACTION signup(name user);
        TABLE sign {
            name attendee;
            time_point_sec time;
            uint64_t primary_key() const { return attendee.value; }
        };
        typedef multi_index<"sign"_n, sign> signup_table;
      private:
        signup_table _signers;
    };

};
