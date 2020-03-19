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
    ASSERT_EQ(
      pipe(
        Stack<int>{},
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return drop(xs); }),
      Stack<int>{});
  }

  TEST(Stack, Drop2)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return drop2(xs); }),
      empty_stack<int>);
  }

  TEST(Stack, Drop3)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return drop3(xs); }),
      empty_stack<int>);
  }

  TEST(Stack, Swap)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return swap(xs); }),
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); }));
  }

  TEST(Stack, Dup)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return dup(xs); }),
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 0); }));
  }

  TEST(Stack, Nip)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return nip(xs); }),
      pipe(empty_stack<int>, [](auto xs) { return push(xs, 1); }));
  }

  TEST(Stack, Tuck)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return tuck(xs); }),
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); }));
  }

  TEST(Stack, Over)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return over(xs); }),
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 0); },
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 0); }));
  }

  TEST(Stack, App1)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app1(xs, [](auto x) { return x * x; }); }),
      pipe(empty_stack<int>, [](auto xs) { return push(xs, 4); }));
  }

  TEST(Stack, App2)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x + y; }); }),
      pipe(empty_stack<int>, [](auto xs) { return push(xs, 3); }));
  }

  TEST(Stack, App2Subtract)
  {
    ASSERT_EQ(
      pipe(
        empty_stack<int>,
        [](auto xs) { return push(xs, 1); },
        [](auto xs) { return push(xs, 2); },
        [](auto xs) { return app2(xs, [](auto x, auto y) { return x - y; }); }),
      pipe(empty_stack<int>, [](auto xs) { return push(xs, 1); }));
  }

} // end of namespace ListProcessing::Testing
