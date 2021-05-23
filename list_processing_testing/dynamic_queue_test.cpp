//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_queue.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_queue;
using ListProcessing::Dynamic::queue;

namespace ListProcessing::Testing {
  TEST(Queue, EmptyQueueIsEmpty) { ASSERT_TRUE(isEmpty(empty_queue<int>)); }

  TEST(Queue, FObjEmptyQueueIsEmpty) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isEmpty(empty_queue<int>));
  }

  TEST(Queue, EmptyQueueFrontThrows) {
    ASSERT_THROW(front(empty_queue<int>), std::logic_error);
  }

  TEST(Queue, FObjEmptyQueueFrontThrows) {
    using namespace ListProcessing::Operators;
    ASSERT_THROW(front(empty_queue<int>), std::logic_error);
  }

  TEST(Queue, PushNotEmpty) {
    ASSERT_FALSE(isEmpty(push(1, empty_queue<int>)));
  }

  TEST(Queue, FObjPushNotEmpty) {
    using namespace ListProcessing::Operators;
    ASSERT_FALSE(isEmpty(push(1, empty_queue<int>)));
  }

  TEST(Queue, PushPopIsEmpty) {
    ASSERT_TRUE(isEmpty(pop(push(1, empty_queue<int>))));
  }

  TEST(Queue, FObjPushPopIsEmpty) {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isEmpty(pop(push(1, empty_queue<int>))));
  }

  TEST(Queue, FontPushIsValue) {
    ASSERT_EQ(front(push('x', empty_queue<char>)), 'x');
  }

  TEST(Queue, FObjFontPushIsValue) {
    using namespace ListProcessing::Operators;
    ASSERT_EQ(front(push('x', empty_queue<char>)), 'x');
  }

  TEST(Queue, Order) {
    const auto xs = queue('a', 'b', 'c');
    ASSERT_EQ(front(xs), 'a');
    ASSERT_EQ(front(pop(xs)), 'b');
    ASSERT_EQ(front(pop(pop(xs))), 'c');
    ASSERT_TRUE(isEmpty(pop(pop(pop(xs)))));
  }

  TEST(Queue, FObjOrder) {
    using namespace ListProcessing::Operators;
    const auto xs = queue('a', 'b', 'c');
    ASSERT_EQ(front(xs), 'a');
    ASSERT_EQ(front(pop(xs)), 'b');
    ASSERT_EQ(front(pop(pop(xs))), 'c');
    ASSERT_TRUE(isEmpty(pop(pop(pop(xs)))));
  }

} // end of namespace ListProcessing::Testing
