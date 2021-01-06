#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  class ForceGet : public Static_curried<ForceGet, Nat<3>> {
  public:
    template<typename K, typename V, typename T>
    static constexpr auto
    call(K&& key, V&& alternate, T&& xs){
      return xs.forceGet(forward<K>(key), forward<V>(alternate));
    }
  } constexpr forceGet{};

} // end of namespace ListProcessing::Operators::Details
