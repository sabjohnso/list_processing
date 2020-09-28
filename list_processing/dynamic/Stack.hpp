#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>

namespace ListProcessing::Dynamic::Details
{

  template<typename T>
  constexpr auto
  pipe(T&& x)
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
  constexpr auto
  fanout(T&& x){ return nil<decay_t<T>>; }

  template<typename T, typename F, typename ... Fs>
  constexpr auto
  fanout(T&& x, F&& f, Fs&& ... fs){
    return list(f(x), fs(x) ...);
  }


  template<typename T>
  class Stack
  {

  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Stack()
      : data(nil<value_type>)
    {}

  private:
    using data_type = List<value_type>;

    Stack(data_type xs)
      : data(xs)
    {}

    data_type data;

    friend Stack
    push(Stack xs, const_reference x)
    {
      return Stack(cons(x, xs.data));
    }

    friend bool
    isempty(Stack xs)
    {
      return isNull(xs.data);
    }

    friend value_type
    top(Stack xs)
    {
      return (!isempty(xs)) ? head(xs.data) : throw logic_error("Cannot read top of empty stack");
    }

    friend Stack
    pop(Stack xs)
    {
      return Stack(tail(xs.data));
    }

    friend Stack
    drop(Stack xs)
    {
      return pop(xs);
    }

    friend Stack
    drop2(Stack xs)
    {
      return drop(drop(xs));
    }

    friend Stack
    drop3(Stack xs)
    {
      return drop(drop2(xs));
    }

    friend Stack
    dup(Stack xs)
    {
      return push(xs, top(xs));
    }

    friend Stack
    swap(Stack xs)
    {
      return pipe(
        drop2(xs),
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop(xs))); });
    }

    friend Stack
    nip(Stack xs)
    {
      return push(drop2(xs), top(xs));
    }

    friend Stack
    tuck(Stack xs)
    {
      return pipe(
        drop2(xs),
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop(xs))); },
        [&](auto ys) { return push(ys, top(xs)); });
    }

    friend Stack
    over(Stack xs)
    {
      return push(xs, top(drop(xs)));
    }

    friend Stack
    rot(Stack xs)
    {
      return pipe(
        drop3(xs),
        [&](auto ys) { return push(ys, top(drop(xs))); },
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop2(xs))); });
    }

    friend bool
    operator==(Stack xs, Stack ys)
    {
      return (isempty(xs) && isempty(ys)) ? true
                                          : (((!isempty(xs)) && (!isempty(ys)))
                                               ? (top(xs) == top(ys)) && (drop(xs) == drop(ys))
                                               : false);
    }

    template<typename F>
    friend Stack
    app1(Stack xs, F f)
    {
      return push(drop(xs), f(top(xs)));
    }

    template<typename F>
    friend Stack
    app2(Stack xs, F f)
    {
      return push(drop2(xs), f(top(xs), top(drop(xs))));
    }

    friend bool
    operator!=(Stack xs, Stack ys)
    {
      return !(xs == ys);
    }

  }; // end of class Stack

  template<typename T>
  const Stack<T> empty_stack{};

} // end of namespace ListProcessing::Dynamic::Details
