//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... ListProcessing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_queue;
using ListProcessing::CompileTime::makeQueue;
using ListProcessing::CompileTime::pipe;

namespace ListProcessing::Testing
{
  TEST(CompileTimeQueue, EmptyQueueIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_queue));
  }

  TEST(CompileTimeQueue, PushNotEmpty)
  {
    ASSERT_FALSE(isEmpty(push(empty_queue, 'a')));
  }

  TEST(CompileTimeQueue, FrontPushIsValue)
  {
    ASSERT_EQ(front(push(empty_queue, 'a')), 'a');
  }

  TEST(CompileTimeQueue, PushPopIsEmpty)
  {
    ASSERT_TRUE(isEmpty(pop(push(empty_queue, 'a'))));
  }

  TEST(CompileTimeQueue, Order)
  {
    constexpr auto xs = makeQueue('a', 'b', 'c');
    ASSERT_EQ(front(xs), 'a');
    ASSERT_EQ(front(pop(xs)), 'b');
    ASSERT_EQ(front(pop(pop(xs))), 'c');
    ASSERT_TRUE(isEmpty(pop(pop(pop(xs)))));
    ASSERT_TRUE(isEmpty(pop(pop(pop(pop(xs))))));
  }

} // end of namespace ListProcessing::Testing
