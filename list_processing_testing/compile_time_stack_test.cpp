//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_stack;
using ListProcessing::CompileTime::make_stack;
using ListProcessing::CompileTime::pipe;

namespace ListProcessing::Testing
{
  TEST(CompileTimeStack, EmptyStackIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_stack));
    static_assert(isEmpty(empty_stack));
  }

  TEST(CompileTimeStack, PushStackIsNotEmpty)
  {
    ASSERT_FALSE(isEmpty(push(empty_stack, 'x')));
    static_assert(!isEmpty(push(empty_stack, 'x')));
  }

  TEST(CompileTimeStack, TopOfPushIsPushedValue)
  {
    ASSERT_EQ(top(push(empty_stack, 'x')), 'x');
    static_assert(top(push(empty_stack, 'x')) == 'x');
  }

  TEST(CompileTimeStack, Dup)
  {
    ASSERT_EQ(dup(make_stack('x')), make_stack('x', 'x'));
    static_assert(dup(make_stack('x')) == make_stack('x', 'x'));
  }

  TEST(CompileTimeStack, Swap)
  {
    ASSERT_EQ(swap(make_stack('y', 'x')), make_stack('x', 'y'));
    static_assert(swap(make_stack('x', 'y')) == make_stack('y', 'x'));
  }

  TEST(CompileTimeStack, Nip)
  {
    ASSERT_EQ(nip(make_stack('x', 'y')), make_stack('x'));
    static_assert(nip(make_stack('x', 'y')) == make_stack('x'));
  }

  TEST(CompileTimeStack, Tuck)
  {
    ASSERT_EQ(tuck(make_stack('x', 'y')), make_stack('x', 'y', 'x'));
    static_assert(
      tuck(make_stack('x', 'y')) == make_stack('x', 'y', 'x'));
  }

  TEST(CompileTimeStack, Over)
  {
    ASSERT_EQ(over(make_stack('x', 'y')), make_stack('y', 'x', 'y'));
    static_assert(
      over(make_stack('x', 'y')) == make_stack('y', 'x', 'y'));
  }

  TEST(CompileTimeStack, Rot)
  {
    ASSERT_EQ(
      rot(make_stack('x', 'y', 'z')), make_stack('z', 'x', 'y'));
    static_assert(
      rot(make_stack('x', 'y', 'z')) == make_stack('z', 'x', 'y'));
  }

} // end of namespace ListProcessing::Testing
