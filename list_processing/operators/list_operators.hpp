#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{
  template<typename T>
  concept HasHead = requires(T&& xs){
    {forward<T>(xs).head()};
  };

  /**
   * @brief Return the head of a list
   */
  class Head : public Static_curried<Head, Nat<1>>{
  public:
    template<HasHead T>
    static constexpr auto
    call(T&& xs){
      return forward<T>(xs).head();
    }
  } constexpr head{};


  template<typename T>
  concept HasTail  = requires(T&& xs){
    forward<T>(xs).tail();
  };

  /**
   * @brief Return the tail of a list
   */
  class Tail : public Static_curried<Tail, Nat<1>>{
  public:
    template<HasTail T>
    static constexpr auto
    call(T&& xs){
      return forward<T>(xs).tail();
    }
  } constexpr tail{};


  template<typename T, typename I>
  concept HasListRef = requires(I&& index, T&& xs){
    {forward<T>(xs).listRef(forward<I>(index))};
  };

  /**
   * @brief Append lists
   */
  class ListRef : public Static_curried<ListRef, Nat<2>>{
  public:
    template<typename I, HasListRef<I> T>
    static constexpr auto
    call(I&& index, T&& xs){
      return forward<T>(xs).listRef(forward<I>(index));
    }
  } constexpr listRef{};


  template<typename T, typename U>
  concept HasAppend = requires(U&& xs, T&& ys){
    {forward<T>(ys).append(forward<U>(xs))};
  };

  /**
   * @brief Append lists
   */
  class Append : public Static_curried<Append, Nat<2>>{
  public:
    template<typename U, HasAppend<U> T>
    static constexpr auto
    call(U&& xs, T&& ys){
      return forward<T>(ys).append(forward<U>(xs));
    }
  } constexpr append{};


  template<typename T, typename F>
  concept HasMapList = requires(F&& f, T&& xs){
    {forward<T>(xs).mapList(forward<F>(f))};
  };

  /**
   * @brief Functorial mapping operator for lists
   */
  class MapList : public Static_curried<MapList, Nat<2>>{
  public:
    template<typename F, HasMapList<F> T>
    static constexpr auto
    call(F&& f, T&& xs){
      return forward<T>(xs).mapList(forward<F>(f));
    }
  } constexpr mapList{};


  template<typename T, typename F>
  concept HasFApplyList = requires(F&& fs, T&& xs){
    {forward<T>(xs).fApplyList(forward<F>(fs))};
  };

  /**
   * @brief Applicative mapping operator for lists
   */
  class FApplyList : public Static_curried<FApplyList, Nat<2>>{
  public:
    template<typename F, HasFApplyList<F> T>
    static constexpr auto
    call(F&& fs, T&& xs){
      return forward<T>(xs).fApplyList(forward<F>(fs));
    }
  } constexpr fApplyList{};

  template<typename T, typename F>
  concept HasFlatMapList = requires(F&& f, T&& xs){
    {forward<T>(xs).flatMapList(forward<F>(f))};
  };

  /**
   * @brief Monadic mapping operator for lists
   */
  class FlatMapList : public Static_curried<FlatMapList, Nat<2>>{
  public:
    template<typename F, HasFlatMapList<F> T>
    static constexpr auto
    call(F&& f, T&& xs){
      return forward<T>(xs).flatMapList(forward<F>(f));
    }
  } constexpr flatMapList{};


  template<typename T>
  concept HasFlattenList = requires(T&& xss){
    {forward<T>(xss).flattenList()};
  };

  /**
   * @brief Monadic flatten operator for lists
   */
  class FlattenList : public Static_curried<FlattenList, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xss){
      return forward<T>(xss).flattenList();
    }
  } constexpr flattenList{};





} // end of namespace ListProcessing::Operators::Details
