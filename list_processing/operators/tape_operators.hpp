#pragma once

namespace ListProcessing::Operators::Details
{

  class IsAtBack : public Static_curried<IsAtBack,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.isAtBack();
    }
  } constexpr isAtBack{};

  class IsAtFront : public Static_curried<IsAtFront,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.isAtFront();
    }
  } constexpr isAtFront{};

  class Insert : public Static_curried<Insert,Nat<2>>{
  public:
    template<typename V, typename T>
    static constexpr auto
    call(V&& x, T&& xs){
      return xs.insert(forward<V>(x));
    }
  } constexpr insert{};

  class Erase : public Static_curried<Erase,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.erase();
    }
  } constexpr erase{};

  class Write : public Static_curried<Write,Nat<2>>{
  public:
    template<typename V, typename T>
    static constexpr auto
    call(V&& x, T&& xs){
      return xs.write(forward<V>(x));
    }
  } constexpr write{};

  class Read : public Static_curried<Read,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.read();
    }
  } constexpr read{};

  class Position : public Static_curried<Position,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.position();
    }
  } constexpr position{};

  class Remaining : public Static_curried<Remaining,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.remaining();
    }
  } constexpr remaining{};

  class Fwd : public Static_curried<Fwd,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.fwd();
    }
  } constexpr fwd{};

  class Bwd : public Static_curried<Bwd,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.bwd();
    }
  } constexpr bwd{};

  class MoveBy : public Static_curried<MoveBy,Nat<2>>{
  public:
    template<typename I, typename T>
    static constexpr auto
    call(I&& offset, T&& xs){
      return xs.moveBy(offset);
    }
  } constexpr moveBy{};

  class MoveTo : public Static_curried<MoveTo,Nat<2>>{
  public:
    template<typename I, typename T>
    static constexpr auto
    call(I&& index, T&& xs){
      return xs.moveBy(index);
    }
  } constexpr moveTo{};

  class ToFront : public Static_curried<ToFront,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.toFront();
    }
  } constexpr toFront{};

  class ToBack : public Static_curried<ToBack,Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return xs.toBack();
    }
  } constexpr toBack{};

  class Splice : public Static_curried<Splice,Nat<2>>{
  public:
    template<typename T, typename U>
    static constexpr auto
    call(T&& xs, U&& ys){
      return xs.splice(ys);
    }
  } constexpr splice{};

} // end of namespace ListProcessing::Operators::Details
