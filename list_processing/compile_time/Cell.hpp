#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T, typename U>
  class Cell;

  template<typename T, typename U>
  constexpr size_type length_(Type<Cell<T, U>>)
  {
    return 1 + length_(type<U>);
  }

  template<typename T, typename U>
  constexpr bool islist_type(Type<Cell<T, U>>)
  {
    return islist_type(type<U>);
  }

  template<typename T, typename U>
  class Cell : pair<T, U>
  {
  public:
    using HeadType = T;
    using TailType = U;
    using pair<T, U>::pair;

  private:
    friend constexpr auto
    head(Cell const& xs)
    {
      return xs.first;
    }

    friend constexpr auto
    tail(Cell const& xs)
    {
      return xs.second;
    }

    friend constexpr bool
    islist(Cell const&)
    {
      return islist_type(type<TailType>);
    }

    friend constexpr bool
    isnothing(Cell const&)
    {
      return false;
    }

    friend constexpr bool
    ispair(Cell const&)
    {
      return true;
    }

    constexpr bool friend
    operator==(Cell const& xs, Cell const& ys)
    {
      return head(xs) == head(ys) && tail(xs) == tail(ys);
    }

    template<typename V, typename W>
    friend constexpr bool
    operator==(Cell const& xs, Cell<V, W> const& ys)
    {
      return head(xs) == head(ys) && tail(xs) == tail(ys);
    }

    template<typename V,
             typename Check = enable_if_t<!ispair_type(type<V>), void>>
    friend constexpr bool
    operator==(Cell const& xs, V const&)
    {
      return false;
    }

    template<typename V,
             typename Check = enable_if_t<!ispair_type(type<V>), void>>
    friend constexpr bool
    operator==(V const&, Cell const& xs)
    {
      return false;
    }

    friend constexpr bool
    operator==(Cell const& xs, Nothing const&)
    {
      return false;
    }

    friend constexpr bool
    operator==(Nothing const&, Cell const& xs)
    {
      return false;
    }

    friend constexpr bool
    operator!=(Cell const& xs, Nothing const& y)
    {
      return !(xs == y);
    }

    friend constexpr bool
    operator!=(Nothing const& x, Cell const& ys)
    {
      return !(x == ys);
    }

    template<typename V>
    friend constexpr bool
    operator!=(Cell const& xs, V const& y)
    {
      return !(xs == y);
    }

    friend constexpr size_type
    length(Cell const&)
    {
      return length_(type<Cell>);
    }

    template<typename V>
    friend constexpr auto
    rappend(Cell const& xs, V const& ys)
    {
      return rappend(tail(xs), cons(head(xs), ys));
    }

    friend constexpr auto
    reverse(Cell const& xs)
    {
      return rappend(xs, nothing);
    }

    template<typename V>
    friend constexpr auto
    append(Cell const& xs, V const& ys)
    {
      return rappend(reverse(xs), ys);
    }

    friend constexpr auto
    take(Nat<0>, Cell const& xs)
    {
      return nothing;
    }

    template<size_t N>
    friend constexpr auto
    take(Nat<N>, Cell const& xs)
    {
      return cons(head(xs), take(nat<N - 1>, tail(xs)));
    }

    friend constexpr auto
    drop(Nat<0>, Cell const& xs)
    {
      return xs;
    }

    template<size_t N>
    friend constexpr auto
    drop(Nat<N>, Cell const& xs)
    {
      return drop(nat<N - 1>, tail(xs));
    }

    template<typename F, typename V>
    friend constexpr auto
    foldl(F f, V const& init, Cell const& xs)
    {
      return foldl(f, f(init, head(xs)), tail(xs));
    }

    template<typename F, typename V>
    friend constexpr auto
    foldr(F f, V const& init, Cell const& xs)
    {
      return foldl([=](auto x, auto y) { return f(y, x); }, init, reverse(xs));
    }

    template<typename F, typename... Us>
    friend constexpr auto
    app_(F f, Cell const& xs, Us const&... ys)
    {
      return app_(f, tail(xs), ys..., head(xs));
    }

    template<typename F>
    friend constexpr auto
    app(F f, Cell const& xs)
    {
      return app_(f, xs);
    }

  }; // end of class Cell

  template<typename T>
  constexpr bool ispair_type(Type<T>)
  {
    return false;
  }

  template<typename T, typename U>
  constexpr bool ispair_type(Type<Cell<T, U>>)
  {
    return true;
  }

  template<typename T, typename U>
  constexpr auto
  cons(T&& x, U&& y)
  {
    return Cell<decay_t<T>, decay_t<U>>{ forward<T>(x), forward<U>(y) };
  }

  template<typename T, typename... Ts>
  constexpr auto
  list(T&& x, Ts&&... xs)
  {
    return cons(forward<T>(x), list(forward<Ts>(xs)...));
  }

} // end of namespace ListProcessing::CompileTime::Details
