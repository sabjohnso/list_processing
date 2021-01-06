#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class Remove : public Static_curried<Remove, Nat<2>>{
  public:
    template<typename K, typename T>
    static constexpr auto
    call(K&& key, T&& xs){
      return xs.remove(forward<K>(key));
    }
  } constexpr remove{};

} // end of namespace ListProcessing::Operators::Details
