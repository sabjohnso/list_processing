#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/dynamic/List1.hpp>
#include <list_processing/dynamic/ListFwd.hpp>
#include <list_processing/dynamic/ShortList.hpp>

namespace ListProcessing::Dynamic::Details {

  /**
   * @brief Optimized specialization of the List class template
   *
   * @details This specialization of the List class template
   * implements an improvement in memory utilization for small
   * list element types.
   */
  template<typename T, size_type N>
  class List
  {
  public:
    using value_type = T;
    using const_reference = value_type const&;
    using Datum = ShortList<T, N>;
    using Data = List<Datum, 1>;
    static constexpr size_type chunk_size = N;

  private:
    Data data;

  public:
    List()
      : data(Data::nil)
    {}

    List(Nil)
      : data(Data::nil)
    {}

    List(const_reference x, List const& xs)
      : data(
          xs.data.isNull() || isFull(xs.data.head())
            ? cons(Datum(x), xs.data)
            : cons(cons(x, xs.data.head()), xs.data.tail()))
    {}

    List(Data input_data)
      : data(input_data)
    {}

    inline static const List nil = List();

    bool
    hasData() const
    {
      return data.hasData();
    }

    friend bool
    hasData(List xs)
    {
      return xs.hasData();
    }

    bool
    isEmpty() const
    {
      return !hasData();
    }

    friend bool
    isEmpty(List xs)
    {
      return xs.isEmpty();
    }

    bool
    isNull() const
    {
      return !hasData();
    }

    friend bool
    isNull(List xs)
    {
      return xs.isNull();
    }

    const value_type&
    getHead() const
    {
      return data.getHead().getHead();
    }

    const value_type&
    head() const
    {
      return data.head().head();
    }

    friend value_type
    head(List xs)
    {
      return xs.head();
    }

    List
    tail() const
    {
      return hasData() ? (data.head().length() == 1
                            ? List(data.tail())
                            : List(cons(data.head().tail(), data.tail())))
                       : nil;
    }

    friend List
    tail(List xs)
    {
      return xs.hasData()
               ? (xs.data.head().length() == 1
                    ? List(xs.data.tail())
                    : List(cons(xs.data.head().tail(), xs.data.tail())))
               : nil;
    }

    size_type
    length() const
    {
      return foldL(
        [](auto accum, auto chunk) { return accum + chunk.length(); }, 0, data);
    }

    friend size_type
    length(List xs)
    {
      return xs.length();
    }

    friend List
    cons(const_reference x, List xs)
    {
      return List(x, xs);
    }

    template<typename F>
    static Trampoline<List>
    buildList(F f, size_type n, List xs)
    {
      return n > 0 ? Trampoline<List>(
                       [=] { return buildList(f, n - 1, cons(f(n - 1), xs)); })
                   : Trampoline<List>(xs);
    }

    template<typename F>
    friend List
    buildListAux(F f, size_type n, List xs)
    {
      struct Aux
      {
        Trampoline<List>
        run(F f, size_type n, List xs) const
        {
          return n > 0 ? Trampoline<List>([=, this] {
            return run(f, n - 1, cons(f(n - 1), xs));
          })
                       : Trampoline<List>(xs);
        }
      } constexpr aux{};
      return List(aux.run(f, n, xs));
    }

    friend List
    drop(List xs, size_type n)
    {
      using tramp = Trampoline<List>;
      struct Aux
      {
        tramp
        run(List xs, size_type n) const
        {
          return xs.hasData() && n > 0
                   ? tramp([=, this] { return run(xs.tail(), n - 1); })
                   : tramp(xs);
        }
      } constexpr aux{};
      return List(aux.run(xs, n));
    }

    friend List
    take(List xs, size_type n)
    {
      using tramp = Trampoline<List>;
      struct Aux
      {
        tramp
        run(List xs, size_type n, List accum) const
        {
          return xs.hasData() && n > 0 ? tramp([=, this] {
            return run(xs.tail(), n - 1, cons(xs.head(), accum));
          })
                                       : tramp(reverse(accum));
        }
      } constexpr aux{};
      return List(aux.run(xs, n, nil));
    }

    friend value_type
    listRef(List xs, index_type index)
    {
      return drop(xs, index).head();
    }

    friend bool
    operator==(List xs, List ys)
    {
      using tramp = Trampoline<bool>;
      struct Aux
      {
        tramp
        run(List xs, List ys) const
        {
          return xs.hasData() && ys.hasData()
                   ? (xs.head() == ys.head()
                        ? tramp([=, this] { return run(xs.tail(), ys.tail()); })
                        : tramp(false))
                   : tramp(xs.isNull() && ys.isNull() ? true : false);
        }
      } constexpr aux{};
      return xs.length() == ys.length() ? bool(aux.run(xs, ys)) : false;
    }

    template<typename U>
    friend bool
    operator!=(List xs, U ys)
    {
      return !(xs == ys);
    }

    template<size_type M>
    friend bool
    operator==(List xs, List<T, M> ys)
    {
      static_assert(M < N);
      using tramp = Trampoline<bool>;
      struct Aux
      {
        tramp
        run(List xs, List<T, M> ys) const
        {
          return xs.hasData() && ys.hasData()
                   ? (xs.head() == ys.head()
                        ? tramp([=, this] { return run(xs.tail(), ys.tail()); })
                        : tramp(false))
                   : tramp((xs.isNull() && ys.isNull() ? true : false));
        }
      } constexpr aux{};
      return xs.length() == ys.length() ? bool(aux.run(xs, ys)) : false;
    }

    friend List
    rappend(List xs, List ys)
    {
      struct Aux
      {
        Trampoline<List>
        run(List xs, List ys) const
        {
          return xs.hasData() ? Trampoline<List>([=, this] {
            return run(xs.tail(), cons(xs.head(), ys));
          })
                              : Trampoline<List>(ys);
        }
      } constexpr aux{};
      return List(aux.run(xs, ys));
    }

    friend List
    reverse(List xs)
    {
      return rappend(xs, nil);
    }

    friend List
    append(List xs, List ys)
    {
      return rappend(reverse(xs), ys);
    }

    template<typename F, typename U>
    friend U
    foldL(F f, U const& init, List xs)
    {
      using tramp = Trampoline<U>;
      struct Aux
      {
        tramp
        run(F f, U init, List xs) const
        {
          return xs.hasData() ? tramp([=, this] {
            return run(f, f(init, xs.head()), xs.tail());
          })
                              : tramp(init);
        }
      } constexpr aux{};
      return U(aux.run(f, init, xs));
    }

    template<typename F, typename U>
    friend U
    foldR(F f, List xs, U init)
    {
      using tramp = Trampoline<U>;
      struct Aux
      {
        tramp
        run(F f, List xs, U init) const
        {
          return xs.hasData() ? tramp([=, this] {
            return run(f, xs.tail(), f(xs.head(), init));
          })
                              : tramp(init);
        }
      } constexpr aux{};
      return U(aux.run(f, reverse(xs), init));
    }

    template<typename F, typename Result>
    static Result
    rMap(F f, List xs, Result accum)
    {
      using tramp = Trampoline<Result>;
      struct Aux
      {
        tramp
        run(F f, List xs, Result accum) const
        {
          return xs.hasData() ? tramp([=, this] {
            return run(f, xs.tail(), cons(f(xs.head()), accum));
          })
                              : tramp(accum);
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, accum));
    }

    template<
      typename F,
      typename U = decay_t<result_of_t<F(T)>>,
      typename Result = ListType<U>>
    friend Result
    map(F f, List xs)
    {
      return reverse(rMap(f, xs, Result::nil));
    }

    /**
     * @brief Applicative map of a list of functions over a list
     * of values.
     */
    template<
      typename F,
      size_type M,
      typename Result = ListType<result_of_t<F(value_type)>>>
    friend Result
    aMap(List<F, M> fs, List xs)
    {
      using tramp = Trampoline<Result>;
      struct Aux
      {
        tramp
        run(List<F, M> fs, List xs, Result accum) const
        {
          return fs.hasData() ? tramp([=, this] {
            return run(fs.tail(), xs, Result(rMap(fs.head(), xs, accum)));
          })
                              : tramp(reverse(accum));
        }
      } constexpr aux{};
      return Result(aux.run(fs, xs, Result::nil));
    }

    template<typename F, size_type M, typename Us, typename... Vss>
    friend auto
    aMap(List<F, M> fs, List xs, Us ys, Vss... zss)
    {
      return aMap(aMap(fs, xs), ys, zss...);
    }

    template<typename F>
    friend auto
    mMap(F f, List xs)
    {
      using Result = result_of_t<F(T)>;
      using tramp = Trampoline<Result>;
      struct Aux
      {
        tramp
        run(F f, List xs, Result accum) const
        {
          return xs.hasData() ? tramp([=, this] {
            return run(f, xs.tail(), rappend(f(xs.head()), accum));
          })
                              : tramp(reverse(accum));
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, Result::nil));
    }

    template<typename F>
    friend F
    doList(List xs, F f)
    {
      unique_ptr<List> ptr(make_unique<List>(xs));
      while (!ptr->isNull()) {
        f(ptr->head());
        ptr = make_unique<List>(ptr->tail());
      }
      return f;
    }
  }; // end of class List<T,N>

} // end of namespace ListProcessing::Dynamic::Details
