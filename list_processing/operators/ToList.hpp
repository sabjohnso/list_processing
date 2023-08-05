#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T>
  concept HasToList = requires(const T& xs) { xs.toList(); };

  class ToList : public Static_callable<ToList>
  {
  public:
    template<HasToList T>
    static constexpr auto
    call(T&& xs)
    {
      return std::forward<T>(xs).toList();
    }
  } constexpr toList{};

} // namespace ListProcessing::Operators::Details
