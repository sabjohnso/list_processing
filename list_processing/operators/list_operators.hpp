#pragma once

//
// ... List Processing header files
//
#include <list_processing/operators/import.hpp>

namespace ListProcessing::Operators::Details {
  template<typename T>
  concept HasHead = requires(T&& xs) {
    { std::forward<T>(xs).head() };
  };

  /**
   * @brief Return the head of a list
   */
  class Head : public Static_curried<Head, Nat<1>> {
  public:
    template<HasHead T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).head();
    }
  } constexpr head{};

  template<typename T>
  concept HasTail = requires(T&& xs) {
    std::forward<T>(xs).tail();
  };

  /**
   * @brief Return the tail of a list
   */
  class Tail : public Static_curried<Tail, Nat<1>> {
  public:
    template<HasTail T>
    static constexpr auto
    call(T&& xs) {
      return std::forward<T>(xs).tail();
    }
  } constexpr tail{};

  template<typename T, typename I>
  concept HasListRef = requires(I&& index, T&& xs) {
    { std::forward<T>(xs).listRef(std::forward<I>(index)) };
  };

  /**
   * @brief Append lists
   */
  class ListRef : public Static_curried<ListRef, Nat<2>> {
  public:
    template<typename I, HasListRef<I> T>
    static constexpr auto
    call(I&& index, T&& xs) {
      return std::forward<T>(xs).listRef(std::forward<I>(index));
    }
  } constexpr listRef{};

  template<typename T, typename U>
  concept HasAppend = requires(U&& xs, T&& ys) {
    { std::forward<T>(ys).append(std::forward<U>(xs)) };
  };

  /**
   * @brief Append lists
   */
  class Append : public Static_curried<Append, Nat<2>> {
  public:
    template<typename U, HasAppend<U> T>
    static constexpr auto
    call(U&& xs, T&& ys) {
      return std::forward<T>(ys).append(std::forward<U>(xs));
    }
  } constexpr append{};

  template<typename T, typename F>
  concept HasMapList = requires(F&& f, T&& xs) {
    { std::forward<T>(xs).mapList(std::forward<F>(f)) };
  };

  /**
   * @brief Functorial mapping operator for lists
   */
  class MapList : public Static_curried<MapList, Nat<2>> {
  public:
    template<typename F, HasMapList<F> T>
    static constexpr auto
    call(F&& f, T&& xs) {
      return std::forward<T>(xs).mapList(std::forward<F>(f));
    }
  } constexpr mapList{};

  template<typename T, typename F>
  concept HasFApplyList = requires(F&& fs, T&& xs) {
    { std::forward<T>(xs).fApplyList(std::forward<F>(fs)) };
  };

  /**
   * @brief Applicative mapping operator for lists
   */
  class FApplyList : public Static_curried<FApplyList, Nat<2>> {
  public:
    template<typename F, HasFApplyList<F> T>
    static constexpr auto
    call(F&& fs, T&& xs) {
      return std::forward<T>(xs).fApplyList(std::forward<F>(fs));
    }
  } constexpr fApplyList{};

  template<typename T, typename F>
  concept HasFlatMapList = requires(F&& f, T&& xs) {
    { std::forward<T>(xs).flatMapList(std::forward<F>(f)) };
  };

  /**
   * @brief Monadic mapping operator for lists
   */
  class FlatMapList : public Static_curried<FlatMapList, Nat<2>> {
  public:
    template<typename F, HasFlatMapList<F> T>
    static constexpr auto
    call(F&& f, T&& xs) {
      return std::forward<T>(xs).flatMapList(std::forward<F>(f));
    }
  } constexpr flatMapList{};

  template<typename T>
  concept HasFlattenList = requires(T&& xss) {
    { std::forward<T>(xss).flattenList() };
  };

  /**
   * @brief Monadic flatten operator for lists
   */
  class FlattenList : public Static_curried<FlattenList, Nat<1>> {
  public:
    template<typename T>
    static constexpr auto
    call(T&& xss) {
      return std::forward<T>(xss).flattenList();
    }
  } constexpr flattenList{};

  template<typename T, typename Pred>
  concept HasFilter = requires(T&& xs, Pred&& pred) {
    { std::forward<T>(xs).filter(std::forward<Pred>(pred)) };
  };

  /**
   * @brief Filter the contents of an input list
   */
  class Filter : public Static_curried<Filter, Nat<2>> {
  public:
    template<typename Pred, HasFilter<Pred> T>
    static constexpr auto
    call(Pred&& pred, T&& xs) {
      return std::forward<T>(xs).filter(std::forward<Pred>(pred));
    }
  } constexpr filter{};

  template<typename T, typename Cmp>
  concept HasSort = requires(T&& xs, Cmp&& cmp) {
    { std::forward<T>(xs).sort(std::forward<Cmp>(cmp)) };
  };

  /**
   * @brief Sort the elements of a list
   */
  class Sort : public Static_curried<Sort, Nat<2>> {
  public:
    template<typename Cmp, HasSort<Cmp> T>
    static constexpr auto
    call(Cmp&& cmp, T&& xs) {
      return std::forward<T>(xs).sort(std::forward<Cmp>(cmp));
    }
  } constexpr sort{};

} // end of namespace ListProcessing::Operators::Details
