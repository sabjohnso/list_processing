#pragma once

//
// ... Standard header files
//
#include <algorithm>
#include <iostream>
#include <iterator>

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{

  /**
   * @brief A tag to indicate the build constructor
   */
  struct build_tag
  {};

  /**
   * @brief A non-user-facing class template describing short lists
   *
   * @details This class template is intended to improve memory usage by
   * storing list values in pre-allocated chunks of a statically selected
   * length. In addition to memory usage, there may be performance benefits
   * for some list operations. The efficacy of the optimization,
   * aswell as the appropriate seletion of maximum length depend on
   * the element type.
   *
   * List values are stored in pre-allocated, contiguous chunks.
   * Whether optimal or not, there are some restrictions on
   * the list value type that must be satisfied to use this class template:
   *
   *   - the value type must be default constructible
   *   - the value type must be assignable
   *
   * The ShortList class template is implemented as a
   * non-empty list with a maximum length statically specified through
   * the template parameters: N. Every instance has at
   * least one element, leaving the representation of the absence of data
   * as the responsibility of classes using this class template.
   *
   */
  template<typename T, size_type N>
  class ShortList
  {
    static_assert(is_default_constructible_v<T>);

    static_assert(N > 0);

  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    static constexpr size_type extent = N;

    ShortList(const_reference x)
      : data(make_shared<Kernel>(x))
      , fillpoint(1)
      , reversed(false)
    {}

    template<typename U, size_type M, typename F>
    friend ShortList
    buildShortList(F f, size_type n);

    template<
      typename F,
      typename Check = enable_if_t<is_invocable_r_v<value_type, F, index_type>, void>>
    ShortList(F f, size_type n, build_tag)
      : data(make_shared<Kernel>(f, n, build_tag{}))
      , fillpoint(n)
      , reversed(false)
    {}




  private:
    /**
     * @brief A private nested class describing the shared shorage
     * for ShortLists.
     *
     * @details This class is only visible within the scope of the
     * ShortList template specialization in which it is nested.
     * Nevertheless, care should be taken to hide the implementation
     * details of this class because the implementation is stateful,
     * would be detrimental to architecture of the List Processing
     * library if exposed.
     */
    class Kernel
    {
    public:
      Kernel(const_reference x)
      {
        values[0] = x;
        fillpoint = 1;
      }

      Kernel(Kernel&& input)
        : values(move(input.values))
        , fillpoint(input.fillpoint)
      {}

      template<
        typename F,
        typename Check = enable_if_t<is_invocable_r_v<value_type, F, index_type>, void>>
      Kernel(F f, size_type n, build_tag)
        : fillpoint(n)
      {
        assert(n < extent);
        for (index_type i = 0; i < n; ++i) {
          values[i] = f(n - i - 1);
        }
      }

      const_reference
      operator[](index_type index) const
      {
        assert(index >= 0);
        assert(index < fillpoint);
        return values[index];
      }

      Kernel()
        : fillpoint(0)
      {}

    public:




      static shared_ptr<Kernel>
      copy(shared_ptr<const Kernel> xs, size_type n)
      {
        auto result = make_shared<Kernel>();
        copy_n(begin(xs->values), n, begin(result->values));
        result->fillpoint = n;
        return result;
      }

      static shared_ptr<Kernel>
      reverseCopy(shared_ptr<const Kernel> xs, size_type n)
      {
        auto result = make_shared<Kernel>();
        copy_n(rbegin(xs->values) + extent - n, n, begin(result->values));
        result->fillpoint = n;
        return result;
      }

      static shared_ptr<Kernel>
      conj(shared_ptr<Kernel> xs, index_type index, const_reference x)
      {
        assert(xs);
        lock_guard<mutex> lock(xs->mex);
        if (xs->fillpoint == index) {
          return conjExisting(xs, x);
        } else {
          return conjNew(xs, index, x);
        }
      }

      static shared_ptr<Kernel>
      conjExisting(shared_ptr<Kernel> xs, const_reference x)
      {
        xs->values[xs->fillpoint++] = x;
        return xs;
      }

      static shared_ptr<Kernel>
      conjNew(shared_ptr<Kernel> xs, index_type index, const_reference x)
      {
        auto result = make_shared<Kernel>();
        copy_n(begin(xs->values), index, begin(result->values));
        result->values[index] = x;
        result->fillpoint = index + 1;
        return result;
      }

    private:
      array<value_type, extent> values;
      index_type fillpoint;
      mutex mex;

    }; // end of class Kernel

    shared_ptr<Kernel> data;
    index_type fillpoint;
    bool reversed;

    ShortList(const_reference x, ShortList xs)
      : data(Kernel::conj(xs.data, xs.fillpoint, x))
      , fillpoint(xs.fillpoint + 1)
      , reversed(false)
    {}

    ShortList(ShortList xs, size_type new_fillpoint)
      : data(xs.data)
      , fillpoint(new_fillpoint)
      , reversed(false)
    {
      assert(!xs.isReversed());
    }

    ShortList(ShortList xs, bool reverse)
      : data(xs.data)
      , fillpoint(xs.fillpoint)
      , reversed(reverse ? !xs.reversed : xs.reversed)
    {}

    ShortList(shared_ptr<Kernel> input_data, index_type input_fillpoint, bool input_reversed)
      : data(input_data)
      , fillpoint(input_fillpoint)
      , reversed(input_reversed)
    {}

  public:



    const_reference
    getHead() const {
      return isReversed()
        ? (*data)[0]
        : (*data)[fillpoint - 1];
    }

    const_reference
    head() const {
      return isReversed()
        ? (*data)[0]
        : (*data)[fillpoint - 1];
    }


    friend value_type
    head(ShortList xs){
      return xs.head();
    }

    size_type
    length() const {
      assert(fillpoint > 0);
      return fillpoint;
    }

    friend size_type
    length(ShortList xs)
    {
      return xs.length();
    }

    bool
    isFull() const { return length() == extent; }

    friend bool
    isFull(ShortList xs)
    {
      return xs.isFull();
    }

    bool
    isReversed() const {
      return reversed;
    }

    friend bool
    isReversed(ShortList xs)
    {
      return xs.isReversed();
    }

    ShortList
    copy() const {
      return isReversed()
        ? ShortList(Kernel::reverseCopy(data, fillpoint), fillpoint, false)
        : ShortList(Kernel::copy(data, fillpoint), fillpoint, false);
    }

    friend ShortList
    copy(ShortList xs)
    {
      return xs.copy();
    }

    ShortList
    cons(const_reference x) const {
      return isReversed() ? copy().cons(x) : ShortList(x, *this);
    }

    friend ShortList
    cons(const_reference x, ShortList xs)
    {
      return xs.cons(x);
    }


    const_reference
    listRef(index_type index) const {
      return isReversed() ? (*data)[index] : (*data)[fillpoint - index - 1];
    }


    friend value_type
    listRef(ShortList xs, index_type index)
    {
      return xs.listRef(index);
    }

    friend ShortList
    reverse(ShortList xs)
    {
      return ShortList(xs, true);
    }


    ShortList
    tail() const
    {
      return isReversed() ? copy().tail() : ShortList(*this, fillpoint - 1);
    }

    friend ShortList
    tail(ShortList xs)
    {
      return xs.tail();
    }

    ShortList
    take(size_type n) const {
      assert(n > 0);
      assert(n <= length());
      return reverse(reverse(*this).drop( length() - n));
    }

    friend ShortList
    take(ShortList xs, size_type n)
    {
      return xs.take(n);
    }

    ShortList
    drop(size_type n) const {
      assert(length() > n);
      return isReversed() ? copy().drop(n) : ShortList(*this, length() - n);
    }

    friend ShortList
    drop(ShortList xs, size_type n)
    {
      return xs.drop(n);
    }

    friend bool
    operator==(ShortList xs, ShortList ys)
    {
      index_type n = xs.length();
      index_type i = 0;
      bool result = xs.length() == ys.length();
      while (result && i < n) {
        result = xs.listRef(i) == ys.listRef(i);
        ++i;
      }
      return result;
    }

    friend bool
    operator!=(ShortList xs, ShortList ys)
    {
      return !(xs == ys);
    }

    friend ostream&
    operator<<(ostream& os, ShortList xs)
    {
      size_type n = xs.length();
      os << "(" << xs.listRef(0);
      for (index_type i = 1; i < n; ++i) {
        os << " " << xs.listRef(i);
      }
      os << ")";
      return os;
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    friend ShortList<U, N>
    fMap(F f, ShortList xs)
    {
      return ShortList<U, N>(
        [=](auto index) { return f(xs.listRef(index)); }, xs.length(), build_tag{});
    }

    template<typename F, typename U>
    friend U
    foldL(F f, U init, ShortList xs)
    {
      size_type n = xs.length();
      for (index_type i = 0; i < n; ++i) {
        init = f(init, xs.listRef(i));
      }
      return init;
    }

    template<typename F, typename U>
    friend U
    foldR(F f, ShortList xs, U init)
    {
      size_type n = xs.length();
      for (index_type i = 0; i < n; ++i) {
        init = f(xs.listRef(n - i - 1), init);
      }
      return init;
    }
  };

  template<typename T, size_type N, typename T1>
  ShortList<T, N>
  short_list(T1&& x1)
  {
    return ShortList<T, N>(forward<T1>(x1));
  }

  template<typename T, size_type N, typename T1, typename T2, typename... Ts>
  ShortList<T, N>
  short_list(T1&& x1, T2&& x2, Ts&&... xs)
  {
    return cons(forward<T1>(x1), short_list<T, N>(forward<T2>(x2), forward<Ts>(xs)...));
  }

  template<typename T, size_type N, typename F>
  ShortList<T, N>
  buildShortList(F f, size_type n)
  {
    return ShortList<T, N>(f, n, build_tag{});
  }

} // end of namespace ListProcessing::Dynamic::Details
