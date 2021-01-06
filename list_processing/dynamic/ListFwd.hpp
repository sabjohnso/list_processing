#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/ListTraits.hpp>

namespace ListProcessing::Dynamic::Details
{

  /**
   * @brief A class template describing homogeneous dynamic lists.
   *
   * @details Specializations of this class implement a persistent
   * (functional) list data structure where specializations provide
   * optimizations for some value types but present a uniform interface
   *
   * @tparam T - a type parameter specifying the list element type
   *
   * @tparam N - an integral type parameter specifying the chunk size
   * for the underlying kernel. The chunk size is use to reduce the
   * memory overhead of lists with certain value types.
   */
  template<typename T, size_type N = ListTraits<T>::chunk_size>
  class List;

  template<typename T>
  const List<T, ListTraits<T>::chunk_size> nil =
    List<T, ListTraits<T>::chunk_size>::nil;

  template<typename T>
  using ListType = List<T, ListTraits<T>::chunk_size>;


} // end of namespace ListProcessing::Dynamic::Details
