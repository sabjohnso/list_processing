#pragma once

//
// ... Standard header files
//
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>

//
// ... External header files
//
#include <function_utility/function_utility.hpp>
#include <type_utility/type_utility.hpp>

namespace ListProcessing::CompileTime::Details {
  using integer     = std::ptrdiff_t;
  using size_type   = integer;
  using index_type  = integer;
  using offset_type = integer;

  using std::declval;
  using std::forward;
  using std::pair;

  using std::conditional_t;
  using std::decay_t;
  using std::enable_if_t;
  using std::false_type;
  using std::is_same_v;
  using std::true_type;

  using std::integral_constant;

  using TypeUtility::Nat;
  using TypeUtility::nat;
  using TypeUtility::Type;
  using TypeUtility::type;

  using FunctionUtility::Static_callable;
  using FunctionUtility::Static_curried;

  template<integer I>
  constexpr integral_constant<integer, I> idx{};

  using std::ostream;

} // end of namespace ListProcessing::CompileTime::Details
