#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T, typename K>
  concept HasHasKey = requires(K&& key, T&& xs) {
    { std::forward<T>(xs).hasKey(std::forward<K>(key)) };
  };

  class HasKey : public Static_curried<HasKey, Nat<2>> {
  public:
    template<typename K, HasHasKey<K> T>
    static constexpr auto
    call(K&& key, T&& xs) {
      return std::forward<T>(xs).hasKey(std::forward<K>(key));
    }
  } constexpr hasKey{};
} // end of namespace ListProcessing::Operators::Details
