#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T>
  struct ListTraits
  {
    static constexpr size_type chunk_size = 1;
  };

  template<>
  struct ListTraits<char>
  {
    static constexpr size_type chunk_size = 32;
  };

} // end of namespace ListProcessing::Dynamic::Details
