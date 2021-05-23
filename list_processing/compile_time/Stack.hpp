#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T>
  class Stack;

  template<typename T, typename U>
  Stack(Cell<T, U> const& xs) -> Stack<Cell<T, U>>;

  class ListToStack : public Static_curried<ListToStack, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs) {
      return Stack(forward<T>(xs));
    }
  } constexpr listToStack{};

  template<>
  class Stack<Nothing> {
    using DataType = Nothing;

  public:
    constexpr Stack(){};
    constexpr Stack(Nothing const&){};

  private:
    DataType data;

  public:
    template<typename T>
    constexpr auto
    push(T const& x) const {
      return listToStack(cons(x, nothing));
    }

    template<typename T>
    friend constexpr Stack<Cell<T, Nothing>>
    push(T const& x, Stack const& xs) {
      return xs.push(x);
    }

    constexpr bool
    isEmpty() const {
      return true;
    }

    friend constexpr bool
    isEmpty(Stack const& xs) {
      return xs.isEmpty();
    }

    constexpr Stack
    pop() const {
      return *this;
    }

    friend constexpr Stack
    pop(Stack const& xs) {
      return xs.pop();
    }

    constexpr auto
    pop2() const {
      return *this;
    }

    friend constexpr auto
    pop2(Stack const& xs) {
      return xs.pop2();
    }

    constexpr auto
    pop3() const {
      return *this;
    }

    friend constexpr auto
    pop3(Stack const& xs) {
      return xs.pop3();
    }

    friend constexpr bool
    operator==(Stack const&, Stack const&) {
      return true;
    }

    template<typename T>
    friend constexpr bool
    operator==(Stack const&, T const&) {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator==(T const&, Stack const&) {
      return false;
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Stack const&) {
      os << "#stack()";
      return os;
    }

    friend ostream&
    operator<<(ostream& os, Stack const&) {
      os << "#stack()";
      return os;
    }
  };

  constexpr Stack<Nothing> empty_stack{};

  template<typename T, typename U>
  class Stack<Cell<T, U>> {
    static_assert(isListType(type<U>));

  public:
    using Data    = Cell<T, U>;
    using TopType = T;
    using PopType = U;

    constexpr Stack(Data const& xs)
      : data(xs) {}

  private:
    Data data;

  public:
    template<typename V>
    constexpr Stack<Cell<V, Data>>
    push(V const& x) const {
      return { cons(x, data) };
    }

    template<typename V>
    friend constexpr Stack<Cell<V, Data>>
    push(V const& x, Stack const& xs) {
      xs.push(x);
    }

    constexpr bool
    isEmpty() const {
      return false;
    }

    friend constexpr bool
    isEmpty(Stack const& xs) {
      return xs.isEmpty();
    }

    constexpr TopType
    top() const {
      return head(data);
    }

    friend constexpr TopType
    top(Stack const& xs) {
      return xs.top();
    }

    constexpr Stack<PopType>
    pop() const {
      return { tail(data) };
    }

    friend constexpr Stack<PopType>
    pop(Stack const& xs) {
      return xs.pop();
    }

    constexpr auto
    pop2() const {
      return pop().pop();
    }

    friend constexpr auto
    pop2(Stack const& xs) {
      return xs.pop2();
    }

    constexpr auto
    pop3() const {
      return pop2().pop();
    }

    friend constexpr auto
    pop3(Stack const& xs) {
      return xs.pop();
    }

    constexpr auto
    dup() const {
      return push(top());
    }

    friend constexpr auto
    dup(Stack const& xs) {
      return xs.dup();
    }

    constexpr auto
    swap() const {
      return pop2().push(top()).push(pop().top());
    }

    friend constexpr auto
    swap(Stack const& xs) {
      return xs.swap();
    }

    constexpr auto
    nip() const {
      return pop2().push(top());
    }

    friend constexpr auto
    nip(Stack const& xs) {
      return xs.nip();
    }

    constexpr auto
    tuck() const {
      return pop2().push(top()).push(pop().top()).push(top());
    }

    friend constexpr auto
    tuck(Stack const& xs) {
      return xs.tuck();
    }

    constexpr auto
    over() const {
      return push(pop().top());
    }

    friend constexpr auto
    over(Stack const& xs) {
      return xs.over();
    }

    constexpr auto
    rot() const {
      return pop3().push(pop().top()).push(top()).push(pop2().top());
    }

    friend constexpr auto
    rot(Stack xs) {
      return xs.rot();
    }

    friend constexpr bool
    operator==(Stack const& xs, Stack const& ys) {
      return xs.top() == ys.top() && xs.pop() == ys.pop();
    }

    template<typename V>
    friend constexpr bool
    operator==(Stack const&, V const&) {
      return false;
    }

    template<typename V>
    friend constexpr bool
    operator==(V const&, Stack const&) {
      return false;
    }

    friend constexpr bool
    operator==(Stack const&, Stack<Nothing> const&) {
      return false;
    }

    friend constexpr bool
    operator==(Stack<Nothing> const&, Stack const&) {
      return false;
    }

    template<typename V>
    friend constexpr bool
    operator!=(Stack const& xs, V const& ys) {
      return !(xs == ys);
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Stack const& xs) {
      os << "#Stack(" << xs.top() << " ...)";
      return os;
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Stack const& xs) {
      os << "#Stack(" << xs.top() << " ...)";
      return os;
    }
  };

  template<typename T, typename... Ts>
  constexpr auto
  make_stack(T const& x, Ts const&... xs) {
    return Stack(list(x, xs...));
  }

} // end of namespace ListProcessing::CompileTime::Details
