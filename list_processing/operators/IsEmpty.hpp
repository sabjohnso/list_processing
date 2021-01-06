#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class IsEmpty : public Static_curried<HasData, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){ return xs.isEmpty(); }
  } constexpr isEmpty{};

} // end of namespace ListProcessing::Operators::Details
