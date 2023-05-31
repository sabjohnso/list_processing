//
// ... Standard header files
//
#include <type_traits>
#include <variant>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_tlist.hpp>

namespace ListProcessing::Dynamic::Testing {

  using std::decay_t;
  using std::get;
  using std::holds_alternative;
  using std::is_same_v;

  constexpr auto list = tlist;

  TEST(tlist, Nothing)
  {
    auto xs = list();
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
  }

  TEST(cons, Nothing)
  {
    auto xs = tcons(1, Construct<int>::nil);
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
  }

  TEST(list, OneValue)
  {
    auto xs = list(1);
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
    EXPECT_EQ(car(xs), 1);
  }

  TEST(list, TwoValues)
  {
    auto xs = list(1, 2);
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
    EXPECT_EQ(car(xs), 1);
    EXPECT_TRUE((is_same_v<decltype(cdr(xs)), typename Construct<int>::Slot>));
    EXPECT_TRUE(ispair(cdr(xs)));
    EXPECT_EQ(car(cdr(xs)), 2);
  }

  TEST(list, nested_list)
  {
    auto xs = list(list(1, 2), list(3, 4));
    EXPECT_EQ(car(xs), list(1, 2));
    EXPECT_EQ(cadr(xs), list(3, 4));
  }

} // namespace ListProcessing::Dynamic::Testing
