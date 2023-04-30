#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T, typename U>
  class Cell;

  template<typename T, typename U>
  Cell(T&& x, U&& y) -> Cell<decay_t<T>, decay_t<U>>;

  class Cons : public Static_curried<Cons, Nat<2>>
  {
  public:
    template<typename T, typename U>
    static constexpr auto
    call(T&& x, U&& y)
    {
      return Cell(std::forward<T>(x), std::forward<U>(y));
    }
  } constexpr cons{};

} // end of namespace ListProcessing::CompileTime::Details
