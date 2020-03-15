#pragma once
//
// ... Standard header files
//
#include <cstddef>
#include <type_traits>
#include <utility>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

namespace ListProcessing::CompileTime::Details {
  using integer = std::ptrdiff_t;
  using size_type = integer;
  using index_type = integer;

  using std::forward;
  using std::pair;

  using std::decay_t;
  using std::enable_if_t;

  using std::integral_constant;

  using TypeUtility::Nat;
  using TypeUtility::nat;
  using TypeUtility::Type;
  using TypeUtility::type;

} // end of namespace ListProcessing::CompileTime::Details
