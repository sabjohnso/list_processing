#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class MaybeGet : public Static_curried<MaybeGet, Nat<2>>{
  public:
    template<typename K, typename T>
    static constexpr auto
    call(K&& key, T&& xs){
      return xs.maybeGet(forward<K>(key));
    }
  } constexpr maybeGet{};
} // end of namespace ListProcessing::Operators::Details
