//
// ... Testing header files
//
#include <gtest/gtest.h>
#include <list_processing_testing/static_checks.hpp>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

#define STATIC_EXPECT_EQ(x, y)                    \
  do{                                             \
    static_assert((x) == (y));                    \
    ASSERT_EQ((x),(y));                           \
  } while(false)

#define STATIC_EXPECT_TRUE(...)                 \
  do{                                           \
    static_assert(__VA_ARGS__);                 \
    ASSERT_TRUE(__VA_ARGS__);                   \
  } while(false)

#define STATIC_EXPECT_FALSE(...)                 \
  do{                                            \
    static_assert(!(__VA_ARGS__));               \
    ASSERT_FALSE(__VA_ARGS__);                   \
  } while(false)

namespace {

  using TypeUtility::nat;
  using TypeUtility::type;
  using FunctionUtility::curry;
  using FunctionUtility::identity;

  using ListProcessing::CompileTime::cons;
  using ListProcessing::CompileTime::list;
  using ListProcessing::CompileTime::nothing;
  using ListProcessing::CompileTime::length_;
  using ListProcessing::CompileTime::buildList;

} // end of anonymous namespace

namespace ListProcessing::Testing {

  TEST(CompileTime, Nothing)
  {
    STATIC_EXPECT_TRUE(islist(nothing));
    STATIC_EXPECT_FALSE(ispair(nothing));
    STATIC_EXPECT_TRUE(isnothing(nothing));
    STATIC_EXPECT_EQ(nothing, nothing);
    STATIC_EXPECT_EQ(length(nothing), 0);
    STATIC_EXPECT_FALSE(nothing != nothing);
    STATIC_EXPECT_EQ(reverse(nothing), nothing);
    STATIC_EXPECT_EQ(list(), nothing);
    STATIC_EXPECT_EQ(take(nat<0>, nothing), nothing);
    STATIC_EXPECT_EQ(take(nat<1>, nothing), nothing);
    STATIC_EXPECT_EQ(take(nat<2>, nothing), nothing);
    STATIC_EXPECT_EQ(drop(nat<0>, nothing), nothing);
    STATIC_EXPECT_EQ(drop(nat<1>, nothing), nothing);
    STATIC_EXPECT_EQ(drop(nat<2>, nothing), nothing);
  }

  TEST(CompileTime, Pair)
  {

    constexpr auto xs = cons(1, 'b');
    constexpr auto ys = cons(1, 'b');
    constexpr auto zs = cons(1.0, 'b');

    constexpr auto as = cons(2, 'b');
    constexpr auto bs = cons(2.0, 'b');

    STATIC_EXPECT_FALSE(islist(xs));
    STATIC_EXPECT_TRUE(ispair(xs));
    STATIC_EXPECT_FALSE(isnothing(xs));

    STATIC_EXPECT_EQ(xs, xs);
    STATIC_EXPECT_EQ(xs, ys);
    STATIC_EXPECT_EQ(xs, zs);


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
    static_assert(foldr([](auto x, auto y) { return std::min(x, y); }, 10, xs) == 1);
  }

  TEST(CompileTime, TypeLength){
    STATIC_EXPECT_EQ(length_(type<decltype(list(1, 2))>), 2);
  }

  TEST(CompileTime, ButLast){
    STATIC_EXPECT_EQ(butLast(list(1, 2, 3)), list(1, 2));
  }

  TEST(CompileTime, ApplyList){
    STATIC_EXPECT_EQ(applyList([](auto x, auto y){ return x + y; }, list(3, 4)), 7);
  }

  TEST(CompileTime, MapList){
    STATIC_EXPECT_EQ(
      mapList([](auto x){ return x*x; }, list(1, 2, 3)),
      list(1, 4, 9));
  }

  TEST(CompileTime, FApplyList){
    STATIC_EXPECT_EQ(
      fApplyList(mapList(curry<2>([](auto x, auto y){ return x+y; }), list(1, 2)), list(3, 4)),
      list(4, 5, 5, 6));
  }

  TEST(CompileTime, FlattenList){
    STATIC_EXPECT_EQ(
      flattenList(list(list(1, 2), nothing, list(3, 4))),
      list(1, 2, 3, 4));
  }

  TEST(CompileTime, BuildListNothing){
    STATIC_EXPECT_EQ(
      buildList(nat<0>, [](auto i){ return i*i; }),
      nothing);
  }

  TEST(CompileTime, BuildList){
    STATIC_EXPECT_EQ(
      buildList(nat<3>, [](auto i){ return i*i; }),
      list(0, 1, 4));
  }

  TEST(CompileTime, FlatMapList){
    constexpr auto flip = curry<3>([](auto f, auto x, auto y){ return f(y, x); });
    STATIC_EXPECT_EQ(
      flatMapList(flip(buildList, identity), list(nat<1>, nat<2>, nat<3>)),
      list(0, 0, 1, 0, 1, 2));
  }



} // end of namespace ListProcessing::Testing
