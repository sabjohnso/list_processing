#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/CellFwd.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T>
  constexpr bool
  ispair_type(Type<T>) {
    return false;
  }

  template<typename T, typename U>
  constexpr bool
  ispair_type(Type<Cell<T, U>>) {
    return true;
  }

  template<typename T, typename U>
  constexpr size_type
  length_(Type<Cell<T, U>>) {
    return 1 + length_(type<U>);
  }

  template<typename T, typename U>
  constexpr bool
  isListType(Type<Cell<T, U>>) {
    return isListType(type<U>);
  }

  template<typename T, typename U>
  class Cell : pair<T, U> {
  public:
    using HeadType = T;
    using TailType = U;
    using pair<T, U>::pair;
    using base = pair<T, U>;

  private:
    //  _                _
    // | |_  ___ __ _ __| |
    // | ' \/ -_) _` / _` |
    // |_||_\___\__,_\__,_|
  public:
    constexpr auto
    head() const {
      return base::first;
    }

    friend constexpr auto
    head(Cell const& xs) {
      return xs.head();
    }

    //  _        _ _
    // | |_ __ _(_) |
    // |  _/ _` | | |
    //  \__\__,_|_|_|

    constexpr auto
    tail() const {
      return base::second;
    }

    friend constexpr auto
    tail(Cell const& xs) {
      return xs.tail();
    }

    //  _    _ _    _
    // (_)__| (_)__| |_
    // | (_-< | (_-<  _|
    // |_/__/_|_/__/\__|

    constexpr bool
    islist() const {
      return isListType(type<TailType>);
    }

    friend constexpr bool
    islist(Cell const& xs) {
      return xs.islist();
    }

    //  _             _   _    _
    // (_)____ _  ___| |_| |_ (_)_ _  __ _
    // | (_-< ' \/ _ \  _| ' \| | ' \/ _` |
    // |_/__/_||_\___/\__|_||_|_|_||_\__, |
    //                               |___/

    constexpr bool
    isnothing() const {
      return false;
    }

    friend constexpr bool
    isnothing(Cell const& xs) {
      return xs.isnothing();
    }

    //  _    _  _      _ _
    // (_)__| \| |_  _| | |
    // | (_-< .` | || | | |
    // |_/__/_|\_|\_,_|_|_|

    constexpr bool
    isNull() const {
      return isnothing();
    }

    friend constexpr bool
    isNull(Cell const& xs) {
      return xs.isNull();
    }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/

    constexpr bool
    isEmpty() const {
      return isnothing();
    }

    friend constexpr bool
    isEmpty(Cell const& xs) {
      return xs.isEmpty();
    }

    //  _               _
    // (_)____ __  __ _(_)_ _
    // | (_-< '_ \/ _` | | '_|
    // |_/__/ .__/\__,_|_|_|
    //      |_|

    constexpr bool
    ispair() const {
      return true;
    }

    friend constexpr bool
    ispair(Cell const& xs) {
      return xs.ispair();
    }

    //  ___ ___
    // |___|___|
    // |___|___|

    constexpr bool friend
    operator==(Cell const& xs, Cell const& ys) {
      return xs.head() == ys.head() && xs.tail() == ys.tail();
    }

    template<typename V, typename W>
    friend constexpr bool
    operator==(Cell const& xs, Cell<V, W> const& ys) {
      return xs.head() == ys.head() && xs.tail() == ys.tail();
    }

    template<
      typename V,
      typename Check = enable_if_t<!ispair_type(type<V>), void>>
    friend constexpr bool
    operator==(Cell const&, V const&) {
      return false;
    }

    template<
      typename V,
      typename Check = enable_if_t<!ispair_type(type<V>), void>>
    friend constexpr bool
    operator==(V const&, Cell const&) {
      return false;
    }

    friend constexpr bool
    operator==(Cell const&, Nothing const&) {
      return false;
    }

    friend constexpr bool
    operator==(Nothing const&, Cell const&) {
      return false;
    }

    //  _
    // | |___
    // |_|___|
    // (_)___|

    friend constexpr bool
    operator!=(Cell const& xs, Nothing const& y) {
      return !(xs == y);
    }

    friend constexpr bool
    operator!=(Nothing const& x, Cell const& ys) {
      return !(x == ys);
    }

    template<typename V>
    friend constexpr bool
    operator!=(Cell const& xs, V const& y) {
      return !(xs == y);
    }

    //  _               _   _
    // | |___ _ _  __ _| |_| |_
    // | / -_) ' \/ _` |  _| ' \.
    // |_\___|_||_\__, |\__|_||_|
    //            |___/

    constexpr size_type
    length() const {
      return length_(type<Cell>);
    }

    friend constexpr size_type
    length(Cell const& xs) {
      return xs.length();
    }

    //                                  _
    //  _ _ __ _ _ __ _ __  ___ _ _  __| |
    // | '_/ _` | '_ \ '_ \/ -_) ' \/ _` |
    // |_| \__,_| .__/ .__/\___|_||_\__,_|
    //          |_|  |_|

    constexpr auto
    rappend(Nothing const&) const {
      return *this;
    }

    template<typename V>
    constexpr auto
    rappend(V const& xs) const {
      return cons(xs.head(), *this).rappend(xs.tail());
    }

    template<typename V>
    friend constexpr auto
    rappend(V const& xs, Cell const& ys) {
      return ys.rappend(xs);
    }

    //  _ _ _____ _____ _ _ ___ ___
    // | '_/ -_) V / -_) '_(_-</ -_)
    // |_| \___|\_/\___|_| /__/\___|

    constexpr auto
    reverse() const {
      return nothing.rappend(*this);
    }

    friend constexpr auto
    reverse(Cell const& xs) {
      return xs.reverse();
    }

    //                              _
    //  __ _ _ __ _ __  ___ _ _  __| |
    // / _` | '_ \ '_ \/ -_) ' \/ _` |
    // \__,_| .__/ .__/\___|_||_\__,_|
    //      |_|  |_|

    constexpr auto
    append(Nothing const&) const {
      return *this;
    }

    template<typename V>
    constexpr auto
    append(V const& xs) const {
      return rappend(xs.reverse());
    }

    template<typename V>
    friend constexpr auto
    append(V const& xs, Cell const& ys) {
      return ys.append(xs);
    }

    constexpr auto
    listRef(Nat<0>) const {
      return head();
    }

    template<size_t N>
    constexpr auto
    listRef(Nat<N>) const {
      return tail().listRef(nat<N - 1>);
    }

    template<size_t N>
    friend constexpr auto
    listRef(Nat<N>, Cell const& xs) {
      static_assert(N < length_(type<Cell>));
      return xs.listRef(nat<N>);
    }

    constexpr auto
    take(Nat<0>) const {
      return nothing;
    }

    template<size_t N>
    constexpr auto
    take(Nat<N>) const {
      return cons(head(), tail().take(nat<N - 1>));
    }

    template<size_t N>
    friend constexpr auto
    take(Nat<N>, Cell const& xs) {
      return xs.take(nat<N>);
    }

    constexpr auto
    drop(Nat<0>) const {
      return *this;
    }

    template<size_t N>
    constexpr auto
    drop(Nat<N>) const {
      return tail().drop(nat<N - 1>);
    }

    template<size_t N>
    friend constexpr auto
    drop(Nat<N>, Cell const& xs) {
      return xs.drop(nat<N>);
    }

    constexpr auto
    butLast() const {
      return reverse().tail().reverse();
    }

    friend constexpr auto
    butLast(Cell const& xs) {
      return xs.butLast();
    }

    template<typename F, typename V>
    constexpr auto
    foldl(F f, V const& init) const {
      return tail().foldl(f, f(init, head()));
    }

    template<typename F, typename V>
    friend constexpr auto
    foldl(F f, V const& init, Cell const& xs) {
      return xs.foldl(f, init);
    }

    template<typename F, typename V>
    constexpr auto
    foldr(F f, V const& init) const {
      return reverse().foldl([=](auto x, auto y) { return f(y, x); }, init);
    }

    template<typename F, typename V>
    friend constexpr auto
    foldr(F f, V const& init, Cell const& xs) {
      return xs.foldr(f, init);
    }

    template<typename F>
    constexpr auto
    mapList(F f) const {
      return cons(f(head()), tail().mapList(f));
    }

    template<typename F>
    friend constexpr auto
    mapList(F f, Cell const& xs) {
      return xs.mapList(f);
    }

    constexpr auto
    fApplyList(Nothing const&) const {
      return nothing;
    }

    template<typename Fs>
    constexpr auto
    fApplyList(Fs const& fs) const {
      return fApplyList(fs.tail()).append(mapList(fs.head()));
    }

    template<typename Fs>
    friend constexpr auto
    fApplyList(Fs const& fs, Cell const& xs) {
      return xs.fApplyList(fs);
    }

    template<typename Fs, typename... Ts>
    constexpr auto
    applyList(Fs const& fs, Ts const&... xs) const {
      return tail().applyList(fs, xs..., head());
    }

    template<typename Fs>
    friend constexpr auto
    applyList(Fs const& fs, Cell const& xs) {
      return xs.applyList(fs);
    }

    constexpr auto
    flattenList() const {
      return tail().flattenList().append(head());
    }

    friend constexpr auto
    flattenList(Cell const& xs) {
      return xs.flattenList();
    }

    template<typename F>
    constexpr auto
    flatMapList(F const& f) const {
      return mapList(f).flattenList();
    }

    template<typename F>
    friend constexpr auto
    flatMapList(F const& f, Cell const& xs) {
      return xs.flatMapList(f);
    }

    template<typename F, typename Accum>
    static constexpr auto
    filterAux(F const&, Nothing const&, Accum const& accum) {
      return accum.reverse();
    }

    template<typename Pred, typename V, typename W, typename Accum>
    static constexpr auto
    filterAux(Pred const& pred, Cell<V, W> const& xs, Accum const& accum) {
      if constexpr (Pred{}(V{})) {
        return filterAux(pred, xs.tail(), cons(xs.head(), accum));
      } else {
        return filterAux(pred, xs.tail(), accum);
      }
    }

    template<typename Pred>
    constexpr auto
    filter(Pred const& pred) const {
      return filterAux(pred, *this, nothing);
    }

    template<typename F>
    friend constexpr auto
    filter(F const& pred, Cell const& xs) {
      return filterAux(pred, xs, nothing);
    }

    template<typename Cmp, typename V>
    struct PartialRelation {
      template<typename W>
      constexpr bool
      operator()(W const&) const {
        return Cmp{}(V{}, W{});
      }
    };

    template<typename Cmp, typename V>
    struct NegatePartialRelation {
      template<typename W>
      constexpr bool
      operator()(W const&) const {
        constexpr bool result = !(Cmp{}(V{}, W{}));
        return result;
      }
    };

    template<typename Cmp>
    static constexpr Nothing
    sortAux(Cmp const&, Nothing) {
      return nothing;
    }

    template<typename Cmp, typename V>
    static constexpr Cell<V, Nothing>
    sortAux(Cmp const&, Cell<V, Nothing> const& xs) {
      return xs;
    }

    template<typename Cmp, typename V, typename W>
    static constexpr auto
    sortAux(Cmp const& cmp, Cell<V, W> const& xs) {
      return cons(
               xs.head(),
               sortAux(cmp, xs.tail().filter(PartialRelation<Cmp, V>{})))
        .append(
          sortAux(cmp, xs.tail().filter(NegatePartialRelation<Cmp, V>{})));
    }

    template<typename F>
    constexpr auto
    sort(F const& cmp) const {
      return sortAux(cmp, *this);
    }

    template<typename F>
    friend constexpr auto
    sort(F const& cmp, Cell const& xs) {
      return sortAux(cmp, xs);
    }

    template<typename F>
    friend void
    doList(Cell const& xs, F f) {
      f(xs.head());
      doList(xs.tail(), f);
    }

    template<typename Stream>
    Stream&
    printElements(Stream& os) const {
      os << head();
      if constexpr (ispair_type(type<U>)) {
        os << ' ';
        tail().printElements(os);
      } else if constexpr (!is_same_v<U, Nothing>) {
        os << " . ";
        os << tail();
      }
      return os;
    }

    template<typename Stream>
    Stream&
    printList(Stream& os) const {
      os << '(';
      printElements(os);
      os << ')';
      return os;
    }

    template<typename Stream>
    friend Stream&
    printList(Stream& os, Cell const& xs) {
      xs.printList(os);
      return os;
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Cell const& xs) {
      return xs.printList(os);
    }

    // This concrete stream type implementation
    // is to disambiguate the ostream operators when
    // using gtest.
    friend ostream&
    operator<<(ostream& os, Cell const& xs) {
      return xs.printList(os);
    }

  }; // end of class Cell

  class List : public Static_callable<List> {
  public:
    static constexpr auto
    call() {
      return nothing;
    }

    template<typename T, typename... Ts>
    static constexpr auto
    call(T&& x, Ts&&... xs) {
      return cons(forward<T>(x), call(forward<Ts>(xs)...));
    }
  } constexpr list{};

  template<typename T, typename U>
  struct IsList<Cell<T, U>> : IsList<U> {};

  class BuildList : public Static_curried<BuildList, Nat<2>> {
  public:
    template<size_t N, typename F>
    static constexpr auto
    call(Nat<N>, F const& f) {
      return aux(nat<N>, f, nat<0>, nothing);
    }

  private:
    template<size_t N, typename F, size_t M, typename T>
    static constexpr auto
    aux(Nat<N>, F const& f, Nat<M>, T const accum) {
      if constexpr (N == M) {
        return reverse(accum);
      } else {
        return aux(nat<N>, f, nat<M + 1>, cons(f(index_type{ M }), accum));
      }
    }
  } constexpr buildList{};

  template<typename... Ts>
  using ListType = decltype(list(std::declval<Ts>()...));

} // end of namespace ListProcessing::CompileTime::Details
