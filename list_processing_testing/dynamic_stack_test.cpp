//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_stack;
using ListProcessing::Dynamic::pipe;
using ListProcessing::Dynamic::Stack;

namespace ListProcessing::Testing {

  TEST(Stack, Empty) { ASSERT_TRUE(isempty(Stack<int>())); }
  TEST(Stack, NotEmpty) { ASSERT_FALSE(isempty(push(Stack<int>(), 0))); }
  TEST(Stack, Drop)
  {
    auto xs = pipe(
      Stack<int>{},
      [](auto xs) { return push(xs, 0); },
      [](auto xs) { return drop(xs); });
    ASSERT_EQ(xs, Stack<int>{});
  }

  TEST(Stack, Drop2)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return drop2(xs); });
    ASSERT_EQ(xs,empty_stack<int>);
  }

  TEST(Stack, Drop3)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return drop3(xs); });
    ASSERT_EQ(xs, empty_stack<int>);
  }

  TEST(Stack, Swap)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return swap(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); });
    ASSERT_EQ( xs, ys);
  }

  TEST(Stack, Dup)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return dup(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 0); });
  ASSERT_EQ(xs, ys);

  }

  TEST(Stack, Nip)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return nip(xs); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(xs, 1); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, Tuck)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return tuck(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); });
  ASSERT_EQ(xs, ys);
  }

  TEST(Stack, Over)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return over(xs); });
    auto ys = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App1)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app1(xs, [](auto x) { return x * x; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(xs, 4); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App2)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x + y; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(xs, 3); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App2Subtract)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x - y; }); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(xs, 1); });
    ASSERT_EQ(xs, ys);
  }

} // end of namespace ListProcessing::Testing
