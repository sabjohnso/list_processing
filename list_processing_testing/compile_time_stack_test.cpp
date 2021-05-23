//
// ... Testing header files
//
#include <gtest/gtest.h>
#include <list_processing_testing/static_checks.hpp>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::CompileTime::empty_stack;
using ListProcessing::CompileTime::make_stack;

namespace ListProcessing::Testing {

  using ListProcessing::Operators::pipe;

  TEST(CompileTimeStack, EmptyStackIsEmpty) {
    STATIC_EXPECT_TRUE(isEmpty(empty_stack));
  }

  TEST(CompileTimeStack, FObjEmptyStackIsEmpty) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_TRUE(isEmpty(empty_stack));
  }

  TEST(CompileTimeStack, PushStackIsNotEmpty) {
    STATIC_EXPECT_FALSE(isEmpty(push('x', empty_stack)));
  }

  TEST(CompileTimeStack, FObjPushStackIsNotEmpty) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_FALSE(isEmpty(push('x', empty_stack)));
  }

  TEST(CompileTimeStack, TopOfPushIsPushedValue) {
    STATIC_EXPECT_EQ(top(push('x', empty_stack)), 'x');
  }

  TEST(CompileTimeStack, FObjTopOfPushIsPushedValue) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(top(push('x', empty_stack)), 'x');
  }

  TEST(CompileTimeStack, Dup) {
    STATIC_EXPECT_EQ(dup(make_stack('x')), make_stack('x', 'x'));
  }

  TEST(CompileTimeStack, FObjDup) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(dup(make_stack('x')), make_stack('x', 'x'));
  }

  TEST(CompileTimeStack, Swap) {
    STATIC_EXPECT_EQ(swap(make_stack('y', 'x')), make_stack('x', 'y'));
  }

  TEST(CompileTimeStack, FObjSwap) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(swap(make_stack('y', 'x')), make_stack('x', 'y'));
  }

  TEST(CompileTimeStack, Nip) {
    STATIC_EXPECT_EQ(nip(make_stack('x', 'y')), make_stack('x'));
  }

  TEST(CompileTimeStack, FObjNip) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(nip(make_stack('x', 'y')), make_stack('x'));
  }

  TEST(CompileTimeStack, Tuck) {
    STATIC_EXPECT_EQ(tuck(make_stack('x', 'y')), make_stack('x', 'y', 'x'));
  }

  TEST(CompileTimeStack, FObjTuck) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(tuck(make_stack('x', 'y')), make_stack('x', 'y', 'x'));
  }

  TEST(CompileTimeStack, Over) {
    STATIC_EXPECT_EQ(over(make_stack('x', 'y')), make_stack('y', 'x', 'y'));
  }

  TEST(CompileTimeStack, FObjOver) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(over(make_stack('x', 'y')), make_stack('y', 'x', 'y'));
  }

  TEST(CompileTimeStack, Rot) {
    STATIC_EXPECT_EQ(rot(make_stack('x', 'y', 'z')), make_stack('z', 'x', 'y'));
  }

  TEST(CompileTimeStack, FObjRot) {
    using namespace ListProcessing::Operators;
    STATIC_EXPECT_EQ(rot(make_stack('x', 'y', 'z')), make_stack('z', 'x', 'y'));
  }

} // end of namespace ListProcessing::Testing
