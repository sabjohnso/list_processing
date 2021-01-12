#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details
{

  template<typename D, typename C>
  class Tape;

  template<typename D, typename C>
  Tape<D, C>
  constructTape(D const& data, C const& context);

  template<typename D, typename C>
  class Tape
  {
  public:
    using Data = D;
    using Context = C;

    static_assert(isListType(type<Data>));
    static_assert(isListType(type<Context>));

    constexpr Tape(Data const& d, Context const& c)
      : data(d)
      , context(c)
    {}

  private:
    Data data;
    Context context;

    friend constexpr bool
    isEmpty(Tape const& xs)
    {
      return isNull(xs.data) && isNull(xs.context);
    }

    template<typename V>
    friend constexpr auto
    insert(Tape const& xs, V const& x)
    {
      return constructTape(cons(x, xs.data), xs.context);
    }

    friend constexpr auto
    remove(Tape const& xs)
    {
      return constructTape(tail(xs.data), xs.context);
    }

    template<typename V>
    friend constexpr auto
    write(Tape const& xs, V const& x)
    {
      return insert(xs, x);
    }

    friend constexpr auto
    read(Tape const& xs)
    {
      return head(xs.data);
    }

    friend constexpr index_type
    position(Tape const&)
    {
      return length_(type<C>);
    }

    friend constexpr size_type
    remaining(Tape const&)
    {
      return length_(type<D>);
    }

    friend constexpr size_type
    length(Tape const&)
    {
      return length_(type<C>) + length_(type<D>);
    }

    friend constexpr bool
    isAtFront(Tape const&)
    {
      return length_(type<C>) == 0;
    }

    friend constexpr bool
    isAtBack(Tape const&)
    {
      return length_(type<D>) == 0;
    }

    friend constexpr auto
    fwd(Tape const& xs)
    {
      if constexpr (length_(type<D>) == 0) {
        return xs;
      } else {
        return constructTape(
          tail(xs.data), cons(head(xs.data), xs.context));
      }
    }

    friend constexpr auto
    bwd(Tape const& xs)
    {
      if constexpr (length_(type<C>) == 0) {
        return xs;
      } else {
        return constructTape(
          cons(head(xs.context), xs.data), tail(xs.context));
      }
    }

    template<offset_type N>
    friend constexpr auto
    moveBy(Tape const& xs, integral_constant<offset_type, N>)
    {
      if constexpr (N > 0) {
        return moveBy(fwd(xs), integral_constant<offset_type, N - 1>{});
      } else if constexpr (N < 0) {
        return moveBy(bwd(xs), integral_constant<offset_type, N + 1>{});
      } else {
        return xs;
      }
    }

    template<offset_type N>
    friend constexpr auto
    moveBy(Tape const& xs)
    {
      if constexpr (N > 0) {
        return moveBy(fwd(xs), integral_constant<offset_type, N - 1>{});
      } else if constexpr (N < 0) {
        return moveBy(bwd(xs), integral_constant<offset_type, N + 1>{});
      } else {
        return xs;
      }
    }

    template<index_type N>
    friend constexpr auto
    moveTo(Tape const& xs, integral_constant<index_type, N>)
    {
      return moveBy(
        xs, integral_constant<offset_type, N - length_(type<C>)>{});
    }

    template<index_type N>
    friend constexpr auto
    moveTo(Tape const& xs)
    {
      return moveTo(xs, integral_constant<index_type, N>{});
    }

    friend constexpr auto
    toFront(Tape const& xs)
    {
      return moveTo(xs, integral_constant<index_type, 0>{});
    }

    friend constexpr auto
    toBack(Tape const& xs)
    {
      return moveTo(
        xs,
        integral_constant<
          index_type,
          length_(type<C>) + length_(type<D>)>{});
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Tape const& xs)
    {
      if constexpr (length_(type<D>) == 0 && length_(type<C>) == 0) {
        os << "#Tape()";
      } else if constexpr (length_(type<C>) == 0) {
        os << "#Zippper(" << read(xs) << ", ...)";
      } else if constexpr (length_(type<D>) == 0) {
        os << "#Tape(..., nil)";
      } else {
        os << "#Tape(..., " << read(xs) << ", ...)";
      }
      return os;
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Tape const& xs)
    {
      if constexpr (length_(type<D>) == 0 && length_(type<C>) == 0) {
        os << "#Tape()";
      } else if constexpr (length_(type<C>) == 0) {
        os << "#Zippper(" << read(xs) << ", ...)";
      } else if constexpr (length_(type<D>) == 0) {
        os << "#Tape(..., nil)";
      } else {
        os << "#Tape(..., " << read(xs) << ", ...)";
      }
      return os;
    }
  };

  template<typename T>
  struct IsTape
    : conditional_t<
        is_same_v<T, decay_t<T>>,
        false_type,
        IsTape<decay_t<T>>>
  {};

  template<typename D, typename C>
  struct IsTape<Tape<D, C>> : true_type
  {};

  template<typename D, typename C>
  Tape(D const& data, C const& context) -> Tape<D, C>;

  constexpr Tape<Nothing, Nothing> empty_tape{ nil, nil };

  template<typename D, typename C>
  Tape<D, C>
  constructTape(D const& data, C const& context)
  {
    return Tape<D, C>(data, context);
  }

  template<typename T, typename... Ts>
  constexpr auto
  makeTape(T const& x, Ts const&... xs)
  {
    return Tape(list(x, xs...), nil);
  }

} // end of namespace ListProcessing::CompileTime::Details
