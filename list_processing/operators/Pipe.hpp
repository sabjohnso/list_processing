#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename F, typename T>
  concept HasCall = requires(T&& x, F&& f) {
    { std::forward<F>(f)(std::forward<T>(x)) };
  };

  class Pipe : public Static_callable<Pipe> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& x) {
      return std::forward<T>(x);
    }

    template<typename T, HasCall<T> F, typename... Gs>
    static constexpr auto
    call(T&& x, F&& f, Gs&&... gs) {
      return Pipe::call(std::forward<F>(f)(std::forward<T>(x)), std::forward<Gs>(gs)...);
    }
  } constexpr pipe{};

} // end of namespace ListProcessing::Operators::Details
