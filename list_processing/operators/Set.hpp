#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class Set : public Static_curried<Set, Nat<3>>{
  public:
    template<typename K, typename V, typename T>
    static constexpr auto
    call(K&& key, V&& value, T&& xs){
      return xs.set(forward<K>(key), forward<V>(value));
    }
  } constexpr set{};


} // end of namespace ListProcessing::Operators::Details
