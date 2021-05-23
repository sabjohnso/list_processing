#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/compile_time/CellFwd.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T>
  struct IsList
    : conditional_t<is_same_v<T, decay_t<T>>, false_type, IsList<decay_t<T>>> {
  };

  struct Nothing {

    friend constexpr size_type
    length(Nothing const&) {
      return 0;
    }

    // Predicates
    friend constexpr bool
    islist(Nothing const&) {
      return true;
    }

    friend constexpr bool
    isnothing(Nothing const&) {
      return true;
    }

    friend constexpr bool
    isNull(Nothing const&) {
      return true;
    }

    constexpr bool
    isEmpty() const {
      return true;
    }

    friend constexpr bool
    isEmpty(Nothing const&) {
      return true;
    }

    friend constexpr bool
    ispair(Nothing const&) {
      return false;
    }

    friend constexpr Nothing
    tail(Nothing const& x) {
      return x;
    }

    friend constexpr bool
    operator==(Nothing const&, Nothing const&) {
      return true;
    }

    friend constexpr bool
    operator!=(Nothing const&, Nothing const&) {
      return !(Nothing{} == Nothing{});
    }

    template<typename T>
    friend constexpr bool
    operator==(Nothing const&, T const&) {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator==(T const&, Nothing const&) {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator!=(Nothing const&, T const&) {
      return true;
    }

    template<typename T>
    friend constexpr bool
    operator!=(T const&, Nothing const&) {
      return true;
    }

    constexpr Nothing
    reverse() const {
      return {};
    }

    friend constexpr Nothing
    reverse(Nothing const&) {
      return Nothing{};
    }

    constexpr auto
    rappend(Nothing const&) const {
      return Nothing{};
    }

    template<typename T>
    constexpr auto
    rappend(T const& xs) const {
      return cons(head(xs), Nothing{}).rappend(tail(xs));
    }

    template<typename T>
    friend constexpr auto
    rappend(T const& xs, Nothing const& ys) {
      return ys.rappend(xs);
    }

    template<typename T>
    constexpr auto
    append(T const& xs) const {
      return xs;
    }

    template<typename T>
    friend constexpr auto
    append(T const& xs, Nothing const& ys) {
      return ys.append(xs);
    }

    template<size_t n>
    constexpr auto
    take(Nat<n>) const {
      return Nothing{};
    }

    template<size_t N>
    friend constexpr auto
    take(Nat<N>, Nothing const& xs) {
      return xs.take(nat<N>);
    }

    template<size_t N>
    constexpr auto
    drop(Nat<N>) const {
      return Nothing{};
    }

    template<size_t N>
    friend constexpr auto
    drop(Nat<N>, Nothing const& xs) {
      return xs.drop(nat<N>);
    }

    template<typename F, typename T>
    constexpr auto
    foldl(F const&, T const& init) const {
      return init;
    }

    template<typename F, typename T>
    friend constexpr auto
    foldl(F const& f, T const& init, Nothing const& xs) {
      return xs.foldl(f, init);
    }

    template<typename Fs>
    constexpr auto
    fApplyList(Fs const&) const {
      return Nothing{};
    }

    template<typename Fs>
    friend constexpr auto
    fApplyList(Fs const& fs, Nothing const& xs) {
      return xs.fApplyList(fs);
    }

    template<typename F>
    constexpr auto
    mapList(F const&) const {
      return Nothing{};
    }

    template<typename F>
    friend constexpr auto
    mapList(F const& f, Nothing const& xs) {
      return xs.mapList(f);
    }

    template<typename F, typename... Ts>
    constexpr auto
    applyList(F const& f, Ts const&... xs) const {
      return f(xs...);
    }

    template<typename F>
    friend constexpr auto
    applyList(F const& f, Nothing const& xs) {
      return xs.applyList(f);
    }

    constexpr auto
    flattenList() const {
      return Nothing{};
    }

    friend constexpr auto
    flattenList(Nothing const& xs) {
      return xs.flattenList();
    }

    template<typename F>
    constexpr auto
    flatMapList(F const&) const {
      return Nothing{};
    }

    template<typename F>
    friend constexpr auto
    flatMapList(F const& f, Nothing const& xs) {
      return xs.flatMapList(f);
    }

    template<typename F>
    constexpr Nothing
    filter(F const&) const {
      return {};
    }

    template<typename F>
    friend constexpr Nothing
    filter(F const&, Nothing const&) {
      return {};
    }

    template<typename F>
    constexpr Nothing
    sort(F const&) const {
      return {};
    }

    template<typename F>
    friend constexpr Nothing
    sort(F const&, Nothing const&) {
      return {};
    }

    template<typename F>
    friend void
    doList(Nothing, F) {}

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Nothing const&) {
      os << "nil";
      return os;
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Nothing const&) {
      os << "nil";
      return os;
    }

    template<typename Stream>
    Stream&
    printElements(Stream& os) const {
      return os;
    }

    template<typename Stream>
    friend Stream&
    printElements(Stream& os, Nothing const& xs) {
      return xs.printElements(os);
    }

  }; // end of struct Nothing

  constexpr bool
  length_(Type<Nothing>) {
    return 0;
  }

  template<typename T>
  constexpr bool
  isListType(Type<T>) {
    return false;
  }

  constexpr bool
  isListType(Type<Nothing>) {
    return true;
  }

  constexpr Nothing nothing{};
  constexpr Nothing nil = nothing;

  template<>
  struct IsList<Nothing> : true_type {};

} // end of namespace ListProcessing::CompileTime::Details
