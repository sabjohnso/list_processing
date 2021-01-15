#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details
{

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
