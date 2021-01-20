#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{

  /**
   * @brief Return the head of a list
   */
  class Head : public Static_curried<Head, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return forward<T>(xs).head();
    }
  } constexpr head{};

  /**
   * @brief Return the tail of a list
   */
  class Tail : public Static_curried<Tail, Nat<1>>{
  public:
    template<typename T>
    static constexpr auto
    call(T&& xs){
      return forward<T>(xs).tail();
    }
  } constexpr tail{};


  /**
   * @brief Append lists
   */
  class ListRef : public Static_curried<ListRef, Nat<2>>{
  public:
    template<typename I, typename T>
    static constexpr auto
    call(I&& index, T&& xs){
      return forward<T>(xs).listRef(forward<I>(index));
    }
  } constexpr listRef{};

  /**
   * @brief Append lists
   */
  class Append : public Static_curried<Append, Nat<2>>{
  public:
    template<typename T, typename U>
    static constexpr auto
    call(T&& xs, U&& ys){
      return forward<U>(ys).append(forward<T>(xs));
    }
  } constexpr append{};

  /**
   * @brief Functorial mapping operator for lists
   */
  class MapList : public Static_curried<MapList, Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& f, T&& xs){
      return forward<T>(xs).mapList(forward<F>(f));
    }
  } constexpr mapList{};

  /**
   * @brief Applicative mapping operator for lists
   */
  class FApplyList : public Static_curried<FApplyList, Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& fs, T&& xs){
      return forward<T>(xs).fApplyList(forward<F>(fs));
    }
  } constexpr fApplyList{};

  /**
   * @brief Monadic mapping operator for lists
   */
  class FlatMapList : public Static_curried<FlatMapList, Nat<2>>{
  public:
    template<typename F, typename T>
    static constexpr auto
    call(F&& f, T&& xs){
      return forward<T>(xs).flatMapList(forward<F>(f));
    }
  } constexpr flatMapList{};


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
