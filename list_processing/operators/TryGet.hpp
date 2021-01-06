#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class TryGet : public Static_curried<TryGet, Nat<2>>{
  public:
    template<typename K, typename T>
    static constexpr auto
    call(K&& key, T&& xs){
      return xs.tryGet(forward<K>(key));
    }
  } constexpr tryGet{};
} // end of namespace ListProcessing::Operators::Details
