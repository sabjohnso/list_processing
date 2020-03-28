//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_tape;
using ListProcessing::Dynamic::tape;

namespace ListProcessing::Testing
{

  TEST(Tape, EmptyTapeIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_tape<int>));
  }
  TEST(Tape, EmptyTapeIsAtFront)
  {
    ASSERT_TRUE(isAtFront(empty_tape<int>));
  }
  TEST(Tape, EmptyTapeIsAtBack)
  {
    ASSERT_TRUE(isAtBack(empty_tape<int>));
  }
  TEST(Tape, EmptyTapeLenghtIs0)
  {
    ASSERT_EQ(length(empty_tape<int>), 0);
  }
  TEST(Tape, EmptyTapePositionIs0)
  {
    ASSERT_EQ(position(empty_tape<int>), 0);
  }
  TEST(Tape, EmptyTapeRemainingIs0)
  {
    ASSERT_EQ(remaining(empty_tape<int>), 0);
  }
  TEST(Tape, EmptyTapeReadThrows)
  {
    ASSERT_THROW(read(empty_tape<int>), std::logic_error);
  }
  TEST(Tape, NotEmpty)
  {
    ASSERT_FALSE(isEmpty(tape(1)));
  }
  TEST(Tape, Length1)
  {
    ASSERT_EQ(length(tape(1)), 1);
  }
  TEST(Tape, Length2)
  {
    ASSERT_EQ(length(tape(1, 2)), 2);
  }
  TEST(Tape, Length3)
  {
    ASSERT_EQ(length(tape(1, 2, 3)), 3);
  }
  TEST(Tape, Remaining1Of1)
  {
    ASSERT_EQ(remaining(tape(1)), 1);
  }
  TEST(Tape, Remaining0Of1)
  {
    ASSERT_EQ(remaining(fwd(tape(1))), 0);
  }
  TEST(Tape, Remaining2Of2)
  {
    ASSERT_EQ(remaining(tape(1, 2)), 2);
  }
  TEST(Tape, Remaining1Of2)
  {
    ASSERT_EQ(remaining(tape(1, 2)), 2);
  }
  TEST(Tape, Remaining0Of2)
  {
    ASSERT_EQ(remaining(moveBy(tape(1, 2), 2)), 0);
  }
  TEST(DynamicTape, FirstPosition)
  {
    ASSERT_EQ(position(tape(1)), 0);
  }
  TEST(DynamicTape, SecondPosition)
  {
    ASSERT_EQ(position(fwd(tape(1))), 1);
  }
  TEST(DynamicTape, FirstPositionAgain)
  {
    ASSERT_EQ(position(bwd(fwd(tape(1)))), 0);
  }
  TEST(DynamicTape, AtFront)
  {
    ASSERT_TRUE(isAtFront(tape(1)));
  }
  TEST(DynamicTape, AtBack)
  {
    ASSERT_TRUE(isAtBack(fwd(tape(1))));
  }
  TEST(DynamicTape, MoveBy0)
  {
    ASSERT_TRUE(isAtFront(moveBy(tape(1, 2), 0)));
  }
  TEST(DynamicTape, MoveBy1)
  {
    ASSERT_EQ(position(moveBy(tape(1, 2), 1)), 1);
  }
  TEST(DynamicTape, MoveBy1AndM1)
  {
    ASSERT_TRUE(isAtFront(moveBy(moveBy(tape(1, 2), 1), -1)));
  }
  TEST(DynamicTape, MoveTo0)
  {
    ASSERT_TRUE(isAtFront(moveTo(tape(1, 2), 0)));
  }
  TEST(DynamicTape, MoveTo2)
  {
    ASSERT_TRUE(isAtBack(moveTo(tape(1, 2), 2)));
  }

} // end of namespace ListProcessing::Testing
