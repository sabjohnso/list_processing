#pragma once

//
// ... Standard header files
//
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

namespace ListProcessing::Dynamic::Details
{

  using integer = std::ptrdiff_t;
  using size_type = integer;
  using index_type = integer;
  using offset_type = integer;

  using std::forward;
  using std::move;

  using std::logic_error;

  using std::copy_n;

  using std::make_shared;
  using std::make_unique;
  using std::shared_ptr;
  using std::unique_ptr;

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

  using std::ostream;
  using std::to_string;

  using std::lock_guard;
  using std::mutex;

  using TypeUtility::Nat;
  using TypeUtility::nat;

} // end of namespace ListProcessing::Dynamic::Details
