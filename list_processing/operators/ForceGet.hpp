#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename K, typename V>
  concept HasForceGet = requires(K&& key, V&& alternate, T&& xs) {
    { std::forward<T>(xs).forceGet(std::forward<K>(key), std::forward<V>(alternate)) };
  };

  class ForceGet : public Static_curried<ForceGet, Nat<3>> {
  public:
    template<typename K, typename V, HasForceGet<K, V> T>
    static constexpr auto
    call(K&& key, V&& alternate, T&& xs) {
      return std::forward<T>(xs).forceGet(std::forward<K>(key), std::forward<V>(alternate));
    }
  } constexpr forceGet{};

} // end of namespace ListProcessing::Operators::Details
