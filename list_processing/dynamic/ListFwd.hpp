#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/ListTraits.hpp>

namespace ListProcessing::Dynamic::Details
{

  template<typename T, size_type N = ListTraits<T>::chunk_size>
  class List;

  template<typename T>
  const List<T, ListTraits<T>::chunk_size> nil =
    List<T, ListTraits<T>::chunk_size>::nil;

} // end of namespace ListProcessing::Dynamic::Details
