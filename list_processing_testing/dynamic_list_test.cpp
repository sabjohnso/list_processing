//
// ... Standard header files
//
#include <string>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using namespace std::literals::string_literals;

using ListProcessing::Dynamic::buildList;
using ListProcessing::Dynamic::list;
using ListProcessing::Dynamic::nil;
using ListProcessing::Dynamic::Details::List;

namespace ListProcessing::Testing
{
  TEST(DynamicList, EqualityNilNil)
  {
    ASSERT_TRUE(nil<int> == nil<int>);
  }

  TEST(DynamicList, InequalityNilNil)
  {
    ASSERT_FALSE(nil<int> != nil<int>);
  }

  TEST(DynamicList, EqualityNilX)
  {
    ASSERT_FALSE(nil<int> == list(1));
  }

  TEST(DynamicList, InequalityNilX)
  {
    ASSERT_TRUE(nil<int> != list(1));
  }

  TEST(DynamicList, EqualityXX)
  {
    ASSERT_TRUE(list(1) == list(1));
  }

  TEST(DynamicList, InequalityXX)
  {
    ASSERT_FALSE(list(1) != list(1));
  }

  TEST(DynamicList, EqualityXY)
  {
    ASSERT_FALSE(list(1) == list(2));
  }

  TEST(DynamicList, InequalityXY)
  {
    ASSERT_TRUE(list(1) != list(2));
  }

  TEST(DynamicList, NilIsNull)
  {
    ASSERT_TRUE(isNull(nil<int>));
  }

  TEST(DynamicList, LengthNilIs0)
  {
    ASSERT_EQ(length(nil<int>), 0);
  }

  TEST(DynamicList, NotNilHasData)
  {
    ASSERT_FALSE(hasData(nil<int>));
  }

  TEST(DynamicList, Cons)
  {
    ASSERT_TRUE(hasData(cons(1, nil<int>)));
  }

  TEST(DynamicList, ConsLength)
  {
    ASSERT_EQ(length(cons(1, nil<int>)), 1);
  }

  TEST(DynamicList, ListLenght1)
  {
    ASSERT_EQ(length(list(1)), 1);
  }

  TEST(DynamicList, ListLength2)
  {
    ASSERT_EQ(length(list(1, 2)), 2);
  }

  TEST(DynamicList, ListLength3)
  {
    ASSERT_EQ(length(list(1, 2, 3)), 3);
  }

  TEST(DynamicList, Head1)
  {
    auto xs = list(1);
    ASSERT_EQ(head(xs), 1);
  }

  TEST(DynamicList, Head1Temporary)
  {
    ASSERT_EQ(head(list(1)), 1);
  }

  TEST(DynamicList, Rappend)
  {
    ASSERT_EQ(rappend(list(2, 1), list(3, 4)), list(1, 2, 3, 4));
  }

  TEST(DynamicList, Reverse)
  {
    ASSERT_EQ(reverse(list(1, 2, 3)), list(3, 2, 1));
  }

  TEST(DynamicList, Append)
  {
    ASSERT_EQ(append(list(1, 2), list(3, 4)), list(1, 2, 3, 4));
  }

  TEST(DynamicList, Take0Of0)
  {
    ASSERT_EQ(take(nil<int>, 0), nil<int>);
  }

  TEST(DynamicList, Take1Of0)
  {
    ASSERT_EQ(take(nil<int>, 1), nil<int>);
  }

  TEST(DynamicList, Take0Of1)
  {
    ASSERT_EQ(take(list(1), 0), nil<int>);
  }

  TEST(DynamicList, Take1Of1)
  {
    ASSERT_EQ(take(list(1), 1), list(1));
  }

  TEST(DynamicList, Take2Of1)
  {
    ASSERT_EQ(take(list(1), 1), list(1));
  }

  TEST(DynamicList, Take0of2)
  {
    ASSERT_EQ(take(list(1, 2), 0), nil<int>);
  }

  TEST(DynamicList, Take1of2)
  {
    ASSERT_EQ(take(list(1, 2), 1), list(1));
  }

  TEST(DynamicList, Take2of2)
  {
    ASSERT_EQ(take(list(1, 2), 2), list(1, 2));
  }

  TEST(DynamicList, Take3of2)
  {
    ASSERT_EQ(take(list(1, 2), 3), list(1, 2));
  }

  TEST(DynamicList, Drop0Of0)
  {
    ASSERT_EQ(drop(nil<int>, 0), nil<int>);
  }

  TEST(DynamicList, Drop1Of0)
  {
    ASSERT_EQ(drop(nil<int>, 1), nil<int>);
  }

  TEST(DynamicList, Drop0Of1)
  {
    ASSERT_EQ(drop(list(1), 0), list(1));
  }

  TEST(DynamicList, Drop1Of1)
  {
    ASSERT_EQ(drop(list(1), 1), nil<int>);
  }

  TEST(DynamicList, Drop2Of1)
  {
    ASSERT_EQ(drop(list(1), 2), nil<int>);
  }

  TEST(DynamicList, Drop0Of2)
  {
    ASSERT_EQ(drop(list(1, 2), 0), list(1, 2));
  }

  TEST(DynamicList, Drop1Of2)
  {
    ASSERT_EQ(drop(list(1, 2), 1), list(2));
  }

  TEST(DynamicList, Drop2Of2)
  {
    ASSERT_EQ(drop(list(1, 2), 2), nil<int>);
  }

  TEST(DynamicList, Drop3Of2)
  {
    ASSERT_EQ(drop(list(1, 2), 3), nil<int>);
  }

  TEST(DynamicList, FoldL)
  {
    ASSERT_EQ(
      foldL([](auto x, auto y) { return x + y; }, 0, list(1, 2, 3)), 6);
  }

  TEST(DynamicList, FoldR)
  {
    ASSERT_EQ(
      foldR([](auto x, auto y) { return x - y; }, list(1, 2, 3), 6), 0);
  }

  TEST(DynamicList, FMapIntToDouble)
  {
    ASSERT_EQ(
      fMap([](auto x) { return double(x); }, list(1, 2, 3)),
      list(1.0, 2.0, 3.0));
  }

  TEST(DynamicList, FMapIntToString)
  {
    ASSERT_EQ(
      fMap([](auto x) { return std::to_string(x); }, list(1, 2, 3)),
      list("1"s, "2"s, "3"s));
  }

  TEST(DynamicList, FoldString)
  {
    ASSERT_EQ(
      foldL(
        [](auto x, auto y) { return x + y; },
        ""s,
        fMap([](auto x) { return std::to_string(x); }, list(1, 2, 3))),
      "123"s);
  }

  TEST(DynamicListChunked, NilIsNull)
  {
    ASSERT_TRUE(isNull(List<int, 32>::nil));
  }

  TEST(DynamicListChunked, ConsIsNotNull)
  {
    ASSERT_FALSE(isNull(cons(1, List<int, 32>::nil)));
  }

  TEST(DynamicListChunked, ListLenght0)
  {
    ASSERT_EQ(length(nil<char>), 0);
  }

  TEST(DynamicListChunked, ListLenght1)
  {
    ASSERT_EQ(length(list('a')), 1);
  }

  TEST(DynamicListChunked, ListLength2)
  {
    ASSERT_EQ(length(list('a', 'b')), 2);
  }

  TEST(DynamicListChunked, ListLenght3)
  {
    ASSERT_EQ(length(list('a', 'b', 'c')), 3);
  }

  TEST(DynamicListChunked, Head1)
  {
    ASSERT_EQ(head(list('a', 'b', 'c')), 'a');
  }

  TEST(DynamicListChunked, Head2)
  {
    ASSERT_EQ(head(tail(list('a', 'b', 'c'))), 'b');
  }

  TEST(DynamicListChunked, Head3)
  {
    ASSERT_EQ(head(tail(tail(list('a', 'b', 'c')))), 'c');
  }

  TEST(DynamicListChunked, BuildList)
  {}

} // end of namespace ListProcessing::Testing
