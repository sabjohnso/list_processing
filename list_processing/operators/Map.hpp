#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename F>
  concept HasMap = requires(F&& f, T&& xs)
  {
    { std::forward<T>(xs).map(std::forward<F>(f)) };
  };

  class Map : public Static_curried<Map, Nat<2>>
  {
  public:
    template<typename F, HasMap<F> T>
    static constexpr auto
    call(F&& f, T&& xs)
    {
      return std::forward<T>(xs).map(std::forward<F>(f));
    }
  } constexpr map{};

} // end of namespace ListProcessing::Operators::Details
