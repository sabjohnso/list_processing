//
// ... Standard header files
//
#include <stdexcept>
#include <string>

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
#include <list_processing/dynamic.hpp>

namespace {
  using namespace std::literals::string_literals;
  using std::logic_error;
  using std::to_string;

  using TypeUtility::nat;

  using ListProcessing::Dynamic::list;
  using ListProcessing::Dynamic::nothing;

} // end of anonymous namespace

namespace ListProcessing::Testing {

  TEST(Dynamic, Nothing) {
    ASSERT_TRUE(isnothing(nothing<int>));
    ASSERT_FALSE(hasdata(nothing<int>));
    ASSERT_EQ(length(nothing<int>), 0);
  }

  TEST(Dynamic, List) {
    auto const xs = list(1, 2, 3);
    ASSERT_EQ(length(xs), 3);
    ASSERT_EQ(head(xs), 1);
    ASSERT_EQ(tail(xs), list(2, 3));
    ASSERT_EQ(take(xs, 0), nothing<int>);
    ASSERT_EQ(take(xs, 1), list(1));
    ASSERT_EQ(take(xs, 2), list(1, 2));
    ASSERT_EQ(take(xs, 3), list(1, 2, 3));
    ASSERT_EQ(take(xs, 4), list(1, 2, 3));
    ASSERT_EQ(drop(xs, 0), xs);
    ASSERT_EQ(drop(xs, 1), list(2, 3));
    ASSERT_EQ(drop(xs, 2), list(3));
    ASSERT_EQ(drop(xs, 3), nothing<int>);
    ASSERT_EQ(drop(xs, 4), nothing<int>);

    ASSERT_EQ(reverse(xs), list(3, 2, 1));
    ASSERT_EQ(append(xs, list(4, 5, 6)), list(1, 2, 3, 4, 5, 6));

    ASSERT_EQ(
      map([](auto x) { return std::to_string(x); }, xs),
      list("1"s, "2"s, "3"s));

    ASSERT_EQ(
      map([](auto x, auto y) { return x + y; }, list(1, 2), list(3, 4)),
      list(4, 6));

    ASSERT_EQ(foldl([](auto x, auto y) { return x + y; }, 0, xs), 6);
    ASSERT_EQ(foldr([](auto x, auto y) { return x + y; }, xs, 0), 6);
  }

  TEST(Dynamic, Head) { ASSERT_EQ(head(list(1, 2, 3)), 1); }
  TEST(Dynamic, HeadFail) { ASSERT_THROW(head(nothing<int>), logic_error); }

  TEST(Dynamic, ListRef0) { ASSERT_EQ(listref(list(1, 2, 3), 0), 1); }

  TEST(Dynamic, ListRef1) { ASSERT_EQ(listref(list(1, 2, 3), 1), 2); }

  TEST(Dynamic, ListRef2) { ASSERT_EQ(listref(list(1, 2, 3), 2), 3); }

  TEST(Dynamic, BadListRefLowerBound) {
    ASSERT_THROW(listref(list(1, 2, 3), -1), logic_error);
  }
  TEST(Dynamic, BadListRefUpperBound) {
    ASSERT_THROW(listref(list(1, 2, 3), 4), logic_error);
  }

  TEST(Dynamic, App) {
    ASSERT_EQ(app([](auto x, auto y) { return x + y; }, nat<2>, list(1, 2)), 3);
  }

} // end of namespace ListProcessing::Testing
