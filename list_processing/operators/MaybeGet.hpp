#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename K>
  concept HasMaybeGet = requires(K&& key, T&& xs) {
    { std::forward<T>(xs).maybeGet(std::forward<K>(key)) };
  };

  class MaybeGet : public Static_curried<MaybeGet, Nat<2>> {
  public:
    template<typename K, HasMaybeGet<K> T>
    static constexpr auto
    call(K&& key, T&& xs) {
      return std::forward<T>(xs).maybeGet(std::forward<K>(key));
    }
  } constexpr maybeGet{};
} // end of namespace ListProcessing::Operators::Details
