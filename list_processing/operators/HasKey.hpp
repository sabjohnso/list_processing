#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class HasKey : public Static_curried<HasKey, Nat<2>>{
  public:
    template<typename T, typename K>
    static constexpr auto
    call(K&& key, T&& xs){
      return xs.hasKey(forward<K>(key));
    }
  } constexpr hasKey{};
} // end of namespace ListProcessing::Operators::Details
