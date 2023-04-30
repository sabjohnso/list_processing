#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename K>
  concept HasTryGet = requires(K&& key, T&& xs) {
    { std::forward<T>(xs).tryGet(std::forward<K>(key)) };
  };

  class TryGet : public Static_curried<TryGet, Nat<2>> {
  public:
    template<typename K, HasTryGet<K> T>
    static constexpr auto
    call(K&& key, T&& xs) {
      return std::forward<T>(xs).tryGet(std::forward<K>(key));
    }
  } constexpr tryGet{};

} // end of namespace ListProcessing::Operators::Details
