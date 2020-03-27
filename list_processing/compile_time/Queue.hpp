#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>

namespace ListProcessing::CompileTime::Details
{

  template<typename I, typename O>
  class Queue;

  template<typename T, typename... Ts>
  constexpr auto
  makeQueue(T const& x, Ts const&... xs);

  template<typename I, typename O>
  constexpr Queue<I, O>
  constructQueue(I const& in, O const& out);

  template<typename I, typename O>
  class Queue
  {

    static_assert(
      (length_(type<I>) == 0 && length_(type<O>) == 0) ||
      length_(type<O>) != 0);

  public:
    using InputType = I;
    using OutputType = O;

    constexpr Queue(I const& in, O const& out)
      : input(in)
      , output(out)
    {}

  private:
    InputType input;
    OutputType output;

    friend constexpr bool
    isEmpty(Queue const&)
    {
      return length_(type<O>) == 0;
    }

    friend constexpr auto
    front(Queue const& xs)
    {
      return head(xs.output);
    }

    friend constexpr auto
    pop(Queue const& xs)
    {
      if constexpr (length_(type<O>) == 0) {
        return constructQueue(nil, nil);
      } else if constexpr (length_(type<O>) == 1) {
        return constructQueue(nil, reverse(xs.input));
      } else {
        return constructQueue(xs.input, tail(xs.output));
      }
    }

    template<typename T>
    friend constexpr auto
    push(Queue const& xs, T const& x)
    {
      if constexpr (length_(type<O>) == 0) {
        return constructQueue(nil, list(x));
      } else {
        return constructQueue(cons(x, xs.input), xs.output);
      }
    }

    friend constexpr auto
    rot(Queue const& xs)
    {
      return push(pop(xs), front(xs));
    }
  };

  template<typename I, typename O>
  Queue(I const& input, O const& output) -> Queue<I, O>;

  constexpr Queue<Nothing, Nothing> empty_queue{ nil, nil };

  template<typename I, typename O>
  constexpr Queue<I, O>
  constructQueue(I const& in, O const& out)
  {
    return Queue<I, O>(in, out);
  }

  template<typename T, typename... Ts>
  constexpr auto
  makeQueue(T const& x, Ts const&... xs)
  {
    return Queue(nil, list(x, xs...));
  }

} // end of namespace ListProcessing::CompileTime::Details
