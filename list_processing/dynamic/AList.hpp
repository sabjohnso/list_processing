#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/List.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename K, typename T>
  class AList
  {
  public:
    using key_type = K;
    using value_type = T;
    using assoc_type = pair<K,T>;

    AList() : data(nil<assoc_type>) {}

    AList(AList alist, assoc_type assoc )
      : data(cons(assoc, alist))
    {}

  private:
    List<assoc_type> data;

    friend bool
    isEmpty(AList xs){
      return isNull(xs.data);
    }


  }; // end of class AList

  template<typename K, typename T>
  const AList<K,T> empty_alist{};

} // end of namespace ListProcessing::Dynamic::Details
