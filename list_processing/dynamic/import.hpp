#pragma once

//
// ... Standard header files
//
#include <cassert>
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <variant>
#include <type_traits>
#include <utility>
#include <concepts>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>

namespace ListProcessing::Dynamic::Details
{

  using integer = std::ptrdiff_t;
  using size_type = integer;
  using index_type = integer;
  using offset_type = integer;

  using std::forward;
  using std::move;
  using std::get;
  using std::declval;
  using std::pair;
  using std::make_pair;


  using std::logic_error;

  using std::copy_n;

  using std::make_shared;
  using std::make_unique;
  using std::shared_ptr;
  using std::unique_ptr;

  using std::false_type;
  using std::enable_if_t;

  using std::is_assignable_v;
  using std::is_default_constructible_v;
  using std::is_fundamental_v;
  using std::is_invocable_r_v;

  using std::common_type_t;
  using std::conditional_t;
  using std::decay_t;
  using std::result_of_t;

  using std::array;

  using std::variant;
  using std::holds_alternative;

  using std::ostream;
  using std::basic_ostream;
  using std::to_string;

  using std::lock_guard;
  using std::mutex;

  using std::convertible_to;

  using TypeUtility::Nat;
  using TypeUtility::nat;

  using FunctionUtility::Trampoline;

} // end of namespace ListProcessing::Dynamic::Details
