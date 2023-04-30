#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {

  template<typename T, typename V>
  concept HasPush = requires(V&& x, T&& xs) {
    { std::forward<T>(xs).push(std::forward<V>(x)) };
  };

  class Push : public Static_curried<Push, Nat<2>> {
  public:
    template<typename V, HasPush<V> T>
    static constexpr auto
    call(V&& x, T&& xs) {
      return std::forward<T>(xs).push(std::forward<V>(x));
    }
  } constexpr push{};

  template<typename T>
  concept HasTop = requires(T&& xs) {
    { std::forward<T>(xs).top() };
  };

  class Top : public Static_curried<Top, Nat<1>> {
  public:
    template<HasTop T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).top();
    }
  } constexpr top{};

  template<typename T>
  concept HasPop = requires(T&& xs) {
    { std::forward<T>(xs).pop() };
  };

  class Pop : public Static_curried<Pop, Nat<1>> {
  public:
    template<HasPop T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).pop();
    }
  } constexpr pop{};

  template<typename T>
  concept HasPop2 = requires(T&& xs) {
    { std::forward<T>(xs).pop2() };
  };

  class Pop2 : public Static_curried<Pop2, Nat<1>> {
  public:
    template<HasPop2 T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).pop2();
    }
  } constexpr pop2{};

  template<typename T>
  concept HasPop3 = requires(T&& xs) {
    { std::forward<T>(xs).pop3() };
  };

  class Pop3 : public Static_curried<Pop3, Nat<1>> {
  public:
    template<HasPop3 T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).pop3();
    }
  } constexpr pop3{};

  template<typename T>
  concept HasDup = requires(T&& xs) {
    { std::forward<T>(xs).dup() };
  };

  class Dup : public Static_curried<Dup, Nat<1>> {
  public:
    template<HasDup T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).dup();
    }
  } constexpr dup{};

  class Swap : public Static_curried<Swap, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs) {
      return xs.swap();
    }
  } constexpr swap{};

  template<typename T>
  concept HasNip = requires(T&& xs) {
    { std::forward<T>(xs).nip() };
  };

  class Nip : public Static_curried<Nip, Nat<1>> {
  public:
    template<HasNip T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).nip();
    }
  } constexpr nip{};

  template<typename T>
  concept HasTuck = requires(T&& xs) {
    { std::forward<T>(xs).tuck() };
  };

  class Tuck : public Static_curried<Tuck, Nat<1>> {
  public:
    template<HasTuck T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).tuck();
    }
  } constexpr tuck{};

  template<typename T>
  concept HasOver = requires(T&& xs) {
    { std::forward<T>(xs).over() };
  };

  class Over : public Static_curried<Over, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).over();
    }
  } constexpr over{};

  template<typename T>
  concept HasRot = requires(T&& xs) {
    { std::forward<T>(xs).rot() };
  };

  class Rot : public Static_curried<Rot, Nat<1>> {
  public:
    template<HasRot T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).rot();
    }
  } constexpr rot{};

  template<typename T, typename F>
  concept HasApp1 = requires(F&& f, T&& xs) {
    { std::forward<T>(xs).app1(std::forward<F>(f)) };
  };

  class App1 : public Static_curried<App1, Nat<2>> {
  public:
    template<typename F, HasApp1<F> T>
    static constexpr auto
    call(F&& f, T&& xs) {
      return std::forward<T>(xs).app1(std::forward<F>(f));
    }
  } constexpr app1{};

  template<typename T, typename F>
  concept HasApp2 = requires(F&& f, T&& xs) {
    { std::forward<T>(xs).app2(std::forward<F>(f)) };
  };

  class App2 : public Static_curried<App2, Nat<2>> {
  public:
    template<typename F, HasApp2<F> T>
    static constexpr auto
    call(F&& f, T&& xs) {
      return std::forward<T>(xs).app2(std::forward<F>(f));
    }
  } constexpr app2{};

} // end of namespace ListProcessing::Operators::Details
