
#include "activity.hpp"

namespace activity{
  ACTION activity::signup(name user){
      require_auth(user);
      auto sign_itr = _signers.find(user.value);
      eosio_assert(sign_itr == _signers.end(), "already signed");

      _signers.emplace(_self,[&](auto& s){
        s.attendee = user;
        s.time = time_point_sec(now());
      });
  }
  ACTION activity::clean() {
    auto sign_itr = _signers.begin();
    while(sign_itr != _signers.end()) {
      sign_itr = _signers.erase(sign_itr);
    }
    printf("activity v0.0.1");
  }
};

EOSIO_DISPATCH(activity::activity, (signup)(clean))
