#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/Zipper.hpp>

namespace ListProcessing::CompileTime::Details
{

  template<typename D, typename C>
  class Tree;

  template<typename D, typename C>
  constexpr Tree<D, C>
  constructTree(D const& d, C const& c);

  template<typename T>
  struct IsTree
    : conditional_t<
        is_same_v<T, decay_t<T>>,
        false_type,
        IsTree<decay_t<T>>>
  {};

  template<typename D, typename C>
  struct IsTree<Tree<D, C>> : true_type
  {};

  template<typename D, typename C>
  class Tree
  {

    static_assert(IsZipper<D>::value);
    static_assert(IsList<C>::value);

  public:
    using Data = D;
    using Context = C;
    constexpr Tree(D const& d, C const& c)
      : data(d)
      , context(c)
    {}

    constexpr Data const&
    getData() const&
    {
      return data;
    }

  private:
    Data data;
    Context context;

    friend constexpr bool
    isRoot(Tree const& xs)
    {
      return isEmpty(xs.context);
    }

    friend constexpr bool
    isEmpty(Tree const& xs)
    {
      return isEmpty(xs.data) && isEmpty(xs.context);
    }

    friend constexpr auto
    fwd(Tree const& xs)
    {
      return constructTree(fwd(xs.data), xs.context);
    }

    friend constexpr auto
    bwd(Tree const& xs)
    {
      return constructTree(bwd(xs.data), xs.context);
    }

    template<offset_type N>
    friend constexpr auto
    moveBy(Tree const& xs, integral_constant<offset_type, N>)
    {
      return constructTree(moveBy(xs.data, idx<N>), xs.context);
    }

    template<index_type N>
    friend constexpr auto
    moveTo(Tree const& xs, integral_constant<index_type, N>)
    {
      return constructTree(moveTo(xs.data, idx<N>), xs.context);
    }

    friend constexpr auto
    toFront(Tree const& xs)
    {
      return constructTree(toFront(xs.data), xs.context);
    }
    friend constexpr auto
    toBack(Tree const& xs)
    {
      constructTree(toBack(xs.data), xs.context);
    }

    template<typename T>
    friend constexpr auto
    insert(Tree const& xs, T const& x)
    {
      return constructTree(insert(xs.data, x), xs.context);
    }

    template<typename T>
    friend constexpr auto
    remove(Tree const& xs)
    {
      return constructTree(remove(xs.data), xs.context);
    }

    friend constexpr auto
    insertBranch(Tree const& xs)
    {
      return constructTree(
        insert(xs.data, constructTree(empty_zipper, nil)), xs.context);
    }

    friend constexpr auto
    open(Tree const& xs)
    {
      if constexpr (IsTree<decltype(read(xs.data))>::value) {
        return constructTree(
          read(xs.data).getData(), cons(remove(xs.data), xs.context));
      } else {
        return read(xs.data);
      }
    }

    friend constexpr auto
    close(Tree const& xs)
    {
      return constructTree(
        write(head(xs.context), constructTree(xs.data, nil)),
        tail(xs.context));
    }

    template<typename Accum>
    static constexpr auto
    positionAux(Nothing const&, Accum const& accum)
    {
      return reverse(accum);
    }

    template<typename L, typename Accum>
    static constexpr auto
    positionAux(L const& ctxs, Accum const& accum)
    {}

    friend constexpr auto
    position(Tree const& xs)
    {
      return positionAux(xs.context, cons(position(xs.data), nil));
    }

    friend constexpr auto
    closeAll(Tree const& xs)
    {
      if constexpr (isRoot(xs)) {
        return xs;
      } else {
        return closeAll(close(xs));
      }
    }

    friend constexpr auto
    operator==(Tree const& xs, Tree const& ys)
    {
      return (xs.data == ys.data) && (xs.context == ys.context);
    }

    friend constexpr auto
    operator!=(Tree const& xs, Tree const& ys)
    {
      return !(xs == ys);
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Tree const& xs)
    {
      os << "#<Tree>";
      return os;
    }

    friend ostream&
    operator<<(ostream& os, Tree const& xs)
    {
      os << "#<Tree>";
      return os;
    }

  }; // end of class Tree

  template<typename D, typename C>
  Tree(D const& d, C const& c) -> Tree<D, C>;

  template<typename D, typename C>
  constexpr Tree<D, C>
  constructTree(D const& d, C const& c)
  {
    return Tree(d, c);
  }

  constexpr auto empty_tree = Tree{ empty_zipper, nil };

  template<typename T, typename... Ts>
  constexpr auto
  tree(T const& x, Ts const&... xs)
  {
    return Tree(makeZipper(x, xs...), nil);
  }

} // end of namespace ListProcessing::CompileTime::Details
