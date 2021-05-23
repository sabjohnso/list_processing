#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename K>
  concept HasUnset = requires(K&& key, T&& xs) {
    { forward<T>(xs).unset(forward<K>(key)) };
  };

  class Unset : public Static_curried<Unset, Nat<2>> {
  public:
    template<typename K, HasUnset<K> T>
    static constexpr auto
    call(K&& key, T&& xs) {
      return forward<T>(xs).unset(forward<K>(key));
    }
  } constexpr unset{};

} // end of namespace ListProcessing::Operators::Details
