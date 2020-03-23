#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T>
  class Zipper
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Zipper()
      : data(nil<value_type>)
      , context(nil<value_type>)
    {}

  private:
    using data_type = List<value_type>;

    Zipper(data_type input_data, data_type input_context)
      : data(input_data)
      , context(input_context)
    {}

    data_type data;
    data_type context;

    friend bool
    operator==(Zipper xs, Zipper ys)
    {
      return xs.data == ys.data && xs.context == ys.context;
    }

    friend bool
    operator!=(Zipper xs, Zipper ys)
    {
      return !(xs == ys);
    }

    friend bool
    isAtBack(Zipper xs)
    {
      return isNull(xs.data);
    }

    friend bool
    isAtFront(Zipper xs)
    {
      return isNull(xs.context);
    }

    friend bool
    isEmpty(Zipper xs)
    {
      return isAtFront(xs) && isAtBack(xs);
    }

    friend Zipper
    insert(Zipper xs, const_reference x)
    {
      return Zipper(cons(x, xs.data), xs.context);
    }

    friend Zipper
    remove(Zipper xs)
    {
      return Zipper(tail(xs.data), xs.context);
    }

    friend Zipper
    write(Zipper xs, const_reference x)
    {
      return insert(remove(xs), x);
    }

    friend value_type
    read(Zipper xs)
    {
      return head(xs.data);
    }

    friend index_type
    position(Zipper xs)
    {
      return length(xs.context);
    }

    friend size_type
    remaining(Zipper xs)
    {
      return length(xs.data);
    }

    friend size_type
    length(Zipper xs)
    {
      return position(xs) + remaining(xs);
    }

    friend Zipper
    fwd(Zipper xs)
    {
      return Zipper(tail(xs.data), cons(head(xs.data), xs.context));
    }

    friend Zipper
    bwd(Zipper xs)
    {
      return Zipper(cons(head(xs.context), xs.data), tail(xs.context));
    }

    friend Zipper
    moveBy(Zipper xs, offset_type offset)
    {
      return (offset > 0)
               ? moveBy(fwd(xs), offset - 1)
               : ((offset < 0) ? moveBy(bwd(xs), offset + 1) : xs);
    }

    friend Zipper
    moveTo(Zipper xs, index_type index)
    {
      return moveBy(xs, index - position(xs));
    }

    friend Zipper
    toFront(Zipper xs)
    {
      return Zipper(rappend(xs.context, xs.data), nil<value_type>);
    }

    friend Zipper
    toBack(Zipper xs)
    {
      return Zipper(nil<value_type>, rappend(xs.data, xs.context));
    }

  }; // end of class Zipper

  template<typename T>
  const Zipper<T> empty_zipper{};

  template<typename T>
  Zipper<T>
  zipperOf()
  {
    return empty_zipper<T>;
  }

  template<typename T, typename T1, typename... Ts>
  Zipper<T>
  zipperOf(T1 const& x, Ts const&... xs)
  {
    return insert(zipperOf<T>(xs...), x);
  }

  template<typename T>
  Zipper<T>
  zipper(T const& x)
  {
    return zipperOf<T>(x);
  }

  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T = common_type_t<T1, T2, Ts...>>
  Zipper<T>
  zipper(T1 const& x1, T2 const& x2, Ts const&... xs)
  {
    return zipperOf<T>(x1, x2, xs...);
  }

} // end of namespace ListProcessing::Dynamic::Details
