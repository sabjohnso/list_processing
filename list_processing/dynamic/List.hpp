#pragma once

//
// ... List Processing' header files
//
#include <list_processing/dynamic/ListOperators.hpp>
#include <list_processing/dynamic/ListTraits.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{

  template<typename T, size_type N>
  class List;

  template<typename T>
  class List<T, 1>
    : public ListOperators<List<T, 1>, T>
    , public ListTraits<T>
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

    friend bool
    hasData(List xs)
    {
      return bool(xs.ptr);
    }

    // clang-format off
    List const&
    getTail() const 
    {
      return hasData(*this)
        ? ptr->tail
        : *this;
    }

    friend List
    tail(List xs)
    {
      return hasData(xs) ? xs.ptr->tail : xs;
    }


    const_reference
    getHead() const
    {
      return hasData(*this)
        ? ptr->head
        : throw logic_error("Cannot access the head of an empty list");
    }

    friend value_type
    head(List xs)
    {
      return hasData(xs)
        ? xs.ptr->head
        : throw logic_error("Cannot access the head of an empty list");
    }
    // clang-format on

  public:
    inline static const List nil{};
  };

  template<typename T, size_type N>
  class List
  {
  public:
    using value_type = T;
    using const_reference = value_type const&;
    using Storage = Chunk<T, N>;
    using Datum = Chunk<T, N>;
    using Data = List<Storage, 1>;

  private:
    Data data;

  public:
    List()
      : data(List<Storage>::nil)
    {}

    List(const_reference x, List const& xs)
      : data(
          (isNull(xs.data) || isFull(head(xs.data)))
            ? cons(Storage(x), xs.data)
            : cons(Storage(x, head(xs.data)), tail(xs.data)))
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

    friend value_type
    head(List xs)
    {
      return hasData(xs) ? head(xs.data)[length(head(xs.data)) - 1]
                         : throw logic_error(
                             "Cannot access the head of an empty list");
    }

    friend List
    tail(List xs)
    {
      return hasData(xs)
               ? ((length(head(xs.data)) == 1)
                    ? List(tail(xs.data))
                    : List(cons(
                        Datum(head(xs.data), length(head(xs.data)) - 1),
                        tail(xs.data))))
               : nil;
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
    rappend(List xs, List ys)
    {}

    friend List
    cons(const_reference x, List xs)
    {
      return List(x, xs);
    }

    template<typename F>
    friend List
    buildList(F f, size_type n, List xs)
    {
      return n > 0 ? buildList(f, n - 1, cons(f(n - 1), xs)) : xs;
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
  auto
  list(T&& x)
  {
    return listOf<decay_t<T>>(forward<T>(x));
  }

  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T =
      common_type_t<decay_t<T1>, decay_t<T2>, decay_t<Ts>...>>
  List<T>
  list(T1&& x1, T2&& x2, Ts&&... xs)
  {
    return listOf<T>(
      forward<T1>(x1), forward<T2>(x2), forward<Ts>(xs)...);
  }

  template<typename T>
  const List<T, ListTraits<T>::chunk_size> nil =
    List<T, ListTraits<T>::chunk_size>::nil;

  template<typename T, typename F>
  List<T>
  buildList(F f, size_type n)
  {
    return buildList(f, n, nil<T>);
  }
} // end of namespace ListProcessing::Dynamic::Details
