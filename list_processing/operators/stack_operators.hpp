#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{

  class Push : public Static_curried<Push, Nat<2>>{
  public:
    template<typename V, typename T>
    static constexpr auto
    call(V&& x, T&& xs){
      return xs.push(forward<V>(x));
    }
  } constexpr push{};

  class Top : public Static_curried<Top,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.top();
    }
  } constexpr top{};

  class Pop : public Static_curried<Pop,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.pop();
    }
  } constexpr pop{};

  class Drop : public Static_curried<Drop,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.drop();
    }
  } constexpr drop{};

  class Drop2 : public Static_curried<Drop2, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.drop2();
    }
  } constexpr drop2{};

  class Drop3 : public Static_curried<Drop3,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.drop3();
    }
  } constexpr drop3{};

  class Dup : public Static_curried<Dup,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.dup();
    }
  } constexpr dup{};

  class Swap : public Static_curried<Swap, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.swap();
    }
  } constexpr swap{};

  class Nip : public Static_curried<Nip, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.nip();
    }
  } constexpr nip{};

  class Tuck : public Static_curried<Tuck, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.tuck();
    }
  } constexpr tuck{};

  class Over : public Static_curried<Over, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.over();
    }
  } constexpr over{};

  class Rot : public Static_curried<Rot, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.rot();
    }
  } constexpr rot{};

  class App1 : public Static_curried<App1,Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& f, T&& xs){
      return xs.app1(forward<F>(f));
    }
  } constexpr app1{};

  class App2 : public Static_curried<App2, Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& f, T&& xs){
      return xs.app2(forward<F>(f));
    }
  } constexpr app2{};

} // end of namespace ListProcessing::Operators::Details
