//
// ... Standard header files
//
#include <iostream>
#include <sstream>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_tape.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_tape;
using ListProcessing::Dynamic::tape;
using std::ostream;

namespace ListProcessing::Testing {

  TEST(Tape, EmptyTapeIsEmpty) { ASSERT_TRUE(isEmpty(empty_tape<int>)); }

  TEST(Tape, FObjeEmptyTapeIsEmpty) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isEmpty(empty_tape<int>));
  }

  TEST(Tape, EmptyTapeIsAtFront) { ASSERT_TRUE(isAtFront(empty_tape<int>)); }

  TEST(Tape, FObjEmptyTapeIsAtFront) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtFront(empty_tape<int>));
  }

  TEST(Tape, EmptyTapeIsAtBack) { ASSERT_TRUE(isAtBack(empty_tape<int>)); }

  TEST(Tape, FObjEmptyTapeIsAtBack) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtBack(empty_tape<int>));
  }

  TEST(Tape, EmptyTapeLenghtIs0) { ASSERT_EQ(length(empty_tape<int>), 0); }

  TEST(Tape, FObjEmptyTapeLenghtIs0) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(length(empty_tape<int>), 0);
  }

  TEST(Tape, EmptyTapePositionIs0) { ASSERT_EQ(position(empty_tape<int>), 0); }

  TEST(Tape, FObjEmptyTapePositionIs0) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(position(empty_tape<int>), 0);
  }

  TEST(Tape, EmptyTapeRemainingIs0) {
    ASSERT_EQ(remaining(empty_tape<int>), 0);
  }

  TEST(Tape, FObjEmptyTapeRemainingIs0) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(empty_tape<int>), 0);
  }

  TEST(Tape, EmptyTapeReadThrows) {
    ASSERT_THROW(read(empty_tape<int>), std::logic_error);
  }

  TEST(Tape, FObjEmptyTapeReadThrows) {
    using namespace ListProcessing::Operators;
    ASSERT_THROW(read(empty_tape<int>), std::logic_error);
  }

  TEST(Tape, NotEmpty) { ASSERT_FALSE(isEmpty(tape(1))); }

  TEST(Tape, FObjNotEmpty) {
    using namespace ListProcessing::Operators;
    ASSERT_FALSE(isEmpty(tape(1)));
  }

  TEST(Tape, Length1) { ASSERT_EQ(length(tape(1)), 1); }

  TEST(Tape, FObjLength1) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(length(tape(1)), 1);
  }

  TEST(Tape, Length2) { ASSERT_EQ(length(tape(1, 2)), 2); }

  TEST(Tape, FObjLength2) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(length(tape(1, 2)), 2);
  }

  TEST(Tape, Length3) { ASSERT_EQ(length(tape(1, 2, 3)), 3); }

  TEST(Tape, FObjLength3) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(length(tape(1, 2, 3)), 3);
  }

  TEST(Tape, Remaining1Of1) { ASSERT_EQ(remaining(tape(1)), 1); }

  TEST(Tape, FObjRemaining1Of1) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(tape(1)), 1);
  }

  TEST(Tape, Remaining0Of1) { ASSERT_EQ(remaining(fwd(tape(1))), 0); }

  TEST(Tape, FObjRemaining0Of1) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(fwd(tape(1))), 0);
  }

  TEST(Tape, Remaining2Of2) { ASSERT_EQ(remaining(tape(1, 2)), 2); }

  TEST(Tape, FObjRemaining2Of2) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(tape(1, 2)), 2);
  }

  TEST(Tape, Remaining1Of2) { ASSERT_EQ(remaining(tape(1, 2)), 2); }

  TEST(Tape, FObjRemaining1Of2) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(tape(1, 2)), 2);
  }

  TEST(Tape, Remaining0Of2) { ASSERT_EQ(remaining(moveBy(2, tape(1, 2))), 0); }

  TEST(Tape, FObjRemaining0Of2) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(remaining(moveBy(2, tape(1, 2))), 0);
  }

  TEST(DynamicTape, FirstPosition) { ASSERT_EQ(position(tape(1)), 0); }

  TEST(DynamicTape, FObjFirstPosition) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(position(tape(1)), 0);
  }

  TEST(DynamicTape, SecondPosition) { ASSERT_EQ(position(fwd(tape(1))), 1); }

  TEST(DynamicTape, FObjSecondPosition) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(position(fwd(tape(1))), 1);
  }

  TEST(DynamicTape, FirstPositionAgain) {
    ASSERT_EQ(position(bwd(fwd(tape(1)))), 0);
  }

  TEST(DynamicTape, FObjFirstPositionAgain) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(position(bwd(fwd(tape(1)))), 0);
  }

  TEST(DynamicTape, AtFront) { ASSERT_TRUE(isAtFront(tape(1))); }

  TEST(DynamicTape, FObjAtFront) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtFront(tape(1)));
  }

  TEST(DynamicTape, AtBack) { ASSERT_TRUE(isAtBack(fwd(tape(1)))); }

  TEST(DynamicTape, FObjAtBack) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtBack(fwd(tape(1))));
  }

  TEST(DynamicTape, MoveBy0) { ASSERT_TRUE(isAtFront(moveBy(0, tape(1, 2)))); }

  TEST(DynamicTape, FObjMoveBy0) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtFront(moveBy(0, tape(1, 2))));
  }

  TEST(DynamicTape, MoveBy1) { ASSERT_EQ(position(moveBy(1, tape(1, 2))), 1); }

  TEST(DynamicTape, FObjMoveBy1) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(position(moveBy(1, tape(1, 2))), 1);
  }

  TEST(DynamicTape, MoveBy1AndM1) {
    ASSERT_TRUE(isAtFront(moveBy(-1, moveBy(1, tape(1, 2)))));
  }

  TEST(DynamicTape, FObjMoveBy1AndM1) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtFront(moveBy(-1, moveBy(1, tape(1, 2)))));
  }

  TEST(DynamicTape, MoveTo0) { ASSERT_TRUE(isAtFront(moveTo(0, tape(1, 2)))); }

  TEST(DynamicTape, FObjMoveTo0) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtFront(moveTo(0, tape(1, 2))));
  }

  TEST(DynamicTape, MoveTo2) { ASSERT_TRUE(isAtBack(moveTo(2, tape(1, 2)))); }

  TEST(DynamicTape, FObjMoveTo2) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isAtBack(moveTo(2, tape(1, 2))));
  }

  TEST(DynamicTape, SpliceAppend) {
    ASSERT_EQ(splice(tape(1, 2), tape(3, 4)), tape(1, 2, 3, 4));
  }

  TEST(DynamicTape, FObjSpliceAppend) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(splice(tape(1, 2), tape(3, 4)), tape(1, 2, 3, 4));
  }

  TEST(DynamicTape, SplicePrepend) {
    ASSERT_EQ(
      toFront(splice(fwd(tape(1, 2)), fwd(tape(3, 4)))), tape(3, 1, 2, 4));
  }

  TEST(DynamicTape, FObjSplicePrepend) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(
      toFront(splice(fwd(tape(1, 2)), fwd(tape(3, 4)))), tape(3, 1, 2, 4));
  }

  TEST(DynamicTape, Reverse) {
    ASSERT_EQ(toFront(reverse(tape(1, 2, 3, 4))), tape(4, 3, 2, 1));
  }

  TEST(DynamicTape, FObjReverse) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(toFront(reverse(tape(1, 2, 3, 4))), tape(4, 3, 2, 1));
  }

  TEST(DynamicTape, Erase) { EXPECT_EQ(erase(tape(1, 2, 3)), tape(2, 3)); }

  TEST(DynamicTape, FObjErase) {
    using namespace ListProcessing::Operators;
    EXPECT_EQ(erase(tape(1, 2, 3)), tape(2, 3));
  }

  TEST(DynamicTape, PrintEmtpy) {
    std::stringstream ss;
    ss << empty_tape<int>;
    EXPECT_EQ(ss.str(), "tape([])");
  }

  TEST(DynamicTape, PrintFront) {
    std::stringstream ss;
    ss << tape(1, 2, 3);
    EXPECT_EQ(ss.str(), "tape([1]...)");
  }

  TEST(DynamicTape, PrintBack) {
    std::stringstream ss;
    ss << toBack(tape(1, 2, 3));
    EXPECT_EQ(ss.str(), "tape(...[])");
  }

  TEST(DynamicTape, Print) {
    std::stringstream ss;
    ss << fwd(tape(1, 2, 3));
    EXPECT_EQ(ss.str(), "tape(...[2]...)");
  }

} // end of namespace ListProcessing::Testing
