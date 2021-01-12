//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... ListProcessing header files
//
#include <list_processing/compile_time.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::CompileTime::empty_queue;
using ListProcessing::CompileTime::makeQueue;


namespace ListProcessing::Testing
{
  namespace // anonymous
  {
    constexpr auto pipe = ListProcessing::Operators::pipe;
  } // end of namespace // anonymous

  TEST(CompileTimeQueue, EmptyQueueIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_queue));
  }

  TEST(CompileTimeQueue, PushNotEmpty)
  {
    ASSERT_FALSE(isEmpty(push('a', empty_queue)));
  }

  TEST(CompileTimeQueue, FrontPushIsValue)
  {
    ASSERT_EQ(front(push('a', empty_queue)), 'a');
  }

  TEST(CompileTimeQueue, PushPopIsEmpty)
  {
    ASSERT_TRUE(isEmpty(pop(push('a', empty_queue))));
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
