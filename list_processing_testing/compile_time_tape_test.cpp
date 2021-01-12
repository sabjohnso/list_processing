//
// ... Testing header files
//
#include <gtest/gtest.h>
#include <list_processing_testing/static_checks.hpp>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_tape;
using ListProcessing::CompileTime::idx;
using ListProcessing::CompileTime::makeTape;

namespace ListProcessing::Testing
{
  TEST(CompileTimeTape, EmptyTapeIsEmpty)
  {
    STATIC_EXPECT_TRUE(isEmpty(empty_tape));
  }

  TEST(CompileTimeTape, MakeTapeisNotEmpty)
  {
    STATIC_EXPECT_FALSE(isEmpty(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, MakeTapeisAtFront)
  {
    STATIC_EXPECT_TRUE(isAtFront(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, MakeTapeNotAtBack)
  {
    STATIC_EXPECT_FALSE(isAtBack(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, FwdNotAtFront)
  {
    STATIC_EXPECT_FALSE(isAtFront(fwd(makeTape('a', 'b', 'c'))));
  }

  TEST(CompileTimeTape, Position)
  {
    STATIC_EXPECT_EQ(position(makeTape('a', 'b', 'c')), 0);
    STATIC_EXPECT_EQ(position(fwd(makeTape('a', 'b', 'c'))), 1);
    STATIC_EXPECT_EQ(position(fwd(fwd(makeTape('a', 'b', 'c')))), 2);
    STATIC_EXPECT_EQ(position(fwd(fwd(fwd(makeTape('a', 'b', 'c'))))), 3);
    STATIC_EXPECT_EQ(
      position(fwd(fwd(fwd(fwd(makeTape('a', 'b', 'c')))))),
      3); // <-- still at back
  }

  TEST(CompileTimeTape, Remaining)
  {
    STATIC_EXPECT_EQ(remaining(makeTape('a', 'b', 'c')), 3);
    STATIC_EXPECT_EQ(remaining(fwd(makeTape('a', 'b', 'c'))), 2);
    STATIC_EXPECT_EQ(remaining(fwd(fwd(makeTape('a', 'b', 'c')))), 1);
    STATIC_EXPECT_EQ(remaining(fwd(fwd(fwd(makeTape('a', 'b', 'c'))))), 0);
  }

  TEST(CompileTimeTape, ToBackAtBack)
  {
    STATIC_EXPECT_TRUE(isAtBack(toBack(makeTape('a', 'b', 'c'))));
  }

  TEST(CompileTimeTape, ToFontAtFront)
  {
    STATIC_EXPECT_TRUE(isAtFront(toFront(toBack(makeTape('a', 'b', 'c')))));
  }

  TEST(CompileTimeTape, MoveBy)
  {
    STATIC_EXPECT_EQ(position(moveBy(idx<0>, makeTape('a', 'b', 'c'))), 0);
    STATIC_EXPECT_EQ(position(moveBy(idx<1>, makeTape('a', 'b', 'c'))), 1);
    STATIC_EXPECT_EQ(position(moveBy(idx<2>, makeTape('a', 'b', 'c'))), 2);
  }

  TEST(CompileTimeTape, MoveByNegative)
  {
    STATIC_EXPECT_EQ(
      position(moveBy(idx<0>, toBack(makeTape('a', 'b', 'c')))), 3);
    STATIC_EXPECT_EQ(
      position(moveBy(idx<-1>, toBack(makeTape('a', 'b', 'c')))), 2);
    STATIC_EXPECT_EQ(
      position(moveBy(idx<-2>, toBack(makeTape('a', 'b', 'c')))), 1);
    STATIC_EXPECT_EQ(
      position(moveBy(idx<-3>, toBack(makeTape('a', 'b', 'c')))), 0);
  }

  TEST(CompileTimeTape, MoveTo)
  {
    STATIC_EXPECT_EQ(position(moveTo(idx<0>, makeTape('a', 'b', 'c'))), 0);
    STATIC_EXPECT_EQ(position(moveTo(idx<1>, makeTape('a', 'b', 'c'))), 1);
    STATIC_EXPECT_EQ(position(moveTo(idx<2>, makeTape('a', 'b', 'c'))), 2);
  }

} // end of namespace ListProcessing::Testing
