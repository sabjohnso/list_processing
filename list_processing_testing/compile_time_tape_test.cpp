//
// ... Testing header files
//
#include <gtest/gtest.h>

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
    ASSERT_TRUE(isEmpty(empty_tape));
  }

  TEST(CompileTimeTape, MakeTapeisNotEmpty)
  {
    ASSERT_FALSE(isEmpty(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, MakeTapeisAtFront)
  {
    ASSERT_TRUE(isAtFront(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, MakeTapeNotAtBack)
  {
    ASSERT_FALSE(isAtBack(makeTape('a', 'b', 'c')));
  }

  TEST(CompileTimeTape, FwdNotAtFront)
  {
    ASSERT_FALSE(isAtFront(fwd(makeTape('a', 'b', 'c'))));
  }

  TEST(CompileTimeTape, Position)
  {
    ASSERT_EQ(position(makeTape('a', 'b', 'c')), 0);
    ASSERT_EQ(position(fwd(makeTape('a', 'b', 'c'))), 1);
    ASSERT_EQ(position(fwd(fwd(makeTape('a', 'b', 'c')))), 2);
    ASSERT_EQ(position(fwd(fwd(fwd(makeTape('a', 'b', 'c'))))), 3);
    ASSERT_EQ(
      position(fwd(fwd(fwd(fwd(makeTape('a', 'b', 'c')))))),
      3); // <-- still at back
  }

  TEST(CompileTimeTape, Remaining)
  {
    ASSERT_EQ(remaining(makeTape('a', 'b', 'c')), 3);
    ASSERT_EQ(remaining(fwd(makeTape('a', 'b', 'c'))), 2);
    ASSERT_EQ(remaining(fwd(fwd(makeTape('a', 'b', 'c')))), 1);
    ASSERT_EQ(remaining(fwd(fwd(fwd(makeTape('a', 'b', 'c'))))), 0);
  }

  TEST(CompileTimeTape, ToBackAtBack)
  {
    ASSERT_TRUE(isAtBack(toBack(makeTape('a', 'b', 'c'))));
  }

  TEST(CompileTimeTape, ToFontAtFront)
  {
    ASSERT_TRUE(isAtFront(toFront(toBack(makeTape('a', 'b', 'c')))));
  }

  TEST(CompileTimeTape, MoveBy)
  {
    ASSERT_EQ(position(moveBy(idx<0>, makeTape('a', 'b', 'c'))), 0);
    ASSERT_EQ(position(moveBy(idx<1>, makeTape('a', 'b', 'c'))), 1);
    ASSERT_EQ(position(moveBy(idx<2>, makeTape('a', 'b', 'c'))), 2);
  }

  TEST(CompileTimeTape, MoveByNegative)
  {
    ASSERT_EQ(
      position(moveBy(idx<0>, toBack(makeTape('a', 'b', 'c')))), 3);
    ASSERT_EQ(
      position(moveBy(idx<-1>, toBack(makeTape('a', 'b', 'c')))), 2);
    ASSERT_EQ(
      position(moveBy(idx<-2>, toBack(makeTape('a', 'b', 'c')))), 1);
    ASSERT_EQ(
      position(moveBy(idx<-3>, toBack(makeTape('a', 'b', 'c')))), 0);
  }

  TEST(CompileTimeTape, MoveTo)
  {
    ASSERT_EQ(position(moveTo(idx<0>, makeTape('a', 'b', 'c'))), 0);
    ASSERT_EQ(position(moveTo(idx<1>, makeTape('a', 'b', 'c'))), 1);
    ASSERT_EQ(position(moveTo(idx<2>, makeTape('a', 'b', 'c'))), 2);
  }

} // end of namespace ListProcessing::Testing
