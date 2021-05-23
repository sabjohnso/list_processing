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
#include <list_processing/dynamic_stream.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_stream;
using ListProcessing::Dynamic::Stream;

namespace ListProcessing::Dynamic::Testing {

  TEST(DynamicStream, FriendEmpty) { EXPECT_TRUE(isEmpty(empty_stream<int>)); }

  TEST(DynamicStream, MembEmpty) { EXPECT_TRUE(empty_stream<int>.isEmpty()); }

  TEST(DynamicStream, FObjEmpty) {
    using namespace ListProcessing::Operators;
    EXPECT_TRUE(isEmpty(empty_stream<int>));
  }

  TEST(DynamicStream, FriendEmptyFail) {
    EXPECT_FALSE(isEmpty(Stream(1, Nil{})));
  }

  TEST(DynamicStream, MembEmptyFail) {
    EXPECT_FALSE(Stream(1, Nil{}).isEmpty());
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
    auto xs = iterate(0, [](auto x) { return x + 1; });
    EXPECT_EQ(streamRef(0, xs), 0);
    EXPECT_EQ(streamRef(1, xs), 1);
    EXPECT_EQ(streamRef(100, xs), 100);
  }

  TEST(DynamicStream, MapInfinite) {
    auto xs = map(
      [](auto x) { return x * x; }, iterate(0, [](auto x) { return x + 1; }));
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
    EXPECT_EQ(length(take(10, iterate(0, [](auto x) { return x + 1; }))), 10);
  }

  TEST(DynamicStream, Fold) {}

} // end of namespace ListProcessing::Dynamic::Testing
