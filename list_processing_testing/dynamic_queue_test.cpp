//
// ... Testing header files
//
#include <gtest/gtest.h>


//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_queue;
using ListProcessing::Dynamic::queue;

namespace ListProcessing::Testing
{
  TEST(Queue, EmptyQueueIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_queue<int>));
  }
  TEST(Queue, EmptyQueueFrontThrows)
  {
    ASSERT_THROW(front(empty_queue<int>), std::logic_error);
  }
  TEST(Queue, PushNotEmpty)
  {
    ASSERT_FALSE(isEmpty(push(empty_queue<int>, 1)));
  }
  TEST(Queue, PushPopIsEmpty)
  {
    ASSERT_TRUE(isEmpty(pop(push(empty_queue<int>, 1))));
  }
  TEST(Queue, FontPushIsValue)
  {
    ASSERT_EQ(front(push(empty_queue<char>, 'x')), 'x');
  }
  TEST(Queue, Order)
  {
    const auto xs = queue('a', 'b', 'c');
    ASSERT_EQ(front(xs), 'a');
    ASSERT_EQ(front(pop(xs)), 'b');
    ASSERT_EQ(front(pop(pop(xs))), 'c');
    ASSERT_TRUE(isEmpty(pop(pop(pop( xs )))));
  }


} // end of namespace ListProcessing::Testing
