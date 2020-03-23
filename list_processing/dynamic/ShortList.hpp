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
   * @brief A tag using to indicate the build constructor
   */
  struct build_tag
  {};

  /**
   * @brief A non-user-facing class template describing short lists
   *
   * @details The ShortList class template is implemented as a
   * non-empty list with a maximum length statically specified through
   * the template parameters: N. This means that every instance has at
   * least one element, leaving the representation of the absence of data
   * as the responsibility of classes using this class template.
   *
   * This class template is intended as an optimization of the
   * storage and some list operations, where list values are stored in
   * pre-allocated, contiguous chunks. The optimal size of the chunks,
   * and whether this class should be used depends on the value type
   * of the list. Whether optimal or not, there are some restrictions on
   * the list value type that must be satisfied to use this class template:
   *
   *   - the value type must be default constructible
   *   - the value type must be assignable
   *
   *
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
      assert(!isReversed(xs));
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

    friend size_type
    length(ShortList const& xs)
    {
      assert(xs.fillpoint > 0);
      return xs.fillpoint;
    }

    friend bool
    isReversed(ShortList xs)
    {
      return xs.reversed;
    }

    friend ShortList
    copy(ShortList xs)
    {
      return isReversed(xs)
               ? ShortList(Kernel::reverseCopy(xs.data, xs.fillpoint), xs.fillpoint, false)
               : ShortList(Kernel::copy(xs.data, xs.fillpoint), xs.fillpoint, false);
    }

    friend ShortList
    cons(const_reference x, ShortList xs)
    {
      return isReversed(xs) ? cons(x, copy(xs)) : ShortList(x, xs);
    }

    friend value_type
    head(ShortList xs)
    {
      return isReversed(xs) ? (*xs.data)[0] : (*xs.data)[xs.fillpoint - 1];
    }

    friend value_type
    listRef(ShortList xs, index_type index)
    {
      return isReversed(xs) ? (*xs.data)[index] : (*xs.data)[xs.fillpoint - index - 1];
    }

    friend ShortList
    reverse(ShortList xs)
    {
      return ShortList(xs, true);
    }

    friend ShortList
    tail(ShortList xs)
    {
      return isReversed(xs) ? tail(copy(xs)) : ShortList(xs, xs.fillpoint - 1);
    }

    friend ShortList
    take(ShortList xs, size_type n)
    {
      assert(n > 0);
      assert(n <= length(xs));
      return reverse(drop(reverse(xs), length(xs) - n));
    }

    friend ShortList
    drop(ShortList xs, size_type n)
    {
      assert(length(xs) > n);
      return isReversed(xs) ? drop(copy(xs), n) : ShortList(xs, length(xs) - n);
    }

    friend bool
    operator==(ShortList xs, ShortList ys)
    {
      index_type n = length(xs);
      index_type i = 0;
      bool result = length(xs) == length(ys);
      while (result && i < n) {
        result = listRef(xs, i) == listRef(ys, i);
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
      size_type n = length(xs);
      os << "(" << listRef(xs, 0);
      for (index_type i = 1; i < n; ++i) {
        os << " " << listRef(xs, i);
      }
      os << ")";
      return os;
    }

    template<typename F, typename U = decay_t<result_of_t<F(T)>>>
    friend ShortList<U, N>
    fMap(F f, ShortList xs)
    {
      return ShortList<U, N>(
        [=](auto index) { return f(listRef(xs, index)); }, length(xs), build_tag{});
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
