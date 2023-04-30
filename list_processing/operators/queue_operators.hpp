#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T>
  concept HasFront = requires(T&& xs) {
    { std::forward<T>(xs).front() };
  };

  class Front : public Static_curried<Front, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).front();
    }
  } constexpr front{};

} // end of namespace ListProcessing::Operators::Details
