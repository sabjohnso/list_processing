#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/dynamic/ListFwd.hpp>

namespace ListProcessing::Dynamic::Details
{
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




  public:

    bool
    hasData() const { return bool(ptr); }

    /**
     * @brief Return true if the input list has data and false otherwise.
     */
    friend bool
    hasData(List xs)
    {
      return xs.hasData();
    }

    /**
     * @brief Return true if this list is empty and false otherwise
     */
    bool
    isEmpty() const { return ! hasData(); }

    /**
     * @brief Return true if the input list is empty and false otherwise
     */
    friend bool
    isEmpty(List xs)
    {
      return xs.isEmpty();
    }


    /**
     * @brief Return true if this list is empty and false otherwise
     */
    bool
    isNull() const { return ! hasData(); }

    /**
     * @brief Return true if the list is empty and false otherwise
     */
    friend bool
    isNull(List xs)
    {
      return xs.isNull();
    }






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
      return xs.hasData() ? xs.ptr->tail : xs;
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
          return xs.hasData()
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
      return xs.hasData()
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
          return xs.hasData()
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
    append(List xs, List ys){
      return rappend(reverse(xs), ys);
    }

    /**
     * @brief Apply the binary input function to the input list,
     * folding from the left.
     */
    template<typename F, typename U>
    friend U
    foldL(F f, U init, List xs){
      using tramp = Trampoline<U>;
      struct Aux {
        tramp
        run(F f, U init, List xs) const {
          return xs.hasData()
            ? Trampoline<U>([=,this]{ return run(f, f(init, head(xs)), tail(xs)); })
            : Trampoline<U>(init);
        }
      } constexpr aux{};
      return U(aux.run(f, init, xs));
    }


    /**
     * @brief Apply the binary input function to the input list,
     * folding from the right.
     *
     * Signature: B(B(A,B), List<A>, B)
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

    /**
     * @brief Map a function over alist and return the results in
     * reverse order.
     *
     * signature: List<B>(B(A), List(A), List<B>)
     */
    template<typename F, typename Result>
    static Result
    rMap(F f, List xs, Result accum){
      using tramp = Trampoline<Result>;
      struct Aux{
        tramp
        run(F f, List xs, Result accum) const {
          return xs.hasData()
            ? tramp([=,this]{ return run(f, tail(xs), cons(f(head(xs)), accum)); })
            : tramp(accum);
        }
      } constexpr aux{};
      return Result(aux.run(f, xs, accum));
    }

    /**
     * @brief Return a list with element equivalent to the elements of
     * the input list transformed by the input function.
     *
     * signature: List<B>(B(A), List<A>)
     */
    template<typename F, typename U = decay_t<result_of_t<F(T)>>, typename Result = List<U>>
    friend Result
    map(F f, List xs){
      return reverse(rMap(f, xs, Result::nil));
    }

    template<typename F, typename Result>
    static Trampoline<Result>
    aMapAux(F fs, List xs, Result accum){
      using tramp = Trampoline<Result>;
      return fs.hasData()
        ? tramp([=]{ return aMapAux(tail(fs), xs, rappend(map(head(fs), xs), accum)); })
        : tramp(reverse(accum));
    }

    /**
     * @brief Applicative mapping for lists.
     *
     * signature: List<B>(List<B(A)>, List<A>)
     */
    template<typename F>
    friend auto
    aMap(F fs, List xs){
      using Result = decltype(map(head(fs), xs));
      return Result(aMapAux(fs, xs, Result::nil));
    }

    /**
     * @brief Variadic applicative mapping for lists
     *
     * signature: List<Z>(List<Z(A, B, Cs ...)>, List<A>, List<B>, List<Cs> ...)
     */
    template<typename F, size_type M, typename Us, typename ... Vss>
    friend auto
    aMap(List<F,M> fs, List xs, Us ys, Vss ... zss)
    {
      return aMap(aMap(fs, xs), ys, zss ...);
    }

    /**
     * @brief Monadic mapping for lists
     *
     * signature: List<B>(List<B>(A), List<A>)
     */
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

    /**
     * @brief Auxilliary function for building lists
     *
     * signature: List<A>(A(Index), List<A>)
     */
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

    /**
     * @brief Return a list like the input list with the
     * first n elements removed if list list has more than
     * n elements, or nil if the list has n or fewer elements.
     *
     * signature: List<A>(List<A>, Size)
     */
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
     * @brief Return a list containing the first n
     * elements of the input list, if the input list has more
     * than n element, or return the input list if it has fewer than
     * n elements.
     *
     * signature: List<A>(List<A>, Size)
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
     *
     * @details It is an error to call this function with and index
     * that is greater than or equal to the length of the list.
     *
     * signature: A(List<A>, Index)
     */
    friend value_type
    listRef(List xs, index_type index)
    {
      return head(drop(xs, index));
    }

    /**
     * @brief Equality operator for Lists
     *
     * signature: bool(List<A>, List<A>)
     */
    friend bool
    operator==(List xs, List ys)
    {
      using tramp = Trampoline<bool>;
      struct Aux{
        tramp
        run(List xs, List ys) const {
          return xs.hasData() && ys.hasData()
            ? (head(xs) == head(ys)
               ? tramp([=,this]{ return run(tail(xs), tail(ys)); })
               : tramp(false))
            : tramp(xs.isNull() && ys.isNull() ? true  : false);
        }
      } constexpr aux{};
      return bool(aux.run(xs, ys));
    }

    /**
     * @brief Inequality of lists
     *
     * signature: bool(List<A>, List<A>)
     */
    friend bool
    operator!=(List xs, List ys)
    {
      return !(xs == ys);
    }

    /**
     * @brief Call a function with each element of an input list
     *
     * signature: B(A)(B(A), List<A>)
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

  }; // end of class List<T,1>

} // end of namespace ListProcessing::Dynamic::Details
