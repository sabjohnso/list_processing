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
#include <list_processing/operators.hpp>

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

    STATIC_EXPECT_FALSE(xs != xs);
    STATIC_EXPECT_FALSE(xs != ys);
    STATIC_EXPECT_FALSE(xs != zs);

    STATIC_EXPECT_FALSE(xs == nothing);
    STATIC_EXPECT_FALSE(xs == as);
    STATIC_EXPECT_FALSE(xs == bs);

    STATIC_EXPECT_TRUE(xs != nothing);
    STATIC_EXPECT_TRUE(xs != as);
    STATIC_EXPECT_TRUE(xs != bs);
  }

  TEST(CompileTime, List)
  {
    constexpr auto xs = list(1, 2, 3, 4);
    constexpr auto ys = list(1, 2, 3, 4);
    constexpr auto zs = list(1.0, 2, 3, 4);

    constexpr auto as = list(2, 3, 4, 5);
    constexpr auto bs = list(2.0, 3, 4, 5);

    STATIC_EXPECT_TRUE(islist(xs));
    STATIC_EXPECT_EQ(xs, ys);
    STATIC_EXPECT_EQ(xs, zs);

    STATIC_EXPECT_FALSE(xs == nothing);
    STATIC_EXPECT_FALSE(xs == as);
    STATIC_EXPECT_FALSE(xs == bs);

    STATIC_EXPECT_EQ(length(xs), 4);

    STATIC_EXPECT_EQ(head(xs), 1);
    STATIC_EXPECT_EQ(tail(xs), list(2, 3, 4));

    STATIC_EXPECT_EQ(reverse(xs), list(4, 3, 2, 1));

    STATIC_EXPECT_EQ(take(nat<0>, xs), nothing);
    STATIC_EXPECT_EQ(take(nat<1>, xs), list(1));
    STATIC_EXPECT_EQ(take(nat<2>, xs), list(1, 2));
    STATIC_EXPECT_EQ(take(nat<3>, xs), list(1, 2, 3));
    STATIC_EXPECT_EQ(take(nat<4>, xs), list(1, 2, 3, 4));
    STATIC_EXPECT_EQ(take(nat<5>, xs), list(1, 2, 3, 4));

    STATIC_EXPECT_EQ(drop(nat<0>, xs), xs);
    STATIC_EXPECT_EQ(drop(nat<1>, xs), list(2, 3, 4));
    STATIC_EXPECT_EQ(drop(nat<2>, xs), list(3, 4));
    STATIC_EXPECT_EQ(drop(nat<3>, xs), list(4));
    STATIC_EXPECT_EQ(drop(nat<4>, xs), nothing);
    STATIC_EXPECT_EQ(drop(nat<5>, xs), nothing);

    STATIC_EXPECT_EQ(append(xs, nothing), xs);
    STATIC_EXPECT_EQ(append(nothing, xs), xs);
    STATIC_EXPECT_EQ(append(list(1, 2), list(3, 4)), xs);

    STATIC_EXPECT_EQ(foldl([](auto x, auto y) { return x + y; }, 0, xs), 10);
    STATIC_EXPECT_EQ(foldr([](auto x, auto y) { return std::min(x, y); }, 10, xs), 1);
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

  TEST(CompileTime, FObjFApplyList){
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(
      fApplyList(mapList(curry<2>([](auto x, auto y){ return x+y; }), list(1, 2)), list(3, 4)),
      list(4, 5, 5, 6));
  }

  TEST(CompileTime, FlattenList){
    STATIC_EXPECT_EQ(
      flattenList(list(list(1, 2), nothing, list(3, 4))),
      list(1, 2, 3, 4));
  }

  TEST(CompileTime, FObjFlattenList){
    using namespace ListProcessing::Operators;
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

  TEST(CompileTime, FobjFlatMapList){
    using namespace ListProcessing::Operators;
    constexpr auto flip = curry<3>([](auto f, auto x, auto y){ return f(y, x); });
    STATIC_EXPECT_EQ(
      flatMapList(flip(buildList, identity), list(nat<1>, nat<2>, nat<3>)),
      list(0, 0, 1, 0, 1, 2));
  }

} // end of namespace ListProcessing::Testing
