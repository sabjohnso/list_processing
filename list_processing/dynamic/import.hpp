#pragma once

//
// ... Standard header files
//
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

namespace ListProcessing::Dynamic::Details {

  using integer = std::ptrdiff_t;
  using size_type = integer;
  using index_type = integer;

  using std::logic_error;
  using std::make_shared;
  using std::shared_ptr;

  using std::common_type_t;
  using std::decay_t;
  using std::result_of_t;

  using std::to_string;

  using TypeUtility::Nat;
  using TypeUtility::nat;

} // end of namespace ListProcessing::Dynamic::Details
