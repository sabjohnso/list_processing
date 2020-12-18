//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

namespace {
  using TypeUtility::nat;
  using TypeUtility::type;

  using ListProcessing::CompileTime::cons;
  using ListProcessing::CompileTime::list;
  using ListProcessing::CompileTime::nothing;
    using ListProcessing::CompileTime::length_;

} // end of anonymous namespace

namespace ListProcessing::Testing {

  TEST(CompileTime, Nothing)
  {
    ASSERT_TRUE(islist(nothing));
    ASSERT_FALSE(ispair(nothing));
    ASSERT_TRUE(isnothing(nothing));

    static_assert(islist(nothing));
    static_assert(!(ispair(nothing)));
    static_assert(isnothing(nothing));

    ASSERT_EQ(nothing, nothing);
    ASSERT_EQ(length(nothing), 0);

    static_assert(nothing == nothing);
    static_assert(length(nothing) == 0);

    ASSERT_FALSE(nothing != nothing);

    static_assert(!(nothing != nothing));

    ASSERT_EQ(reverse(nothing), nothing);
    static_assert(reverse(nothing) == nothing);

    ASSERT_EQ(list(), nothing);
    static_assert(list() == nothing);

    ASSERT_EQ(take(nat<0>, nothing), nothing);
    ASSERT_EQ(take(nat<1>, nothing), nothing);
    ASSERT_EQ(take(nat<2>, nothing), nothing);

    ASSERT_EQ(drop(nat<0>, nothing), nothing);
    ASSERT_EQ(drop(nat<1>, nothing), nothing);
    ASSERT_EQ(drop(nat<2>, nothing), nothing);

    {
      constexpr auto xs = app([](){ return 2; }, nothing);
      ASSERT_EQ(xs, 2);
    }
  }

  TEST(CompileTime, Pair)
  {

    constexpr auto xs = cons(1, 'b');
    constexpr auto ys = cons(1, 'b');
    constexpr auto zs = cons(1.0, 'b');

    constexpr auto as = cons(2, 'b');
    constexpr auto bs = cons(2.0, 'b');

    ASSERT_FALSE(islist(xs));
    ASSERT_TRUE(ispair(xs));
    ASSERT_FALSE(isnothing(xs));

    static_assert(!islist(xs));
    static_assert(ispair(xs));
    static_assert(!isnothing(xs));

    ASSERT_TRUE(xs == xs);
    ASSERT_TRUE(xs == ys);
    ASSERT_TRUE(xs == zs);

    static_assert(xs == xs);
    static_assert(xs == ys);
    static_assert(xs == zs);

    ASSERT_FALSE(xs != xs);
    ASSERT_FALSE(xs != ys);
    ASSERT_FALSE(xs != zs);

    static_assert(!(xs != xs));
    static_assert(!(xs != ys));
    static_assert(!(xs != zs));

    ASSERT_FALSE(xs == nothing);
    ASSERT_FALSE(xs == as);
    ASSERT_FALSE(xs == bs);

    static_assert(!(xs == nothing));
    static_assert(!(xs == as));
    static_assert(!(xs == bs));

    ASSERT_TRUE(xs != nothing);
    ASSERT_TRUE(xs != as);
    ASSERT_TRUE(xs != bs);

    static_assert(!islist(xs));
    static_assert(ispair(xs));
    static_assert(!isnothing(xs));
  }

  TEST(CompileTime, List)
  {
    constexpr auto xs = list(1, 2, 3, 4);
    constexpr auto ys = list(1, 2, 3, 4);
    constexpr auto zs = list(1.0, 2, 3, 4);

    constexpr auto as = list(2, 3, 4, 5);
    constexpr auto bs = list(2.0, 3, 4, 5);

    ASSERT_TRUE(islist(xs));
    ASSERT_EQ(xs, ys);
    ASSERT_EQ(xs, zs);

    ASSERT_FALSE(xs == nothing);
    ASSERT_FALSE(xs == as);
    ASSERT_FALSE(xs == bs);

    ASSERT_EQ(length(xs), 4);

    static_assert(length(xs) == 4);

    ASSERT_EQ(head(xs), 1);
    ASSERT_EQ(tail(xs), list(2, 3, 4));

    static_assert(head(xs) == 1);
    static_assert(tail(xs) == list(2, 3, 4));

    ASSERT_EQ(reverse(xs), list(4, 3, 2, 1));
    static_assert(reverse(xs) == list(4, 3, 2, 1));

    ASSERT_EQ(take(nat<0>, xs), nothing);
    ASSERT_EQ(take(nat<1>, xs), list(1));
    ASSERT_EQ(take(nat<2>, xs), list(1, 2));
    ASSERT_EQ(take(nat<3>, xs), list(1, 2, 3));
    ASSERT_EQ(take(nat<4>, xs), list(1, 2, 3, 4));
    ASSERT_EQ(take(nat<5>, xs), list(1, 2, 3, 4));

    static_assert(take(nat<0>, xs) == nothing);
    static_assert(take(nat<1>, xs) == list(1));
    static_assert(take(nat<2>, xs) == list(1, 2));
    static_assert(take(nat<3>, xs) == list(1, 2, 3));
    static_assert(take(nat<4>, xs) == list(1, 2, 3, 4));
    static_assert(take(nat<5>, xs) == list(1, 2, 3, 4));

    ASSERT_EQ(drop(nat<0>, xs), xs);
    ASSERT_EQ(drop(nat<1>, xs), list(2, 3, 4));
    ASSERT_EQ(drop(nat<2>, xs), list(3, 4));
    ASSERT_EQ(drop(nat<3>, xs), list(4));
    ASSERT_EQ(drop(nat<4>, xs), nothing);
    ASSERT_EQ(drop(nat<5>, xs), nothing);

    static_assert(drop(nat<0>, xs) == xs);
    static_assert(drop(nat<1>, xs) == list(2, 3, 4));
    static_assert(drop(nat<2>, xs) == list(3, 4));
    static_assert(drop(nat<3>, xs) == list(4));
    static_assert(drop(nat<4>, xs) == nothing);
    static_assert(drop(nat<5>, xs) == nothing);

    ASSERT_EQ(append(xs, nothing), xs);
    ASSERT_EQ(append(nothing, xs), xs);
    ASSERT_EQ(append(list(1, 2), list(3, 4)), xs);

    static_assert(append(xs, nothing) == xs);
    static_assert(append(nothing, xs) == xs);
    static_assert(append(list(1, 2), list(3, 4)) == xs);

    static_assert(foldl([](auto x, auto y) { return x + y; }, 0, xs) == 10);
    static_assert(
      foldr([](auto x, auto y) { return std::min(x, y); }, 10, xs) == 1);

    static_assert(app([](int x, int y) -> int { return x + y; }, list(1, 2)) ==
                  3);
  }

  TEST(CompileTime, TypeLength){
    static_assert(length_(type<decltype(list(1, 2))>) == 2);
  }

  TEST(CompileTime, ButLast){
    static_assert(butLast(list(1, 2, 3))== list(1, 2));
  }

} // end of namespace ListProcessing::Testing
