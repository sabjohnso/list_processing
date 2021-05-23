#pragma once

//
// ... Standard header files
//
#include <utility>

//
// ... External header files
//
#include <function_utility/function_utility.hpp>
#include <type_utility/type_utility.hpp>

namespace ListProcessing::Operators::Details {
  using std::forward;

  using FunctionUtility::Static_callable;
  using FunctionUtility::Static_curried;
  using TypeUtility::Nat;

} // end of namespace ListProcessing::Operators::Details
