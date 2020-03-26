#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details
{

  template<typename T>
  constexpr auto
  pipe(T const x)
  {
    return x;
  }

  template<typename T, typename F, typename... Fs>
  constexpr auto
  pipe(T const& x, F f, Fs... fs)
  {
    return pipe(f(x), fs...);
  }

  template<typename T>
  class Stack;

  template<typename T, typename U>
  Stack(Cell<T, U> const& xs) -> Stack<Cell<T, U>>;

  template<>
  class Stack<Nothing>
  {
    using DataType = Nothing;

  public:
    constexpr Stack(){};
    constexpr Stack(Nothing const&){};

  private:
    DataType data;

    template<typename T>
    friend constexpr Stack<Cell<T, Nothing>>
    push(Stack const&, T const& x)
    {
      return Stack<Cell<T, Nothing>>(cons(x, nothing));
    }

    friend constexpr bool
    isEmpty(Stack const&)
    {
      return true;
    }

    friend constexpr Stack
    pop(Stack const& xs)
    {
      return xs;
    }

    friend constexpr auto
    drop(Stack const& xs)
    {
      return xs;
    }

    friend constexpr auto
    drop2(Stack const& xs)
    {
      return xs;
    }

    friend constexpr auto
    drop3(Stack const& xs)
    {
      return xs;
    }

    friend constexpr bool
    operator==(Stack const&, Stack const&)
    {
      return true;
    }

    template<typename T>
    friend constexpr bool
    operator==(Stack const&, T const&)
    {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator==(T const&, Stack const&)
    {
      return false;
    }
  };

  constexpr Stack<Nothing> empty_stack{};

  template<typename T, typename U>
  class Stack<Cell<T, U>>
  {
    static_assert(isListType(type<U>));

  public:
    using Data = Cell<T, U>;
    using TopType = T;
    using PopType = U;

    constexpr Stack(Data const& xs)
      : data(xs)
    {}

  private:
    Data data;

    template<typename V>
    friend constexpr Stack<Cell<V, Data>>
    push(Stack const& xs, V const& x)
    {
      return Stack<Cell<V, Data>>(cons(x, xs.data));
    }

    friend constexpr bool
    isEmpty(Stack const&)
    {
      return false;
    }

    friend constexpr TopType
    top(Stack const& xs)
    {
      return head(xs.data);
    }

    friend constexpr Stack<PopType>
    pop(Stack const& xs)
    {
      return Stack<PopType>(tail(xs.data));
    }

    friend constexpr auto
    drop(Stack const& xs)
    {
      return pop(xs);
    }

    friend constexpr auto
    drop2(Stack const& xs)
    {
      return drop(drop(xs));
    }

    friend constexpr auto
    drop3(Stack const& xs)
    {
      return drop(drop2(xs));
    }

    friend constexpr auto
    dup(Stack const& xs)
    {
      return push(xs, top(xs));
    }

    friend constexpr auto
    swap(Stack const& xs)
    {
      return pipe(
        drop2(xs),
        [=](auto ys) { return push(ys, top(xs)); },
        [=](auto ys) { return push(ys, top(pop(xs))); });
    }

    friend constexpr auto
    nip(Stack const& xs)
    {
      return push(drop2(xs), top(xs));
    }

    friend constexpr auto
    tuck(Stack const& xs)
    {
      return pipe(
        drop2(xs),
        [=](auto ys) { return push(ys, top(xs)); },
        [=](auto ys) { return push(ys, top(drop(xs))); },
        [=](auto ys) { return push(ys, top(xs)); });
    }

    friend constexpr auto
    over(Stack const& xs)
    {
      return push(xs, top(drop(xs)));
    }

    friend constexpr auto
    rot(Stack xs)
    {
      return pipe(
        drop3(xs),
        [=](auto ys) { return push(ys, top(drop(xs))); },
        [=](auto ys) { return push(ys, top(xs)); },
        [=](auto ys) { return push(ys, top(drop2(xs))); });
    }

    friend constexpr bool
    operator==(Stack const& xs, Stack const& ys)
    {
      return top(xs) == top(ys) && pop(xs) == pop(ys);
    }

    template<typename V>
    friend constexpr bool
    operator==(Stack const&, V const&)
    {
      return false;
    }

    template<typename V>
    friend constexpr bool
    operator==(V const&, Stack const&)
    {
      return false;
    }

    friend constexpr bool
    operator==(Stack const&, Stack<Nothing> const&)
    {
      return false;
    }

    friend constexpr bool
    operator==(Stack<Nothing> const&, Stack const&)
    {
      return false;
    }

    template<typename V>
    friend constexpr bool
    operator!=(Stack const& xs, V const& ys)
    {
      return !(xs == ys);
    }
  };

  template<typename T, typename... Ts>
  constexpr auto
  make_stack(T const& x, Ts const&... xs)
  {
    return Stack(list(x, xs...));
  }

} // end of namespace ListProcessing::CompileTime::Details
