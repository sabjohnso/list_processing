#pragma once

//
// ... List Processing header files
//
#include <list_processing/config.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {
  template<typename T>
  struct BasicListTraits
  {
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;
  };

  template<typename T>
  struct SimpleListTraits : BasicListTraits<T>
  {
    static constexpr size_type chunk_size = 1;
  };

  template<typename T>
  struct FundamentalListTraits : BasicListTraits<T>
  {
    static constexpr size_type chunk_size =
      ListProcessing::Config::Info::Parameters::default_chunk_size;
  };

  template<typename T>
  struct ListTraits
    : conditional_t<
        is_fundamental_v<T>,
        FundamentalListTraits<T>,
        SimpleListTraits<T>>
  {};

} // end of namespace ListProcessing::Dynamic::Details
