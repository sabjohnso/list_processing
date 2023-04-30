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
    EXPECT_TRUE((is_same_v<decltype(xs), Nothing>));
  }

  TEST(cons, Nothing)
  {
    auto xs = cons(1, nothing);
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
  }

  TEST(list, OneValue)
  {
    auto xs = list(1);
    std::cout << xs << std::endl;
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
    EXPECT_EQ(car(xs), 1);
  }

  TEST(list, TwoValues)
  {
    auto xs = list(1, 2);
    EXPECT_TRUE((is_same_v<decltype(xs), Construct<int>>));
    EXPECT_EQ(car(xs), 1);
    EXPECT_TRUE(
      (is_same_v<decltype(cdr(xs)), typename Construct<int>::datum_type>));
    // EXPECT_TRUE(ispair(cdr(xs)));
    // EXPECT_EQ(car(cdr(xs)), 2);
  }

} // namespace ListProcessing::Dynamic::Testing
