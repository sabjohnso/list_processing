//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_stack;
using ListProcessing::Dynamic::pipe;
using ListProcessing::Dynamic::Stack;

namespace ListProcessing::Testing {

  TEST(Stack, Empty) { ASSERT_TRUE(isEmpty(Stack<int>())); }

  TEST(Stack, MemEmpty){ ASSERT_TRUE(Stack<int>().isEmpty()); }

  TEST(Stack, FObjEmpty){

    ASSERT_TRUE(ListProcessing::Operators::isEmpty(Stack<int>()));
  }


  TEST(Stack, NotEmpty) { ASSERT_FALSE(isEmpty(push(0, Stack<int>()))); }

  TEST(Stack, FObjNotEmpty){
    using namespace ListProcessing::Operators;
    ASSERT_FALSE(pipe(Stack<int>(),
                      push(0),
                      isEmpty));
  }
  TEST(Stack, Drop)
  {
    auto xs = pipe(
      Stack<int>{},
      [](auto xs) { return push(0, xs); },
      [](auto xs) { return drop(xs); });
    ASSERT_EQ(xs, Stack<int>{});
  }

  TEST(Stack, Drop2)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return drop2(xs); });
    ASSERT_EQ(xs,empty_stack<int>);
  }

  TEST(Stack, Drop3)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return drop3(xs); });
    ASSERT_EQ(xs, empty_stack<int>);
  }

  TEST(Stack, Swap)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return swap(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(0, xs); });
    ASSERT_EQ( xs, ys);
  }

  TEST(Stack, Dup)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return dup(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(0, xs); });
  ASSERT_EQ(xs, ys);

  }

  TEST(Stack, Nip)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return nip(xs); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(1, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, Tuck)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return tuck(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); });
  ASSERT_EQ(xs, ys);
  }

  TEST(Stack, Over)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return over(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(0, xs); },
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(0, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App1)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return app1(xs, [](auto x) { return x * x; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(4, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App2)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x + y; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(3, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App2Subtract)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x - y; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(1, xs); });
    ASSERT_EQ(xs, ys);
  }

} // end of namespace ListProcessing::Testing
