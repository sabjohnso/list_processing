#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T, typename K, typename V>
  concept HasSet = requires(K&& key, V&& value, T&& xs) {
    { std::forward<T>(xs).set(std::forward<K>(key), std::forward<V>(value)) };
  };

  class Set : public Static_curried<Set, Nat<3>> {
  public:
    template<typename K, typename V, HasSet<K, V> T>
    static constexpr auto
    call(K&& key, V&& value, T&& xs) {
      return std::forward<T>(xs).set(std::forward<K>(key), std::forward<V>(value));
    }
  } constexpr set{};

} // end of namespace ListProcessing::Operators::Details
