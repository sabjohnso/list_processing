#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename D, typename C>
  class Zipper;

  template<typename D, typename C>
  Zipper<D, C>
  constructZipper(D const& data, C const& context);

  template<typename D, typename C>
  class Zipper {
  public:
    using Data    = D;
    using Context = C;

    static_assert(isListType(type<Data>));
    static_assert(isListType(type<Context>));

    constexpr Zipper(Data const& d, Context const& c)
      : data(d)
      , context(c) {}

  private:
    Data    data;
    Context context;

    friend constexpr bool
    isEmpty(Zipper const& xs) {
      return isNull(xs.data) && isNull(xs.context);
    }

    template<typename V>
    friend constexpr auto
    insert(Zipper const& xs, V const& x) {
      return constructZipper(cons(x, xs.data), xs.context);
    }

    friend constexpr auto
    remove(Zipper const& xs) {
      return constructZipper(tail(xs.data), xs.context);
    }

    template<typename V>
    friend constexpr auto
    write(Zipper const& xs, V const& x) {
      return insert(xs, x);
    }

    friend constexpr auto
    read(Zipper const& xs) {
      return head(xs.data);
    }

    friend constexpr index_type
    position(Zipper const&) {
      return length_(type<C>);
    }

    friend constexpr size_type
    remaining(Zipper const&) {
      return length_(type<D>);
    }

    friend constexpr size_type
    length(Zipper const&) {
      return length_(type<C>) + length_(type<D>);
    }

    friend constexpr bool
    isAtFront(Zipper const&) {
      return length_(type<C>) == 0;
    }

    friend constexpr bool
    isAtBack(Zipper const&) {
      return length_(type<D>) == 0;
    }

    friend constexpr auto
    fwd(Zipper const& xs) {
      if constexpr (length_(type<D>) == 0) {
        return xs;
      } else {
        return constructZipper(tail(xs.data), cons(head(xs.data), xs.context));
      }
    }

    friend constexpr auto
    bwd(Zipper const& xs) {
      if constexpr (length_(type<C>) == 0) {
        return xs;
      } else {
        return constructZipper(
          cons(head(xs.context), xs.data), tail(xs.context));
      }
    }

    template<offset_type N>
    friend constexpr auto
    moveBy(Zipper const& xs, integral_constant<offset_type, N>) {
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
    moveBy(Zipper const& xs) {
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
    moveTo(Zipper const& xs, integral_constant<index_type, N>) {
      return moveBy(xs, integral_constant<offset_type, N - length_(type<C>)>{});
    }

    template<index_type N>
    friend constexpr auto
    moveTo(Zipper const& xs) {
      return moveTo(xs, integral_constant<index_type, N>{});
    }

    friend constexpr auto
    toFront(Zipper const& xs) {
      return moveTo(xs, integral_constant<index_type, 0>{});
    }

    friend constexpr auto
    toBack(Zipper const& xs) {
      return moveTo(
        xs,
        integral_constant<index_type, length_(type<C>) + length_(type<D>)>{});
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Zipper const& xs) {
      if constexpr (length_(type<D>) == 0 && length_(type<C>) == 0) {
        os << "#Zipper()";
      } else if constexpr (length_(type<C>) == 0) {
        os << "#Zippper(" << read(xs) << ", ...)";
      } else if constexpr (length_(type<D>) == 0) {
        os << "#Zipper(..., nil)";
      } else {
        os << "#Zipper(..., " << read(xs) << ", ...)";
      }
      return os;
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Zipper const& xs) {
      if constexpr (length_(type<D>) == 0 && length_(type<C>) == 0) {
        os << "#Zipper()";
      } else if constexpr (length_(type<C>) == 0) {
        os << "#Zippper(" << read(xs) << ", ...)";
      } else if constexpr (length_(type<D>) == 0) {
        os << "#Zipper(..., nil)";
      } else {
        os << "#Zipper(..., " << read(xs) << ", ...)";
      }
      return os;
    }
  };

  template<typename T>
  struct IsZipper
    : conditional_t<
        is_same_v<T, decay_t<T>>,
        false_type,
        IsZipper<decay_t<T>>> {};

  template<typename D, typename C>
  struct IsZipper<Zipper<D, C>> : true_type {};

  template<typename D, typename C>
  Zipper(D const& data, C const& context) -> Zipper<D, C>;

  constexpr Zipper<Nothing, Nothing> empty_zipper{ nil, nil };

  template<typename D, typename C>
  Zipper<D, C>
  constructZipper(D const& data, C const& context) {
    return Zipper<D, C>(data, context);
  }

  template<typename T, typename... Ts>
  constexpr auto
  makeZipper(T const& x, Ts const&... xs) {
    return Zipper(list(x, xs...), nil);
  }

} // end of namespace ListProcessing::CompileTime::Details
