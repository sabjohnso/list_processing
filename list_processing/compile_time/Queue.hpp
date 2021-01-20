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

  public:

    constexpr bool
    isEmpty() const {
      return length_(type<O>) == 0;
    }

    friend constexpr bool
    isEmpty(Queue const& xs)
    {
      return xs.isEmpty();
    }

    constexpr auto
    front() const { return head(output); }

    friend constexpr auto
    front(Queue const& xs)
    {
      return xs.front();
    }


    constexpr auto
    pop() const {
      if constexpr (length_(type<O>) == 0) {
        return constructQueue(nil, nil);
      } else if constexpr (length_(type<O>) == 1) {
        return constructQueue(nil, reverse(input));
      } else {
        return constructQueue(input, tail(output));
      }
    }

    friend constexpr auto
    pop(Queue const& xs)
    {
      return xs.pop();
    }


    template<typename T>
    constexpr auto
    push(T const& x) const {
      if constexpr (length_(type<O>) == 0) {
        return constructQueue(nil, list(x));
      } else {
        return constructQueue(cons(x, input), output);
      }
    }

    template<typename T>
    friend constexpr auto
    push(T const& x, Queue const& xs)
    {
      return xs.push(x);
    }

    constexpr auto
    rot() const {
      return pop().push(front());
    }

    friend constexpr auto
    rot(Queue const& xs)
    {
      return xs.rot();
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Queue const& xs)
    {
      if constexpr (length_(type<O>) == 0) {
        os << "#Queue()";
      } else {
        os << "#Queue(" << xs.front() << ", ...)";
      }
      return os;
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Queue const& xs)
    {
      if constexpr (length_(type<O>) == 0) {
        os << "#Queue()";
      } else {
        os << "#Queue(" << xs.front() << ", ...)";
      }
      return os;
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
