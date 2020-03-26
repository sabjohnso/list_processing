#pragma once

namespace ListProcessing::CompileTime::Details
{
  template<typename I, typename O>
  class Queue
  {
  public:
    using InputType = I;
    using OutputType = O;

    friend constexpr bool
    isEmpty(Queue const&)
    {
      return type<I> == type<Nothing> && type<O> == type<Nothing>;
    }

    friend constexpr auto
    top(Queue const& xs)
    {
      return head(xs.output);
    }
  };
} // end of namespace ListProcessing::CompileTime::Details
