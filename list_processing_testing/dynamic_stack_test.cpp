//
// ... Standard header files
//
#include <functional>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_stack.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_stack;
using ListProcessing::Dynamic::Stack;

namespace ListProcessing::Testing {
  using ListProcessing::Operators::pipe;

  TEST(Stack, Empty) { ASSERT_TRUE(isEmpty(Stack<int>())); }

  TEST(Stack, MemEmpty){ ASSERT_TRUE(Stack<int>().isEmpty()); }

  TEST(Stack, FObjEmpty)
  {
    using namespace ListProcessing::Operators;
    ASSERT_TRUE(isEmpty(Stack<int>()));
  }


  TEST(Stack, NotEmpty) { ASSERT_FALSE(isEmpty(push(0, Stack<int>()))); }

  TEST(Stack, FObjNotEmpty)
  {
    using namespace ListProcessing::Operators;
    ASSERT_FALSE(
      pipe(Stack<int>(), push(0), isEmpty));
  }

  TEST(Stack, Drop)
  {
    auto xs = pipe(
      Stack<int>{},
      [](auto xs) { return push(0, xs); },
      [](auto xs) { return drop(xs); });
    ASSERT_EQ(xs, Stack<int>{});
  }

  TEST(Stack, FObjDrop)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(
      Stack<int>{},
      push(0),
      drop);
    ASSERT_EQ(xs, Stack<int>{});
  }


  TEST(Stack, Drop2)
  {
    auto xs = pipe(
      empty_stack<int>,
      [](auto xs){ return push(0, xs); },
      [](auto xs){ return push(1, xs); },
      [](auto xs){ return drop2(xs); });
    ASSERT_EQ(xs,empty_stack<int>);
  }

  TEST(Stack, FObjDrop2)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(
      empty_stack<int>,
      push(0),
      push(1),
      drop2);
    ASSERT_EQ(xs, empty_stack<int>);
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


  TEST(Stack, FObjDrop3)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(
        empty_stack<int>,
        push(0),
        push(1),
        push(2),
        drop3);
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

  TEST(Stack, FObjSwap)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(0), push(1), swap);
    auto ys = pipe(empty_stack<int>, push(1), push(0));
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

  TEST(Stack, FObjDup)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(0), dup);
    auto ys = pipe(empty_stack<int>, push(0), push(0));
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

  TEST(Stack, FObjNip)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(0), push(1), nip);
    auto ys = pipe(empty_stack<int>, push(1));
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

  TEST(Stack, FObjTuck)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(0), push(1), tuck);
    auto ys = pipe(empty_stack<int>, push(1), push(0), push(1));
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

  TEST(Stack, FObjOver)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(0), push(1), over);
    auto ys = pipe(empty_stack<int>, push(0), push(1), push(0));
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App1)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return app1([](auto x) { return x * x; }, xs); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(4, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, FObjApp1)
  {
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(2), app1([](auto x){ return x*x; }));
    auto ys = pipe(empty_stack<int>, push(4));
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, App2)
  {
    auto xs = pipe(
        empty_stack<int>,
        [](auto xs) { return push(1, xs); },
        [](auto xs) { return push(2, xs); },
        [](auto xs) { return app2( [](auto x, auto y) { return x + y; }, xs); });
    auto ys = pipe(empty_stack<int>, [](auto xs) { return push(3, xs); });
    ASSERT_EQ(xs, ys);
  }

  TEST(Stack, FObjApp2)
  {
    using std::plus;
    using namespace ListProcessing::Operators;
    auto xs = pipe(empty_stack<int>, push(1), push(2), app2(plus{}));
    auto ys = pipe(empty_stack<int>, push(3));
    ASSERT_EQ(xs, ys);
  }

} // end of namespace ListProcessing::Testing
