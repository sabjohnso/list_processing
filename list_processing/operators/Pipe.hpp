#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class Pipe : public Static_callable<Pipe>
  {
  public:

    template<typename T>
    static constexpr auto
    call(T&& x){ return x; }

    template<typename T, typename F, typename ... Gs>
    static constexpr auto
    call(T&& x, F&& f, Gs&& ... gs){
      return call(forward<F>(f)(forward<T>(x)), forward<Gs>(gs) ...);
    }
  } constexpr pipe{};


} // end of namespace ListProcessing::Operators::Details
