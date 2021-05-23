#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T>
  concept HasHasData = requires(T&& x) {
    { x.hasData() };
  };

  class HasData : public Static_curried<HasData, Nat<1>> {
  public:
    template<HasHasData T>
    static constexpr auto
    call(T&& xs) {
      return xs.hasData();
    }
  } constexpr hasData{};

} // end of namespace ListProcessing::Operators::Details
