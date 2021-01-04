#pragma once

//
// ... List Processing' header files
//
#include <list_processing/dynamic/ListOperators.hpp>
#include <list_processing/dynamic/ListTraits.hpp>
#include <list_processing/dynamic/ShortList.hpp>
#include <list_processing/dynamic/Nil.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<
    typename T1,
    typename T2,
    typename... Ts>
  auto
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


  template<typename T>
  using ListType = List<T, ListTraits<T>::chunk_size>;

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
    List() : ptr(nullptr) {}

    List(Nil) : ptr(nullptr){}

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

    /**
     * @brief Return a list equivalent to the input with the
     * input value at the front.
     */
    friend List
    cons(const_reference x, List xs)
    {
      return List(x, xs);
    }

    /**
     * @brief Return true if the input list has data and false otherwise.
     */
    friend bool
    hasData(List xs)
    {
      return bool(xs.ptr);
    }

    /**
     * @brief Return true if the list is empty and false otherwise
     */
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

    /**
     * @brief Return a list that is equivalent to the tail of
     * the input list.
     */
    friend List
    tail(List xs)
    {
      return hasData(xs) ? xs.ptr->tail : xs;
    }

    /**
     * @brief Return the number of elements in the input list
     */
    friend size_type
    length(List xs){
      using tramp = Trampoline<size_type>;
      struct Aux{
        tramp
        run(List xs, size_type accum) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(tail(xs), accum+1); })
            : tramp(accum);
        }
      } constexpr aux{};
      return size_type(aux.run(xs, 0));
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

    /**
     * @brief Return the value that is at the front of the list.
     *
     * @details It is an error to call this functio with an empty
     * list and in the case it is, an exception will be thrown.
     */
    friend value_type
    head(List xs)
    {
      return hasData(xs)
        ? xs.ptr->head
        : throw logic_error("Cannot access the head of an empty list");
    }
    // clang-format on

    /**
     * @brief Return a list that is equivalent to the first input List
     * reversed and the second input appended to it.
     */
    friend List
    rappend(List xs, List ys)
    {
      using tramp = Trampoline<List>;
      struct Aux{
        tramp
        run(List xs, List ys) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(tail(xs), cons(head(xs), ys)); })
            : tramp(ys);
        }
      } constexpr aux{};
      return List(aux.run(xs, ys));
    }

    /**
     * @brief Return a list that is equivalent to the input list with the
     * order of the input values reversed.
     */
    friend List
    reverse(List xs)
    {
      return rappend(xs, nil);
    }

    /**
     * @brief Return a list that is equivalent to the second input List
     * appended to the first input list.
     */
    friend List
    append(List xs, List ys)
    {
      return rappend(reverse(xs), ys);
    }


    /**
     * @brief Apply the binary input function to the input list,
     * folding from the left.
     */
    template<typename F, typename U>
    friend U
    foldL(F f, U init, List xs)
    {
      using tramp = Trampoline<U>;
      struct Aux {
        tramp
        run(F f, U init, List xs) const {
          return hasData(xs)
            ? Trampoline<U>([=,this]{ return run(f, f(init, head(xs)), tail(xs)); })
            : Trampoline<U>(init);
        }
      } constexpr aux{};
      return U(aux.run(f, init, xs));
    }


    /**
     * @brief Apply the binary input function to the input list,
     * folding from the right.
     */
    template<typename F, typename U>
    friend U
    foldR(F f, List xs, U init)
    {
      using tramp = Trampoline<U>;
      struct Aux {
        tramp
        run(F f, List xs, U init) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), f(head(xs), init)); })
            : tramp(init);
        }
      } constexpr aux{};
      return U(aux.run(f, xs, init));
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    static List<U>
    rfMapAux(F f, List xs, List<U> ys)
    {
      return hasData(xs)
        ? rfMapAux(f, tail(xs), cons(f(head(xs)), ys))
        : ys;
    }



    template<typename F, typename Result>
    static Result
    rMap(F f, List xs, Result accum)
    {
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp
        run(F f, List xs, Result accum) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), cons(f(head(xs)), accum)); })
            : tramp(accum);
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, accum));
    }



    /**
     * @brief Return a list with element equivalent to the elements of
     * the input list transformed by the input function.
     */
    template<typename F, typename U = decay_t<result_of_t<F(T)>>, typename Result = ListType<U>>
    friend Result
    map(F f, List xs){
      return reverse(rMap(f, xs, Result::nil));
    }

    template<typename F, typename Result>
    static Trampoline<Result>
    aMapAux(F fs, List xs, Result accum){
      using tramp = Trampoline<Result>;
      return hasData(fs)
        ? tramp([=]{ return aMapAux(tail(fs), xs, rappend(map(head(fs), xs), accum)); })
        : tramp(reverse(accum));
    }


    template<typename F>
    friend auto
    aMap(F fs, List xs){
      using Result = decltype(map(head(fs), xs));
      return Result(aMapAux(fs, xs, Result::nil));
    }

    template<typename F, size_type M, typename Us, typename ... Vss>
    friend auto
    aMap(List<F,M> fs, List xs, Us ys, Vss ... zss)
    {
      return aMap(aMap(fs, xs), ys, zss ...);
    }

    template<typename F, typename Result = result_of_t<F(T)>>
    friend Result
    mMap(F f, List xs){
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp
        run(F f, List xs, Result accum) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), rappend(f(head(xs)), accum)); })
            : tramp(reverse(accum));
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, Result::nil));
    }

    template<typename F>
    static Trampoline<List>
    buildList(F f, size_type n, List xs){
      return n > 0
        ? Trampoline<List>([=]{ return buildList(f, n-1, cons(f(n-1), xs)); })
        : Trampoline<List>(xs);
    }

    template<typename F>
    friend List
    buildListAux(F f, size_type n, List accum)
    {
      using tramp = Trampoline<List>;
      struct Aux {
        tramp
        run(F f, size_type n, List accum) const {
          return n > 0
            ? tramp([=,this]{ return run(f, n-1, cons(f(n-1), accum)); })
            : tramp(accum);
        }
      } constexpr aux{};
      return List(aux.run(f, n, accum));
    }

    friend List
    drop(List xs, size_type n)
    {
      using tramp = Trampoline<List>;
      struct Aux{
        tramp
        run(List xs, size_type n) const {
          return hasData(xs) && n > 0
            ? tramp([=,this]{ return run(tail(xs), n-1); })
            : tramp(xs);
        }
      } constexpr aux{};
      return List(aux.run(xs, n));
    }


    /**
     * @brief Return an list containing the first n
     * elements of the input list, if the input list has more
     * than n element, or return the input list if it has fewer than
     * n elements.
     */
    friend List
    take(List xs, size_type n)
    {
      using tramp = Trampoline<List>;
      struct Aux {
        tramp
        run(List xs, size_type n, List accum){
          return hasData(xs) && n > 0
            ? tramp([=,this]{ return run(tail(xs), n-1, cons(head(xs), accum)); })
            : tramp(reverse(accum));
        }
      } constexpr aux{};
      return List(aux.run(xs, n, nil));
    }

    /**
     * @brief Return the indicated element of the input list
     */
    friend value_type
    listRef(List xs, index_type index)
    {
      return head(drop(xs, index));
    }

    friend bool
    operator==(List xs, List ys)
    {
      using tramp = Trampoline<bool>;
      struct Aux{
        tramp
        run(List xs, List ys) const {
          return hasData(xs) && hasData(ys)
            ? (head(xs) == head(ys)
               ? tramp([=,this]{ return run(tail(xs), tail(ys)); })
               : tramp(false))
            : tramp(isNull(xs) && isNull(ys) ? true  : false);
        }
      } constexpr aux{};
      return bool(aux.run(xs, ys));
    }

    friend bool
    operator!=(List xs, List ys)
    {
      return !(xs == ys);
    }

    /**
     * @brief Call a function with each element of an input list
     */
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

    List(Nil)
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
    static Trampoline<List>
    buildList(F f, size_type n, List xs){
      return n > 0
        ? Trampoline<List>([=]{ return buildList(f, n-1, cons(f(n-1), xs)); })
        : Trampoline<List>(xs);
    }

    template<typename F>
    friend List
    buildListAux(F f, size_type n, List xs){
      struct Aux {
        Trampoline<List>
        run(F f, size_type n, List xs) const {
          return n > 0
            ? Trampoline<List>([=,this]{ return run(f, n-1, cons(f(n-1), xs)); })
            : Trampoline<List>(xs);
        }
      } constexpr aux{};
      return List(aux.run(f, n, xs));
    }

    friend List
    drop(List xs, size_type n)
    {
      using tramp = Trampoline<List>;
      struct Aux{
        tramp
        run(List xs, size_type n) const {
          return hasData(xs) && n > 0
            ? tramp([=,this]{ return run(tail(xs), n-1); })
            : tramp(xs);
        }
      } constexpr aux{};
      return List(aux.run(xs, n));
    }

    friend List
    take(List xs, size_type n){
      using tramp = Trampoline<List>;
      struct Aux{
        tramp
        run(List xs, size_type n, List accum) const {
          return hasData(xs) && n > 0
            ? tramp([=,this]{ return run(tail(xs), n-1, cons(head(xs), accum)); })
            : tramp(reverse(accum));
        }
      } constexpr aux{};
      return List(aux.run(xs, n, nil));
    }

    friend value_type
    listRef(List xs, index_type index)
    {
      return head(drop(xs, index));
    }

    friend bool
    operator==(List xs, List ys)
    {
      using tramp = Trampoline<bool>;
      struct Aux{
        tramp
        run(List xs, List ys) const {
          return hasData(xs) && hasData(ys)
            ? (head(xs) == head(ys)
               ? tramp([=,this]{ return run(tail(xs), tail(ys)); })
               : tramp(false))
            : tramp(isNull(xs) && isNull(ys) ? true : false);

        }
      }constexpr aux{};
      return length(xs) == length(ys)
        ? bool(aux.run(xs, ys))
        : false;
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
      struct Aux{
        tramp
        run(List xs, List<T, M> ys) const {
          return hasData(xs) && hasData(ys)
            ? (head(xs) == head(ys)
               ? tramp([=,this]{ return run(tail(xs), tail(ys)); })
               : tramp(false))
            : tramp((isNull(xs) && isNull(ys) ? true : false));
        }
      } constexpr aux{};
      return length(xs) == length(ys)
        ? bool(aux.run(xs, ys))
        : false;
    }


    friend List
    rappend(List xs, List ys)
    {
      struct Aux {
        Trampoline<List>
        run(List xs, List ys) const {
          return hasData(xs)
            ? Trampoline<List>([=,this]{ return run(tail(xs), cons(head(xs), ys));  })
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
      struct Aux{
        tramp
        run(F f, U init, List xs) const {
          return hasData(xs)
            ? tramp([=, this]{ return run(f, f(init, head(xs)), tail(xs)); })
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
      struct Aux{
        tramp
        run(F f, List xs, U init) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), f(head(xs), init)); })
            : tramp(init);
        }
      } constexpr aux{};
      return U(aux.run(f, reverse(xs),  init));
    }

    template<typename F, typename Result >
    static Result
    rMap(F f, List xs, Result accum){
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp run(F f, List xs, Result accum) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), cons(f(head(xs)), accum)); })
            : tramp(accum);
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, accum));
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>, typename Result = ListType<U>>
    friend Result
    map(F f, List xs)
    {
      return reverse(rMap(f, xs, Result::nil));
    }


    /**
     * @brief Applicative map of a list of functions over a list
     * of values.
     */
    template<typename F, size_type M, typename Result = ListType<result_of_t<F(value_type)>>>
    friend Result
    aMap(List<F,M> fs, List xs)
    {
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp
        run(List<F,M> fs, List xs, Result accum) const {
          return hasData(fs)
            ? tramp([=,this]{ return run(tail(fs), xs, Result(rMap(head(fs), xs, accum))); })
            : tramp(reverse(accum));
        }
      } constexpr aux{};
      return Result(aux.run(fs, xs, Result::nil));
    }

    template<typename F, size_type M, typename Us, typename ... Vss>
    friend auto
    aMap(List<F,M> fs, List xs, Us ys, Vss ... zss)
    {
      return aMap(aMap(fs, xs), ys, zss ...);
    }

    template<typename F>
    friend auto
    mMap(F f, List xs){
      using Result = result_of_t<F(T)>;
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp
        run(F f, List xs, Result accum) const {
          return hasData(xs)
            ? tramp([=,this]{ return run(f, tail(xs), rappend(f(head(xs)), accum)); })
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
    typename... Ts>
  auto
  list(T1&& x1, T2&& x2, Ts&&... xs)
  {
    using T = common_type_t<decay_t<T1>, decay_t<T2>, decay_t<Ts>...>;
    return listOf<T>(forward<T1>(x1), forward<T2>(x2), forward<Ts>(xs)...);
  }

  template<typename F, typename T = decay_t<result_of_t<F(index_type)>>>
  List<T>
  buildList(F f, size_type n)
  {
    return buildListAux(f, n, nil<T>);
  }
} // end of namespace ListProcessing::Dynamic::Details
