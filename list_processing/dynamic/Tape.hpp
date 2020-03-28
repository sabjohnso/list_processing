#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T>
  class Tape
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Tape()
      : data(nil<value_type>)
      , context(nil<value_type>)
    {}

  private:
    using data_type = List<value_type>;

    Tape(data_type input_data, data_type input_context)
      : data(input_data)
      , context(input_context)
    {}

    data_type data;
    data_type context;

    friend bool
    operator==(Tape xs, Tape ys)
    {
      return xs.data == ys.data && xs.context == ys.context;
    }

    friend bool
    operator!=(Tape xs, Tape ys)
    {
      return !(xs == ys);
    }

    friend bool
    isAtBack(Tape xs)
    {
      return isNull(xs.data);
    }

    friend bool
    isAtFront(Tape xs)
    {
      return isNull(xs.context);
    }

    friend bool
    isEmpty(Tape xs)
    {
      return isAtFront(xs) && isAtBack(xs);
    }

    friend Tape
    insert(Tape xs, const_reference x)
    {
      return Tape(cons(x, xs.data), xs.context);
    }

    friend Tape
    remove(Tape xs)
    {
      return Tape(tail(xs.data), xs.context);
    }

    friend Tape
    write(Tape xs, const_reference x)
    {
      return insert(remove(xs), x);
    }

    friend value_type
    read(Tape xs)
    {
      return head(xs.data);
    }

    friend index_type
    position(Tape xs)
    {
      return length(xs.context);
    }

    friend size_type
    remaining(Tape xs)
    {
      return length(xs.data);
    }

    friend size_type
    length(Tape xs)
    {
      return position(xs) + remaining(xs);
    }

    friend Tape
    fwd(Tape xs)
    {
      return Tape(tail(xs.data), cons(head(xs.data), xs.context));
    }

    friend Tape
    bwd(Tape xs)
    {
      return Tape(cons(head(xs.context), xs.data), tail(xs.context));
    }

    friend Tape
    moveBy(Tape xs, offset_type offset)
    {
      return (offset > 0)
               ? moveBy(fwd(xs), offset - 1)
               : ((offset < 0) ? moveBy(bwd(xs), offset + 1) : xs);
    }

    friend Tape
    moveTo(Tape xs, index_type index)
    {
      return moveBy(xs, index - position(xs));
    }

    friend Tape
    toFront(Tape xs)
    {
      return Tape(rappend(xs.context, xs.data), nil<value_type>);
    }

    friend Tape
    toBack(Tape xs)
    {
      return Tape(nil<value_type>, rappend(xs.data, xs.context));
    }

  }; // end of class Tape

  template<typename T>
  const Tape<T> empty_tape{};

  template<typename T>
  Tape<T>
  tapeOf()
  {
    return empty_tape<T>;
  }

  template<typename T, typename T1, typename... Ts>
  Tape<T>
  tapeOf(T1 const& x, Ts const&... xs)
  {
    return insert(tapeOf<T>(xs...), x);
  }

  template<typename T>
  Tape<T>
  tape(T const& x)
  {
    return tapeOf<T>(x);
  }

  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T = common_type_t<T1, T2, Ts...>>
  Tape<T>
  tape(T1 const& x1, T2 const& x2, Ts const&... xs)
  {
    return tapeOf<T>(x1, x2, xs...);
  }

} // end of namespace ListProcessing::Dynamic::Details
