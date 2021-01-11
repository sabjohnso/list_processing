#pragma once

namespace ListProcessing::Operators::Details
{

  class Map : public Static_curried<Map, Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& f, T&& xs){
      return forward<T>(xs).map(forward<F>(f));
    }
  } constexpr map{};

} // end of namespace ListProcessing::Operators::Details
