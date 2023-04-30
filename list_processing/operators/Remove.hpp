#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename K>
  concept HasRemove = requires(K&& key, T&& xs) {
    { std::forward<T>(xs).remove(std::forward<K>(key)) };
  };

  class Remove : public Static_curried<Remove, Nat<2>> {
  public:
    template<typename K, HasRemove<K> T>
    static constexpr auto
    call(K&& key, T&& xs) {
      return std::forward<T>(xs).remove(std::forward<K>(key));
    }
  } constexpr remove{};

} // end of namespace ListProcessing::Operators::Details
