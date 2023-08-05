#pragma once

//
// ... Standard header files
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

//
// ... External header files
//
#include <function_utility/function_utility.hpp>
#include <type_utility/type_utility.hpp>

namespace ListProcessing::Dynamic::Details {

  using integer = std::ptrdiff_t;
  using size_type = integer;
  using index_type = integer;
  using offset_type = integer;

  using std::declval;
  using std::forward;
  using std::get;
  using std::make_pair;
  using std::move;
  using std::pair;

  using std::function;

  using std::logic_error;

  using std::copy_n;

  using std::convertible_to;
  using std::invocable;

  using std::enable_shared_from_this;
  using std::make_shared;
  using std::make_unique;
  using std::shared_ptr;
  using std::unique_ptr;

  using std::enable_if_t;
  using std::false_type;

  using std::is_assignable_v;
  using std::is_default_constructible_v;
  using std::is_fundamental_v;
  using std::is_invocable_r_v;

  using std::common_type_t;
  using std::conditional_t;
  using std::decay_t;
  using std::invoke_result_t;
  using std::is_same_v;
  using std::remove_cvref_t;
  using std::result_of_t;

  using std::array;

  using std::holds_alternative;
  using std::variant;

  using std::basic_ostream;
  using std::ostream;
  using std::to_string;

  using std::lock_guard;
  using std::mutex;

  using std::convertible_to;

  using std::nullopt;
  using std::optional;

  using std::initializer_list;

  using std::bitset;

  using TypeUtility::count_types;
  using TypeUtility::Nat;
  using TypeUtility::nat;

  using FunctionUtility::Static_callable;
  using FunctionUtility::Static_curried;
  using FunctionUtility::Trampoline;

} // end of namespace ListProcessing::Dynamic::Details
