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

  public:

    constexpr bool
    isEmpty() const {
      return isNull(data) && isNull(context);
    }

    friend constexpr bool
    isEmpty(Tape const& xs)
    {
      return xs.isEmpty();
    }

    template<typename V>
    constexpr auto
    insert(V const& x) const {
      return constructTape(cons(x, data), context);
    }

    template<typename V>
    friend constexpr auto
    insert(Tape const& xs, V const& x)
    {
      return xs.insert(x);
    }

    constexpr auto
    erase() const { return constructTape(tail(data), context); }

    friend constexpr auto
    erase(Tape const& xs)
    {
      return xs.erase();
    }

    template<typename V>
    constexpr auto
    write(V const& x) const {
      return erase().insert(x);
    }

    template<typename V>
    friend constexpr auto
    write(Tape const& xs, V const& x)
    {
      return xs.write(x);
    }

    constexpr auto
    read() const { return head(data); }

    friend constexpr auto
    read(Tape const& xs)
    {
      return xs.read();
    }

    constexpr index_type
    position() const { return length_(type<C>); }

    friend constexpr index_type
    position(Tape const& xs)
    {
      return xs.position();
    }

    constexpr size_type
    remaining() const { return length_(type<D>); }


    friend constexpr size_type
    remaining(Tape const& xs)
    {
      return xs.remaining();
    }

    constexpr size_type
    length(Tape const&) const
    {
      return length_(type<C>) + length_(type<D>);
    }

    friend constexpr size_type
    length(Tape const& xs)
    {
      return xs.length();
    }

    constexpr bool
    isAtFront() const
    {
      return length_(type<C>) == 0;
    }

    friend constexpr bool
    isAtFront(Tape const& xs)
    {
      return xs.isAtFront();
    }

    constexpr bool
    isAtBack() const {
      return length_(type<D>) == 0;
    }

    friend constexpr bool
    isAtBack(Tape const& xs)
    {
      return xs.isAtBack();
    }

    constexpr auto
    fwd() const {
      if constexpr (length_(type<D>) == 0) {
        return *this;
      } else {
        return constructTape(
          tail(data), cons(head(data), context));
      }
    }

    friend constexpr auto
    fwd(Tape const& xs)
    {
      return xs.fwd();
    }


    constexpr auto
    bwd() const {
      if constexpr (length_(type<C>) == 0) {
        return *this;
      } else {
        return constructTape(
          cons(head(context), data), tail(context));
      }
    }

    friend constexpr auto
    bwd(Tape const& xs)
    {
      return xs.bwd();
    }

    template<offset_type N>
    constexpr auto
    moveBy(integral_constant<offset_type, N>) const {
      if constexpr (N > 0){
        return fwd().moveBy(integral_constant<offset_type, N - 1>{});
      } else if constexpr (N < 0){
        return bwd().moveBy(integral_constant<offset_type, N + 1>{});
      } else {
        return *this;
      }
    }

    template<offset_type N>
    friend constexpr auto
    moveBy(Tape const& xs, integral_constant<offset_type, N>)
    {
      return xs.moveBy(integral_constant<offset_type, N>{});
    }

    template<index_type N>
    constexpr auto
    moveTo(integral_constant<index_type, N>) const
    {
      return moveBy(integral_constant<offset_type, N - length_(type<C>)>{});
    }

    template<index_type N>
    friend constexpr auto
    moveTo(Tape const& xs, integral_constant<index_type, N>)
    {
      return xs.moveTo(integral_constant<index_type, N>{});
    }

    constexpr auto
    toFront() const {
      return moveTo(integral_constant<index_type, 0>{});
    }


    friend constexpr auto
    toFront(Tape const& xs)
    {
      return xs.toFront();
    }

    constexpr auto
    toBack() const {
      return moveTo(
        integral_constant<
        index_type,
        length_(type<C>) + length_(type<D>)>{});
    }

    friend constexpr auto
    toBack(Tape const& xs)
    {
      return xs.toBack();
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Tape const& xs)
    {
      if constexpr (length_(type<D>) == 0 && length_(type<C>) == 0) {
        os << "#Tape()";
      } else if constexpr (length_(type<C>) == 0) {
        os << "#Tape(" << read(xs) << ", ...)";
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
