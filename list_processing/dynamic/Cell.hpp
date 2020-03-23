#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{

  template<typename T>
  class Cell
  {
  public:
    using value_type = T;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    Cell()
      : ptr(nullptr)
    {}

    Cell(const_reference x, Cell const& xs)
      : ptr(make_shared<Kernel>(x, xs))
    {}

  private:
    struct Kernel
    {
      Kernel(const_reference x, Cell const& xs)
        : head(x)
        , tail(xs)
      {}

      Kernel(Kernel const&) = delete;

      Kernel(Kernel&& xs)
        : head(move(xs.head))
        , tail(move(xs.tail))
      {}

      value_type head;
      Cell tail;
    }; // end of class Kernel

    using KernelPointer = shared_ptr<const Kernel>;

    KernelPointer ptr;

    friend bool
    hasdata(Cell xs)
    {
      return bool(xs.ptr);
    }

    friend bool
    isnothing(Cell xs)
    {
      return !hasdata(xs);
    }

    friend auto
    cons(const_reference x, Cell xs)
    {
      return Cell(x, xs);
    }

    friend auto
    head(Cell xs)
    {
      return hasdata(xs) ? xs.ptr->head : throw logic_error("empty list has no head");
    }

    friend auto
    tail(Cell xs)
    {
      return hasdata(xs) ? xs.ptr->tail : xs;
    }

    static size_type
    length_aux(Cell xs, size_type accum)
    {
      return hasdata(xs) ? length_aux(tail(xs), accum + 1) : accum;
    }

    friend size_type
    length(Cell xs)
    {
      return length_aux(xs, 0);
    }

    friend bool
    operator==(Cell xs, Cell ys)
    {
      return isnothing(xs) && isnothing(ys)
               ? true
               : (hasdata(xs) && hasdata(ys) ? (head(xs) == head(ys) && tail(xs) == tail(ys))
                                             : false);
    }

    friend Cell
    rappend(Cell xs, Cell ys)
    {
      return hasdata(xs) ? rappend(tail(xs), cons(head(xs), ys)) : ys;
    }

    friend Cell
    reverse(Cell xs)
    {
      return rappend(xs, Cell());
    }

    friend Cell
    append(Cell xs, Cell ys)
    {
      return rappend(reverse(xs), ys);
    }

    friend Cell
    drop(Cell xs, size_type n)
    {
      return (hasdata(xs) && n) > 0 ? drop(tail(xs), n - 1) : xs;
    }

    static Cell
    take_aux(Cell xs, size_type n, Cell accum)
    {
      return hasdata(xs) && n > 0 ? take_aux(tail(xs), n - 1, cons(head(xs), accum))
                                  : reverse(accum);
    }

    friend Cell
    take(Cell xs, size_type n)
    {
      return take_aux(xs, n, Cell());
    }

    template<typename F, typename Accum, typename... Us>
    static Accum
    map_aux(Accum accum, F f, Cell xs, Us... yss)
    {
      return hasdata(xs)
               ? map_aux(cons(f(head(xs), head(yss)...), accum), f, tail(xs), tail(yss)...)
               : reverse(accum);
    }

    template<typename F, typename... Us>
    friend auto
    map(F f, Cell xs, Us... yss)
    {
      using R = decay_t<result_of_t<F(T, typename Us::value_type...)>>;
      return map_aux(Cell<R>{}, f, xs, yss...);
    }

    template<typename F, typename U>
    friend U
    foldl(F f, U const& init, Cell xs)
    {
      return hasdata(xs) ? foldl(f, f(init, head(xs)), tail(xs)) : init;
    }

    template<typename F, typename U>
    friend U
    foldr(F f, Cell xs, U const& init)
    {
      return hasdata(xs) ? foldr(f, tail(xs), f(head(xs), init)) : init;
    }

    static value_type
    listref_aux(Cell xs, index_type index)
    {
      return index > 0 ? listref_aux(tail(xs), index - 1) : head(xs);
    }

    friend auto
    listref(Cell xs, index_type index)
    {
      return index >= 0 && index < length(xs)
               ? listref_aux(xs, index)
               : throw logic_error("listref called with invalid index:" + to_string(index));
    }

    template<typename F, typename... Us>
    static auto
    app_aux(F f, Nat<0>, Cell, Us... ys)
    {
      return f(ys...);
    }

    template<typename F, size_t N, typename... Us>
    static auto
    app_aux(F f, Nat<N>, Cell xs, Us... ys)
    {
      return app_aux(f, nat<N - 1>, tail(xs), ys..., head(xs));
    }

    template<typename F, size_t N>
    friend auto
    app(F f, Nat<N>, Cell xs)
    {
      return app_aux(f, nat<N>, xs);
    }

  }; // end of class Cell

  template<typename T>
  const Cell<T> nothing{};

  template<typename T>
  auto
  listof()
  {
    return nothing<T>;
  }

  template<typename T>
  auto
  list(T const& x)
  {
    return cons(x, nothing<T>);
  }

  template<typename T, typename T1, typename... Ts>
  auto
  listof(T1 const& x, Ts const&... xs)
  {
    return cons(x, listof<T>(xs...));
  }

  template<typename T1, typename T2, typename... Ts>
  auto
  list(T1 const& x1, T2 const& x2, Ts const&... xs)
  {
    return listof<common_type_t<T1, T2, Ts...>>(x1, x2, xs...);
  }

} // end of namespace ListProcessing::Dynamic::Details
