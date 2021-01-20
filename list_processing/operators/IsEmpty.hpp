#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{

  template<typename T>
  concept HasIsEmpty = requires(T&& xs){
    {forward<T>(xs).isEmpty()};
  };

  class IsEmpty : public Static_curried<IsEmpty, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){ return forward<T>(xs).isEmpty(); }
  } constexpr isEmpty{};

} // end of namespace ListProcessing::Operators::Details
