#pragma once

//
// ... List Processing header files
//
// #include <list_processing/dynamic/Chunk.hpp>
#include <list_processing/dynamic/ListFwd.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename L, typename T>
  class ListOperators
  {
  public:
    // clang-format off
    constexpr
    operator L const &() const&
    {
      return static_cast<L const&>(*this);
    }

    constexpr
    operator L&&() &&
    {
      return static_cast<L&&>(*this);
    }

    operator L&() &
    {
      return static_cast<L&>(*this);
    }
    // clang-format on

    friend bool
    isNull(ListOperators const& xs)
    {
      return !hasData(xs);
    }

    friend bool
    operator==(ListOperators const& xs, ListOperators const& ys)
    {
      return hasData(xs) && hasData(ys)
               ? head(xs) == head(ys) && tail(xs) == tail(ys)
               : (isNull(xs) && isNull(ys) ? true : false);
    }

    friend bool
    operator!=(ListOperators const& xs, ListOperators const& ys)
    {
      return !(xs == ys);
    }

    static size_type
    lengthAux(L const& xs, size_type accum)
    {
      return isNull(xs) ? accum : lengthAux(tail(xs), accum + 1);
    }

    friend size_type
    length(ListOperators const& xs)
    {
      return lengthAux(xs, 0);
    }

    static L
    consAux(T const& x, L const& xs)
    {
      return L(x, xs);
    }

    friend L
    cons(T const& x, ListOperators const& xs)
    {
      return consAux(x, xs);
    }

    static L
    rappendAux(L xs, L ys)
    {
      return isNull(xs) ? ys : rappendAux(tail(xs), cons(head(xs), ys));
    }

    friend L
    rappend(ListOperators const& xs, ListOperators const& ys)
    {
      return rappendAux(xs, ys);
    }

    friend L
    reverse(ListOperators const& xs)
    {
      return rappend(xs, L::nil);
    }

    friend L
    append(ListOperators const& xs, ListOperators const& ys)
    {
      return rappend(reverse(xs), ys);
    }

    static L
    takeAux(L const& xs, size_type n, L const& accum)
    {
      return hasData(xs) && n > 0
               ? takeAux(tail(xs), n - 1, cons(head(xs), accum))
               : reverse(accum);
    }

    friend L
    take(ListOperators const& xs, size_type n)
    {
      return takeAux(xs, n, L::nil);
    }

    friend L
    dropAux(L xs, size_type n)
    {
      return hasData(xs) && n > 0 ? dropAux(tail(xs), n - 1) : xs;
    }

    friend L
    drop(ListOperators const& xs, size_type n)
    {
      return dropAux(xs, n);
    }

    template<typename F, typename U>
    static U
    foldLAux(F f, U const& init, L xs)
    {
      return hasData(xs) ? foldLAux(f, f(init, head(xs)), tail(xs))
                         : init;
    }

    template<typename F, typename U>
    friend auto
    foldL(F f, U const& init, ListOperators const& xs)
    {
      return foldLAux(f, init, xs);
    }

    template<typename F, typename U>
    static U
    foldRAux(F f, L xs, U const& init)
    {
      return hasData(xs) ? foldRAux(f, tail(xs), f(init, head(xs)))
                         : init;
    }

    template<typename F, typename U>
    friend auto
    foldR(F f, ListOperators const& xs, U const& init)
    {
      return foldRAux(f, xs, init);
    }

    template<typename F, typename Accum>
    friend Accum
    fMapAux(F f, L xs, Accum accum)
    {
      return hasData(xs)
               ? fMapAux(f, tail(xs), cons(f(head(xs)), accum))
               : reverse(accum);
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    friend auto
    fMap(F f, ListOperators const& xs)
    {
      return fMapAux(f, xs, List<U>::nil);
    }
  }; // end of class ListOperators

} // end of namespace ListProcessing::Dynamic::Details
