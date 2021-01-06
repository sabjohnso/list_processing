#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class Unset : public Static_curried<Unset, Nat<2>>{
  public:
    template<typename K, typename T>
    static constexpr auto
    call(K&& key, T&& xs){
      return xs.unset(forward<K>(key));
    }
  } constexpr unset{};

} // end of namespace ListProcessing::Operators::Details
