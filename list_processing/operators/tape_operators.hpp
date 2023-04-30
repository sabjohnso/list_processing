#pragma once

namespace ListProcessing::Operators::Details {

  template<typename T>
  concept HasIsAtBack = requires(T&& xs) {
    { std::forward<T>(xs).isAtBack() };
  };

  class IsAtBack : public Static_curried<IsAtBack, Nat<1>> {
  public:
    template<HasIsAtBack T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).isAtBack();
    }
  } constexpr isAtBack{};

  template<typename T>
  concept HasIsAtFront = requires(T&& xs) {
    { std::forward<T>(xs).isAtFront() };
  };

  class IsAtFront : public Static_curried<IsAtFront, Nat<1>> {
  public:
    template<HasIsAtFront T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).isAtFront();
    }
  } constexpr isAtFront{};

  template<typename T, typename V>
  concept HasInsert = requires(V&& x, T&& xs) {
    { std::forward<T>(xs).insert(std::forward<V>(x)) };
  };

  class Insert : public Static_curried<Insert, Nat<2>> {
  public:
    template<typename V, HasInsert<V> T>
    static constexpr auto
    call(V&& x, T&& xs) {
      return std::forward<T>(xs).insert(std::forward<V>(x));
    }
  } constexpr insert{};

  template<typename T>
  concept HasErase = requires(T&& xs) {
    { std::forward<T>(xs).erase() };
  };

  class Erase : public Static_curried<Erase, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).erase();
    }
  } constexpr erase{};

  template<typename T, typename V>
  concept HasWrite = requires(V&& x, T&& xs) {
    { std::forward<T>(xs).write(std::forward<V>(x)) };
  };

  class Write : public Static_curried<Write, Nat<2>> {
  public:
    template<typename V, HasWrite<V> T>
    static constexpr auto
    call(V&& x, T&& xs) {
      return std::forward<T>(xs).write(std::forward<V>(x));
    }
  } constexpr write{};

  template<typename T>
  concept HasRead = requires(T&& xs) {
    { std::forward<T>(xs).read() };
  };

  class Read : public Static_curried<Read, Nat<1>> {
  public:
    template<HasRead T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).read();
    }
  } constexpr read{};

  template<typename T>
  concept HasPosition = requires(T&& xs) {
    { std::forward<T>(xs).position() };
  };

  class Position : public Static_curried<Position, Nat<1>> {
  public:
    template<HasPosition T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).position();
    }
  } constexpr position{};

  template<typename T>
  concept HasRemaining = requires(T&& xs) {
    { std::forward<T>(xs).remaining() };
  };

  class Remaining : public Static_curried<Remaining, Nat<1>> {
  public:
    template<HasRemaining T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).remaining();
    }
  } constexpr remaining{};

  template<typename T>
  concept HasFwd = requires(T&& xs) {
    { std::forward<T>(xs).fwd() };
  };

  class Fwd : public Static_curried<Fwd, Nat<1>> {
  public:
    template<HasFwd T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).fwd();
    }
  } constexpr fwd{};

  template<typename T>
  concept HasBwd = requires(T&& xs) {
    { std::forward<T>(xs).bwd() };
  };

  class Bwd : public Static_curried<Bwd, Nat<1>> {
  public:
    template<HasBwd T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).bwd();
    }
  } constexpr bwd{};

  template<typename T, typename I>
  concept HasMoveBy = requires(I&& offset, T&& xs) {
    { std::forward<T>(xs).moveBy(offset) };
  };

  class MoveBy : public Static_curried<MoveBy, Nat<2>> {
  public:
    template<typename I, HasMoveBy<I> T>
    static constexpr auto
    call(I&& offset, T&& xs) {
      return std::forward<T>(xs).moveBy(offset);
    }
  } constexpr moveBy{};

  template<typename T, typename I>
  concept HasMoveTo = requires(I&& index, T&& xs) {
    { std::forward<T>(xs).moveTo(index) };
  };

  class MoveTo : public Static_curried<MoveTo, Nat<2>> {
  public:
    template<typename I, HasMoveTo<I> T>
    static constexpr auto
    call(I&& index, T&& xs) {
      return std::forward<T>(xs).moveTo(index);
    }
  } constexpr moveTo{};

  template<typename T>
  concept HasToFront = requires(T&& xs) {
    { std::forward<T>(xs).toFront() };
  };

  class ToFront : public Static_curried<ToFront, Nat<1>> {
  public:
    template<HasToFront T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).toFront();
    }
  } constexpr toFront{};

  template<typename T>
  concept HasToBack = requires(T&& xs) {
    { std::forward<T>(xs).toBack() };
  };

  class ToBack : public Static_curried<ToBack, Nat<1>> {
  public:
    template<HasToBack T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).toBack();
    }
  } constexpr toBack{};

  template<typename U, typename T>
  concept HasSplice = requires(T&& xs, U&& ys) {
    { std::forward<T>(xs).splice(std::forward<T>(ys)) };
  };

  class Splice : public Static_curried<Splice, Nat<2>> {
  public:
    template<typename U, HasSplice<U> T>
    static constexpr auto
    call(T&& xs, U&& ys) {
      return std::forward<T>(xs).splice(std::forward<T>(ys));
    }
  } constexpr splice{};

} // end of namespace ListProcessing::Operators::Details
