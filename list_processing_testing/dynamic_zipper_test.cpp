//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_zipper;
using ListProcessing::Dynamic::zipper;

namespace ListProcessing::Testing
{

  TEST(Zipper, EmptyZipperIsEmpty) { ASSERT_TRUE(isEmpty(empty_zipper<int>)); }
  TEST(Zipper, EmptyZipperIsAtFront) { ASSERT_TRUE(isAtFront(empty_zipper<int>)); }
  TEST(Zipper, EmptyZipperIsAtBack) { ASSERT_TRUE(isAtBack(empty_zipper<int>)); }
  TEST(Zipper, EmptyZipperLenghtIs0) { ASSERT_EQ(length(empty_zipper<int>), 0); }
  TEST(Zipper, EmptyZipperPositionIs0) { ASSERT_EQ(position(empty_zipper<int>), 0); }
  TEST(Zipper, EmptyZipperRemainingIs0) { ASSERT_EQ(remaining(empty_zipper<int>), 0); }
  TEST(Zipper, EmptyZipperReadThrows) { ASSERT_THROW(read(empty_zipper<int>), std::logic_error); }
  TEST(Zipper, NotEmpty) { ASSERT_FALSE(isEmpty(zipper(1))); }
  TEST(Zipper, Length1) { ASSERT_EQ(length(zipper(1)), 1); }
  TEST(Zipper, Length2) { ASSERT_EQ(length(zipper(1, 2)), 2); }
  TEST(Zipper, Length3) { ASSERT_EQ(length(zipper(1, 2, 3)), 3); }
  TEST(Zipper, Remaining1Of1) { ASSERT_EQ(remaining(zipper(1)), 1); }
  TEST(Zipper, Remaining0Of1) { ASSERT_EQ(remaining(fwd(zipper(1))), 0); }
  TEST(Zipper, Remaining2Of2) { ASSERT_EQ(remaining(zipper(1, 2)), 2); }
  TEST(Zipper, Remaining1Of2) { ASSERT_EQ(remaining(zipper(1, 2)), 2); }
  TEST(Zipper, Remaining0Of2) { ASSERT_EQ(remaining(moveBy(zipper(1, 2), 2)), 0); }
  TEST(DynamicZipper, FirstPosition) { ASSERT_EQ(position(zipper(1)), 0); }
  TEST(DynamicZipper, SecondPosition) { ASSERT_EQ(position(fwd(zipper(1))), 1); }
  TEST(DynamicZipper, FirstPositionAgain) { ASSERT_EQ(position(bwd(fwd(zipper(1)))), 0); }
  TEST(DynamicZipper, AtFront) { ASSERT_TRUE(isAtFront(zipper(1))); }
  TEST(DynamicZipper, AtBack) { ASSERT_TRUE(isAtBack(fwd(zipper(1)))); }
  TEST(DynamicZipper, MoveBy0) { ASSERT_TRUE(isAtFront(moveBy(zipper(1, 2), 0))); }
  TEST(DynamicZipper, MoveBy1) { ASSERT_EQ(position(moveBy(zipper(1, 2), 1)), 1); }
  TEST(DynamicZipper, MoveBy1AndM1) { ASSERT_TRUE(isAtFront(moveBy(moveBy(zipper(1, 2), 1), -1))); }
  TEST(DynamicZipper, MoveTo0) { ASSERT_TRUE(isAtFront(moveTo(zipper(1, 2), 0))); }
  TEST(DynamicZipper, MoveTo2) { ASSERT_TRUE(isAtBack(moveTo(zipper(1, 2), 2))); }

} // end of namespace ListProcessing::Testing
