//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_zipper;
using ListProcessing::CompileTime::idx;
using ListProcessing::CompileTime::makeZipper;

namespace ListProcessing::Testing
{
  TEST(CompileTimeZipper, EmptyZipperIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_zipper));
  }

  TEST(CompileTimeZipper, MakeZipperisNotEmpty)
  {
    ASSERT_FALSE(isEmpty(makeZipper('a', 'b', 'c')));
  }

  TEST(CompileTimeZipper, MakeZipperisAtFront)
  {
    ASSERT_TRUE(isAtFront(makeZipper('a', 'b', 'c')));
  }

  TEST(CompileTimeZipper, MakeZipperNotAtBack)
  {
    ASSERT_FALSE(isAtBack(makeZipper('a', 'b', 'c')));
  }

  TEST(CompileTimeZipper, FwdNotAtFront)
  {
    ASSERT_FALSE(isAtFront(fwd(makeZipper('a', 'b', 'c'))));
  }

  TEST(CompileTimeZipper, Position)
  {
    ASSERT_EQ(position(makeZipper('a', 'b', 'c')), 0);
    ASSERT_EQ(position(fwd(makeZipper('a', 'b', 'c'))), 1);
    ASSERT_EQ(position(fwd(fwd(makeZipper('a', 'b', 'c')))), 2);
    ASSERT_EQ(position(fwd(fwd(fwd(makeZipper('a', 'b', 'c'))))), 3);
    ASSERT_EQ(
      position(fwd(fwd(fwd(fwd(makeZipper('a', 'b', 'c')))))),
      3); // <-- still at back
  }

  TEST(CompileTimeZipper, Remaining)
  {
    ASSERT_EQ(remaining(makeZipper('a', 'b', 'c')), 3);
    ASSERT_EQ(remaining(fwd(makeZipper('a', 'b', 'c'))), 2);
    ASSERT_EQ(remaining(fwd(fwd(makeZipper('a', 'b', 'c')))), 1);
    ASSERT_EQ(remaining(fwd(fwd(fwd(makeZipper('a', 'b', 'c'))))), 0);
  }

  TEST(CompileTimeZipper, ToBackAtBack)
  {
    ASSERT_TRUE(isAtBack(toBack(makeZipper('a', 'b', 'c'))));
  }

  TEST(CompileTimeZipper, ToFontAtFront)
  {
    ASSERT_TRUE(isAtFront(toFront(toBack(makeZipper('a', 'b', 'c')))));
  }

  TEST(CompileTimeZipper, MoveBy)
  {
    ASSERT_EQ(position(moveBy(makeZipper('a', 'b', 'c'), idx<0>)), 0);
    ASSERT_EQ(position(moveBy(makeZipper('a', 'b', 'c'), idx<1>)), 1);
    ASSERT_EQ(position(moveBy(makeZipper('a', 'b', 'c'), idx<2>)), 2);
  }

  TEST(CompileTimeZipper, MoveByNegative)
  {
    ASSERT_EQ(
      position(moveBy(toBack(makeZipper('a', 'b', 'c')), idx<0>)), 3);
    ASSERT_EQ(
      position(moveBy(toBack(makeZipper('a', 'b', 'c')), idx<-1>)), 2);
    ASSERT_EQ(
      position(moveBy(toBack(makeZipper('a', 'b', 'c')), idx<-2>)), 1);
    ASSERT_EQ(
      position(moveBy(toBack(makeZipper('a', 'b', 'c')), idx<-3>)), 0);
  }

  TEST(CompileTimeZipper, MoveTo)
  {
    ASSERT_EQ(position(moveTo(makeZipper('a', 'b', 'c'), idx<0>)), 0);
    ASSERT_EQ(position(moveTo(makeZipper('a', 'b', 'c'), idx<1>)), 1);
    ASSERT_EQ(position(moveTo(makeZipper('a', 'b', 'c'), idx<2>)), 2);
  }

} // end of namespace ListProcessing::Testing
