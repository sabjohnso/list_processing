#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class Front : public Static_curried<Front, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.front();
    }
  } constexpr front{};

} // end of namespace ListProcessing::Operators::Details
