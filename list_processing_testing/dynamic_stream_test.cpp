//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <function_utility/function_utility.hpp>

//
// ... List Processing header files
//
#include <list_processing/dynamic_list.hpp>
#include <list_processing/dynamic_stream.hpp>
#include <list_processing/operators.hpp>

namespace ListProcessing::Dynamic::Testing {

  TEST(DynamicStream, FriendEmpty) { EXPECT_TRUE(isEmpty(empty_stream<int>)); }

  TEST(DynamicStream, MembEmpty) { EXPECT_TRUE(empty_stream<int>.isEmpty()); }

  TEST(DynamicStream, FObjEmpty) {
    using namespace ListProcessing::Operators;
    EXPECT_TRUE(isEmpty(empty_stream<int>));
  }

  TEST(DynamicStream, FriendEmptyFail) {
    EXPECT_FALSE(isEmpty(cons(1, empty_stream<int>)));
  }

  TEST(DynamicStream, MembEmptyFail) {
    EXPECT_FALSE(Stream(1, empty_stream<int>).isEmpty());
  }

  TEST(DynamicStream, FObjEmptyFail) {
    using namespace ListProcessing::Operators;
    EXPECT_FALSE(isEmpty(Stream(1, Nil{})));
  }

  TEST(DynamicStream, FriendCons) {
    EXPECT_EQ(head(cons(1, empty_stream<int>)), 1);
  }

  TEST(DynamicStream, MembCons) {
    EXPECT_EQ(empty_stream<int>.cons(1).head(), 1);
  }

  TEST(DynamicStream, FObjCons) {
    using namespace ListProcessing::Operators;
    EXPECT_EQ(head(cons(1, empty_stream<int>)), 1);
  }

  TEST(DynamicStream, BuildEmpty) {
    EXPECT_TRUE(isEmpty(buildStream(0, [](auto x) { return x; })));
  }

  TEST(DynamicStream, Build1) {
    EXPECT_EQ(head(buildStream(1, [](auto x) { return x; })), 0);
  }

  TEST(DynamicStream, StreamRef) {
    auto xs = streamIterate(0, [](auto x) { return x + 1; });
    EXPECT_EQ(streamRef(0, xs), 0);
    EXPECT_EQ(streamRef(1, xs), 1);
    EXPECT_EQ(streamRef(100, xs), 100);
  }

  TEST(DynamicStream, MapInfinite) {
    auto xs = map([](auto x) { return x * x; }, streamIterate(0, [](auto x) {
                    return x + 1;
                  }));
    EXPECT_EQ(streamRef(0, xs), 0);
    EXPECT_EQ(streamRef(1, xs), 1);
    EXPECT_EQ(streamRef(2, xs), 4);
    EXPECT_EQ(streamRef(3, xs), 9);
  }

  TEST(DynamicStream, MapFinite) {
    auto xs = map(
      [](auto x) { return x * x; }, buildStream(10, [](auto x) { return x; }));
    EXPECT_EQ(streamRef(0, xs), 0);
    EXPECT_EQ(streamRef(1, xs), 1);
    EXPECT_EQ(streamRef(2, xs), 4);
    EXPECT_EQ(streamRef(3, xs), 9);
  }

  TEST(DynamicStream, Take) {
    EXPECT_EQ(
      length(take(10, streamIterate(0, [](auto x) { return x + 1; }))), 10);
  }

  // Testing a stack overflow on destruction of a long stream
  TEST(DynamicStream, Pull) {
    auto xs = buildStream(100000, [](auto) { return 1; });
    xs.pull();
  }

  TEST(DynamicStream, Fold) {

    EXPECT_EQ(
      foldL(
        [](auto x, auto y) { return x + y; },
        0,
        take(4, streamIterate(1, [](auto x) { return x + 1; }))),
      10);

    EXPECT_EQ(
      foldL(
        [](auto x, auto y) { return x + y; },
        0,
        buildStream(4, [](auto x) { return x + 1; })),
      10);

    EXPECT_GT(
      foldL(
        [](auto x, auto y) { return x + y; },
        0,
        buildStream(10000, [](auto) { return 1; })),
      0);

    EXPECT_GT(
      foldL(
        [](auto x, auto y) { return x + y; },
        0,
        take(10000, streamIterate(0, [](auto) { return 1; }))),
      0);
  }

  TEST(DynamicStream, Append) {
    auto xs = append(
      buildStream(2, [](auto x) { return x + 1; }),
      buildStream(2, [](auto x) { return x + 3; }));
    EXPECT_EQ(streamRef(0, xs), 1);
    EXPECT_EQ(streamRef(1, xs), 2);
    EXPECT_EQ(streamRef(2, xs), 3);
    EXPECT_EQ(streamRef(3, xs), 4);
  }

  TEST(DynamicStream, ToList) {
    using ListProcessing::Dynamic::list;
    using ListProcessing::Operators::toList;
    EXPECT_EQ(
      toList(buildStream(3, [](auto x) { return x; })), list(0L, 1L, 2L));
  }

} // end of namespace ListProcessing::Dynamic::Testing
