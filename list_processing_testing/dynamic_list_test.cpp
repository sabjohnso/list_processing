//
// ... Standard header files
//
#include <functional>
#include <string>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... External header files
//
#include <function_utility/function_utility.hpp>

//
// ... List Processing header files
//
#include <list_processing/dynamic_list.hpp>

using namespace std::literals::string_literals;
using std::function;
using std::plus;

using FunctionUtility::curry;

using ListProcessing::Dynamic::buildList;
using ListProcessing::Dynamic::list;
using ListProcessing::Dynamic::ListType;
using ListProcessing::Dynamic::nil;
using ListProcessing::Dynamic::Nil;
using ListProcessing::Dynamic::size_type;
using ListProcessing::Dynamic::Details::List;

namespace ListProcessing::Testing {
  namespace // anonymous
  {
    template<typename T>
    std::ostream&
    operator<<(std::ostream& os, ListType<T> xs) {
      os << "(";
      if (hasData(xs)) {
        os << head(xs);
        doList(tail(xs), [&](auto x) { os << " " << x; });
      }
      os << ")";
      return os;
    }

  } // namespace

  TEST(DynamicList, EqualityNilNil) { ASSERT_TRUE(nil<int> == nil<int>); }

  TEST(DynamicList, InequalityNilNil) { ASSERT_FALSE(nil<int> != nil<int>); }

  TEST(DynamicList, EqualityNilX) { ASSERT_FALSE(nil<int> == list(1)); }

  TEST(DynamicList, InequalityNilX) { ASSERT_TRUE(nil<int> != list(1)); }

  TEST(DynamicList, EqualityXX) { ASSERT_TRUE(list(1) == list(1)); }

  TEST(DynamicList, InequalityXX) { ASSERT_FALSE(list(1) != list(1)); }

  TEST(DynamicList, EqualityXY) { ASSERT_FALSE(list(1) == list(2)); }

  TEST(DynamicList, InequalityXY) { ASSERT_TRUE(list(1) != list(2)); }

  TEST(DynamicList, NilIsNull) { ASSERT_TRUE(isNull(nil<int>)); }

  TEST(DynamicList, LengthNilIs0) { ASSERT_EQ(length(nil<int>), 0); }

  TEST(DynamicList, NotNilHasData) { ASSERT_FALSE(hasData(nil<int>)); }

  TEST(DynamicList, Cons) { ASSERT_TRUE(hasData(cons(1, nil<int>))); }

  TEST(DynamicList, ConsLength) { ASSERT_EQ(length(cons(1, nil<int>)), 1); }

  TEST(DynamicList, ListLenght1) { ASSERT_EQ(length(list(1)), 1); }

  TEST(DynamicList, ListLength2) { ASSERT_EQ(length(list(1, 2)), 2); }

  TEST(DynamicList, ListLength3) { ASSERT_EQ(length(list(1, 2, 3)), 3); }

  TEST(DynamicList, Head1) {
    auto xs = list(1);
    ASSERT_EQ(head(xs), 1);
  }

  TEST(DynamicList, Head1Temporary) { ASSERT_EQ(head(list(1)), 1); }

  TEST(DynamicList, Rappend) {
    ASSERT_EQ(rappend(list(2, 1), list(3, 4)), list(1, 2, 3, 4));
  }

  TEST(DynamicList, Reverse) {
    ASSERT_EQ(reverse(list(1, 2, 3)), list(3, 2, 1));
  }

  TEST(DynamicList, Append) {
    ASSERT_EQ(append(list(1, 2), list(3, 4)), list(1, 2, 3, 4));
  }

  TEST(DynamicList, Take0Of0) { ASSERT_EQ(take(nil<int>, 0), nil<int>); }

  TEST(DynamicList, Take1Of0) { ASSERT_EQ(take(nil<int>, 1), nil<int>); }

  TEST(DynamicList, Take0Of1) { ASSERT_EQ(take(list(1), 0), nil<int>); }

  TEST(DynamicList, Take1Of1) { ASSERT_EQ(take(list(1), 1), list(1)); }

  TEST(DynamicList, Take2Of1) { ASSERT_EQ(take(list(1), 1), list(1)); }

  TEST(DynamicList, Take0of2) { ASSERT_EQ(take(list(1, 2), 0), nil<int>); }

  TEST(DynamicList, Take1of2) { ASSERT_EQ(take(list(1, 2), 1), list(1)); }

  TEST(DynamicList, Take2of2) { ASSERT_EQ(take(list(1, 2), 2), list(1, 2)); }

  TEST(DynamicList, Take3of2) { ASSERT_EQ(take(list(1, 2), 3), list(1, 2)); }

  TEST(DynamicList, Drop0Of0) { ASSERT_EQ(drop(nil<int>, 0), nil<int>); }

  TEST(DynamicList, Drop1Of0) { ASSERT_EQ(drop(nil<int>, 1), nil<int>); }

  TEST(DynamicList, Drop0Of1) { ASSERT_EQ(drop(list(1), 0), list(1)); }

  TEST(DynamicList, Drop1Of1) { ASSERT_EQ(drop(list(1), 1), nil<int>); }

  TEST(DynamicList, Drop2Of1) { ASSERT_EQ(drop(list(1), 2), nil<int>); }

  TEST(DynamicList, Drop0Of2) { ASSERT_EQ(drop(list(1, 2), 0), list(1, 2)); }

  TEST(DynamicList, Drop1Of2) { ASSERT_EQ(drop(list(1, 2), 1), list(2)); }

  TEST(DynamicList, Drop2Of2) { ASSERT_EQ(drop(list(1, 2), 2), nil<int>); }

  TEST(DynamicList, Drop3Of2) { ASSERT_EQ(drop(list(1, 2), 3), nil<int>); }

  TEST(DynamicList, FoldL) {
    auto xs = foldL([](auto x, auto y) { return x + y; }, 0, list(1, 2, 3));
    ASSERT_EQ(xs, 6);
  }

  TEST(DynamicList, FoldR) {
    auto xs = foldR([](auto x, auto y) { return y - x; }, list(1, 2, 3), 6);
    ASSERT_EQ(xs, 0);
  }

  TEST(DynamicList, FMapIntToDouble) {
    auto xs = map([](auto x) { return double(x); }, list(1, 2, 3));
    ASSERT_EQ(xs, list(1.0, 2.0, 3.0));
  }

  TEST(DynamicList, FMapIntToString) {
    auto xs = map([](auto x) { return std::to_string(x); }, list(1, 2, 3));
    ASSERT_EQ(xs, list("1"s, "2"s, "3"s));
  }

  TEST(DynamicList, FoldString) {
    auto xs = foldL(
      [](auto x, auto y) { return x + y; },
      ""s,
      map([](auto x) { return std::to_string(x); }, list(1, 2, 3)));
    ASSERT_EQ(xs, "123"s);
  }

  TEST(DynamicList, AMapDoubles) {
    auto xs = aMap(
      list(
        function<double(double)>([](auto x) { return x + x; }),
        function<double(double)>([](auto x) { return x * x; })),
      list(1.0, 2.0, 3.0));
    ASSERT_EQ(xs, list(2.0, 4.0, 6.0, 1.0, 4.0, 9.0));
  }

  TEST(DynamicList, AMapPlusInt) {
    EXPECT_EQ(
      aMap(map(curry<2>(plus{}), list(1, 2)), list(3, 4)), list(4, 5, 5, 6));
  }

  TEST(DynamicList, AMapStrings) {
    using function_type = function<std::string(std::string)>;
    auto xs             = aMap(
      list(
        function_type([](auto x) { return x + x; }),
        function_type([](auto x) { return "-"s + x; })),
      list("a"s, "b"s, "c"s));
    ASSERT_EQ(xs, list("aa"s, "bb"s, "cc"s, "-a"s, "-b"s, "-c"s));
  }

  TEST(DynamicList, AMapBinary) {
    using function_type         = function<function<double(double)>(double)>;
    constexpr auto curryDouble2 = [](auto f) {
      return function_type([=](double x) {
        return function<double(double)>([=](double y) { return f(x, y); });
      });
    };

    ASSERT_EQ(
      aMap(
        list(curryDouble2(std::plus{}), curryDouble2(std::multiplies{})),
        list(1.0, 2.0),
        list(3.0, 4.0)),
      list(4.0, 5.0, 5.0, 6.0, 3.0, 4.0, 6.0, 8.0));
  }

  TEST(DynamicListChunked, NilIsNull) {
    ASSERT_TRUE(isNull(List<int, 32>::nil));
  }

  TEST(DynamicListChunked, ConsIsNotNull) {
    ASSERT_FALSE(isNull(cons(1, List<int, 32>::nil)));
  }

  TEST(DynamicListChunked, ListLenght0) { ASSERT_EQ(length(nil<char>), 0); }

  TEST(DynamicListChunked, ListLenght1) { ASSERT_EQ(length(list('a')), 1); }

  TEST(DynamicListChunked, ListLength2) {
    ASSERT_EQ(length(list('a', 'b')), 2);
  }

  TEST(DynamicListChunked, ListLenght3) {
    ASSERT_EQ(length(list('a', 'b', 'c')), 3);
  }

  TEST(DynamicListChunked, Head1) { ASSERT_EQ(head(list('a', 'b', 'c')), 'a'); }

  TEST(DynamicListChunked, Head2) {
    ASSERT_EQ(head(tail(list('a', 'b', 'c'))), 'b');
  }

  TEST(DynamicListChunked, Head3) {
    ASSERT_EQ(head(tail(tail(list('a', 'b', 'c')))), 'c');
  }

  TEST(DynamicListChunked, BuildList) {
    constexpr size_type n  = 129;
    auto                xs = buildList([](auto i) { return i; }, n);
    ASSERT_EQ(length(xs), n);
    for (size_type i = 0; i < n; ++i) {
      ASSERT_EQ(listRef(xs, i), i);
    }
  }

  TEST(DynamicListChunked, BuildBigList) {
    constexpr size_type n  = 100'000;
    auto                xs = buildList([](auto i) { return i; }, n);
    EXPECT_EQ(length(xs), n);
    doList(xs, [i = size_type(0)](auto x) mutable { ASSERT_EQ(x, i++); });
  }

  TEST(DynamicListChunked, ReverseBigList) {
    constexpr size_type n   = 100'000;
    constexpr size_type nm1 = n - 1;
    auto                xs  = reverse(buildList([](auto i) { return i; }, n));
    EXPECT_EQ(length(xs), n);
    doList(xs, [i = size_type(0)](auto x) mutable { ASSERT_EQ(x, nm1 - i++); });
  }

  TEST(DynamicListChunked, MapBigList) {
    constexpr size_type n = 100'000;
    auto                xs =
      map([](auto x) { return x * x; }, buildList([](auto i) { return i; }, n));
    EXPECT_EQ(length(xs), n);
  }

  TEST(DynamicList, GenericNil) { ASSERT_EQ(cons(1, Nil{}), list(1)); }
} // end of namespace ListProcessing::Testing
