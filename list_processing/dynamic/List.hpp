#pragma once

//
// ... List Processing' header files
//
#include <list_processing/dynamic/ListOperators.hpp>
#include <list_processing/dynamic/ListTraits.hpp>
#include <list_processing/dynamic/ShortList.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T = common_type_t<decay_t<T1>, decay_t<T2>, decay_t<Ts>...>>
  List<T>
  list(T1&& x1, T2&& x2, Ts&&... xs);


  /**
   * @brief A class template describing homogeneous dynamic lists.
   *
   * @details Specializations of this class implement a persistent
   * (functional) list data structure where specializations provide
   * optimizations for some value types but present a uniform interface
   *
   * @tparam T - a type parameter specifying the list element type
   *
   * @tparam N - an integral type parameter specifying the chunk size
   * for the underlying kernel. The chunk size is use to reduce the
   * memory overhead of lists with certain value types.
   */
  template<typename T, size_type N>
  class List;

  /**
   * @brief Reference specialization of the List class template
   */
  template<typename T>
  class List<T, 1> : public ListTraits<T>
  {
  public:
    using value_type = T;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    friend ListOperators<List, T>;

  private:
    List()
      : ptr(nullptr)
    {}

    List(const_reference x, List const& xs)
      : ptr(make_shared<Kernel>(x, xs))
    {}

  private:
    struct Kernel
    {
      Kernel(const_reference x, List const& xs)
        : head(x)
        , tail(xs)
      {}

      Kernel(Kernel&& input)
        : head(move(input.head))
        , tail(move(input.tail))
      {}

      value_type head;
      List tail;
    };

    using kernel_pointer = shared_ptr<const Kernel>;
    kernel_pointer ptr;

    friend List
    cons(const_reference x, List xs)
    {
      return List(x, xs);
    }

    friend bool
    hasData(List xs)
    {
      return bool(xs.ptr);
    }

    friend bool
    isNull(List xs)
    {
      return !hasData(xs);
    }

  public:
    // clang-format off
    List const&
    getTail() const
    {
      return hasData(*this)
        ? ptr->tail
        : *this;
    }
  private:

    friend List
    tail(List xs)
    {
      return hasData(xs) ? xs.ptr->tail : xs;
    }

    static size_type
    lengthAux(List xs, size_type accum){
      return hasData(xs)
        ? lengthAux(tail(xs), accum+1)
        : accum;
    }

    friend size_type
    length(List xs){
      return lengthAux(xs, 0);
    }

  public:
    const_reference
    getHead() const
    {
      return hasData(*this)
        ? ptr->head
        : throw logic_error("Cannot access the head of an empty list");
    }
  private:

    friend value_type
    head(List xs)
    {
      return hasData(xs)
        ? xs.ptr->head
        : throw logic_error("Cannot access the head of an empty list");
    }
    // clang-format on

    friend List
    rappend(List xs, List ys)
    {
      return hasData(xs) ? rappend(tail(xs), cons(head(xs), ys)) : ys;
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
      return hasData(xs) ? foldL(f, f(init, head(xs)), tail(xs)) : init;
    }

    template<typename F, typename U>
    friend U
    foldR(F f, List xs, U const& init)
    {
      return hasData(xs) ? foldR(f, tail(xs), f(head(xs), init)) : init;
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    static List<U>
    rfMapAux(F f, List xs, List<U> ys)
    {
      return hasData(xs)
        ? rfMapAux(f, tail(xs), cons(f(head(xs)), ys))
        : ys;
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    static List<U>
    fMapAux(F f, List xs, List<U> ys)
    {
      return reverse(rfMapAux(f, xs, ys));
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    friend decay_t<decltype(list(declval<U>(), declval<U>()))>
    fMap(F f, List xs)
    {
      return fMapAux(f, xs, List<U>::nil);
    }

    template<typename F, size_type M, typename U = decay_t<result_of_t<F(T)>>>
    static decay_t<decltype(fMap(declval<F>(), declval<List>()))>
    aMapAux(List<F,M> fs, List xs){
      return hasData(fs)
        ? append(fMap(head(fs), xs), aMapAux(tail(fs), xs))
        : List<U>::nil;
    }


    template<typename F, size_type M>
    friend auto
    aMap(List<F,M> fs, List xs){
      return aMapAux(fs, xs);
    }

    template<typename F, size_type M, typename Us, typename ... Vss>
    friend auto
    aMap(List<F,M> fs, List xs, Us ys, Vss ... zss)
    {
      return aMap(aMap(fs, xs), ys, zss ...);
    }


    template<typename F>
    friend List
    buildListAux(F f, size_type n, List xs)
    {
      return n > 0 ? buildListAux(f, n - 1, cons(f(n - 1), xs)) : xs;
    }

    friend List
    drop(List xs, size_type n)
    {
      return n > 0 ? drop(tail(xs), n - 1) : xs;
    }

    static List
    takeAux(List xs, size_type n, List accum)
    {
      return (n > 0 && hasData(xs))
               ? takeAux(tail(xs), n - 1, cons(head(xs), accum))
               : reverse(accum);
    }

    friend List
    take(List xs, size_type n)
    {
      return takeAux(xs, n, nil);
    }

    friend value_type
    listRef(List xs, index_type index)
    {
      return head(drop(xs, index));
    }

    friend bool
    operator==(List xs, List ys)
    {
      return hasData(xs) && hasData(ys)
               ? head(xs) == head(ys) && tail(xs) == tail(ys)
               : (isNull(xs) && isNull(ys) ? true : false);
    }

    friend bool
    operator!=(List xs, List ys)
    {
      return !(xs == ys);
    }

    template<typename F>
    friend F
    doList(List xs, F f)
    {
      unique_ptr<List> ptr(make_unique<List>(xs));
      while(! isNull(*ptr))
      {
        f(head(*ptr));
        ptr = make_unique<List>(tail(*ptr));
      }
      return f;
    }

  public:
    inline static const List nil{};
  };

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

    List(const_reference x, List const& xs)
      : data(
          (isNull(xs.data) || isFull(head(xs.data)))
            ? cons(Datum(x), xs.data)
            : cons(cons(x, head(xs.data)), tail(xs.data)))
    {}

    List(Data input_data)
      : data(input_data)
    {}

    inline static const List nil = List();

    friend bool
    hasData(List xs)
    {
      return hasData(xs.data);
    }

    friend bool
    isNull(List xs)
    {
      return !(hasData(xs));
    }

    const value_type&
    getHead() const { return data.getHead().getHead(); }


    friend value_type
    head(List xs)
    {
      return hasData(xs) ? head(head(xs.data))
                         : throw logic_error(
                             "Cannot access the head of an empty list");
    }

    friend List
    tail(List xs)
    {
      return hasData(xs)
               ? ((length(head(xs.data)) == 1)
                    ? List(tail(xs.data))
                    : List(cons(tail(head(xs.data)), tail(xs.data))))               : nil;
    }

    friend size_type
    length(List xs)
    {
      return foldL(
        [](auto accum, auto chunk) { return accum + length(chunk); },
        0,
        xs.data);
    }

    friend List
    cons(const_reference x, List xs)
    {
      return List(x, xs);
    }

    template<typename F>
    friend List
    buildListAux(F f, size_type n, List xs)
    {
      return n > 0 ? buildListAux(f, n - 1, cons(f(n - 1), xs)) : xs;
    }

    friend List
    drop(List xs, size_type n)
    {
      return hasData(xs)
               ? ((n >= length(head(xs.data)))
                    ? drop(
                        List(tail(xs.data)), n - length(head(xs.data)))
                    : ((n > 0)
                         ? List(cons(
                             drop(head(xs.data), n), tail(xs.data)))
                         : xs))
               : xs;
    }

    static List
    takeAux(List xs, size_type n, Data accum)
    {
      return hasData(xs)
               ? ((n > length(head(xs.data)))
                    ? takeAux(
                        List(tail(xs.data)),
                        n - length(head(xs.data)),
                        cons(head(xs.data), accum))
                    : (n > 0 ? List(reverse(
                                 cons(take(head(xs.data), n), accum)))
                             : List(reverse(accum))))
               : List(accum);
    }

    friend List
    take(List xs, size_type n)
    {
      return takeAux(xs, n, Data::nil);
    }

    friend value_type
    listRef(List xs, index_type index)
    {
      return head(drop(xs, index));
    }

    friend bool
    operator==(List xs, List ys)
    {
      return hasData(xs) && hasData(ys)
               ? head(xs) == head(ys) && tail(xs) == tail(ys)
               : (isNull(xs) && isNull(ys) ? true : false);
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
      return hasData(xs) && hasData(ys)
               ? head(xs) == head(ys) && tail(xs) == tail(ys)
               : (isNull(xs) && isNull(ys) ? true : false);
    }

    friend List
    rappend(List xs, List ys)
    {
      return hasData(xs)
               ? rappend(
                   List(tail(xs.data)),
                   List(cons(reverse(head(xs.data)), ys.data)))
               : ys;
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
    static U
    foldLAux(F f, U const& init, List xs)
    {
      return hasData(xs) ? foldLAux(
                             f,
                             foldL(f, init, head(xs.data)),
                             List(tail(xs.data)))
                         : init;
    }

    template<typename F, typename U>
    friend U
    foldL(F f, U const& init, List xs)
    {
      return foldLAux(f, init, xs);
    }

    template<typename F, typename U>
    static U
    foldRAux(F f, List rxs, U init)
    {
      return hasData(rxs) ? foldRAux(
                              f,
                              List(tail(rxs.data)),
                              foldR(f, head(rxs.data), init))
                          : init;
    }

    template<typename F, typename U>
    friend U
    foldR(F f, List xs, U init)
    {
      return foldRAux(f, List(reverse(xs.data)), init);
    }

    template<typename F, typename R>
    static R
    rFMapAux(F f, Data xs, R accum)
    {
      return hasData(xs)
        ? rFMapAux(f, tail(xs), cons(fMap(f, head(xs)), accum))
        : accum;
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    static List<U, N>
    fMapAux(F f, Data xs, typename List<U, N>::Data accum)
    {
      return reverse(rFMapAux(f, xs, accum));
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    friend List<U, N>
    fMap(F f, List xs)
    {
      return fMapAux(f, xs.data, List<U, N>::Data::nil);
    }


    template<
      typename F,
      size_type M,
      typename U = decay_t<result_of_t<F(T)>>,
      typename R = decay_t<decltype(fMap(declval<F>(), declval<List>()))>
      >
    static R
    aMapAux(List<F,M> fs, List xs)
    {
      return hasData(fs)
        ? append(fMap(head(fs), xs), aMapAux( tail(fs), xs ))
        : R::nil;
    }


    template<typename F, size_type M>
    friend auto
    aMap(List<F,M> fs, List xs)
    {
      return aMapAux(fs, xs);
    }

    template<typename F, size_type M, typename Us, typename ... Vss>
    friend auto
    aMap(List<F,M> fs, List xs, Us ys, Vss ... zss)
    {
      return aMap(aMap(fs, xs), ys, zss ...);
    }

    template<typename F>
    friend F
    doList(List xs, F f)
    {
      unique_ptr<List> ptr(make_unique<List>(xs));
      while(! isNull(*ptr))
      {
        f(head(*ptr));
        ptr = make_unique<List>(tail(*ptr));
      }
      return f;
    }
  }; // end of class List<T,N>

  template<typename T>
  List<T>
  listOf()
  {
    return nil<T>;
  }

  template<typename T, typename T1, typename... Ts>
  List<T>
  listOf(T1&& x1, Ts&&... xs)
  {
    return cons(forward<T1>(x1), listOf<T>(forward<Ts>(xs)...));
  }

  template<typename T>
  List<decay_t<T>>
  list(T&& x)
  {
    return listOf<decay_t<T>>(forward<T>(x));
  }

  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T = common_type_t<decay_t<T1>, decay_t<T2>, decay_t<Ts>...>>
  List<T>
  list(T1&& x1, T2&& x2, Ts&&... xs)
  {
    return listOf<T>(forward<T1>(x1), forward<T2>(x2), forward<Ts>(xs)...);
  }



  template<typename F, typename T = decay_t<result_of_t<F(index_type)>>>
  List<T>
  buildList(F f, size_type n)
  {
    return buildListAux(f, n, nil<T>);
  }
} // end of namespace ListProcessing::Dynamic::Details
