//
// NOTE: At the time of writing, the test in this file are test
// of implementation details, because the ShortList class template.
// is not viewed as user-facing. They are being retained because the
// current view that regarding whether the ShortList class template
// should become user-facing is not firm.
//
// Therefore, if maintianing the tests in this file becomes costly,
// they may be safely discarded.

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic/ShortList.hpp>

using ListProcessing::Dynamic::Details::index_type;
using ListProcessing::Dynamic::Details::size_type;

using ListProcessing::Dynamic::Details::buildShortList;
using ListProcessing::Dynamic::Details::short_list;
using ListProcessing::Dynamic::Details::ShortList;

namespace ListProcessing::Testing
{

  TEST(ShortList, InitialValue)
  {
    ASSERT_EQ(head(ShortList<int, 32>(1)), 1);
  }

  TEST(ShortList, InitialLength)
  {
    ASSERT_EQ(length(ShortList<int, 32>(1)), 1);
  }

  TEST(ShortList, ConsLength2)
  {
    ASSERT_EQ(length(cons(1, ShortList<int, 32>(2))), 2);
  }

  TEST(ShortList, ConsLength3)
  {
    ASSERT_EQ(length(cons(1, cons(2, ShortList<int, 32>(1)))), 3);
  }

  TEST(ShortList, Head1Of3)
  {
    ASSERT_EQ(head(cons(1, cons(2, ShortList<int, 32>(3)))), 1);
  }

  TEST(ShortList, Head2Of3)
  {
    ASSERT_EQ(head(tail(cons(1, cons(2, ShortList<int, 32>(3))))), 2);
  }

  TEST(ShortList, Head3Of3)
  {
    ASSERT_EQ(head(tail(tail(cons(1, cons(2, ShortList<int, 32>(3)))))), 3);
  }

  TEST(ShortList, ReverseList1)
  {
    ASSERT_EQ(length(reverse(ShortList<int, 32>(1))), 1);
  }

  // implementation details
  TEST(ShortList, ReverseList1IsReversed)
  {
    ASSERT_TRUE(isReversed(reverse(ShortList<int, 32>(1))));
  }

  TEST(ShortList, HeadReverseList1)
  {
    ASSERT_EQ(head(reverse(ShortList<int, 32>(1))), 1);
  }

  TEST(ShortList, ReverseList2)
  {
    ASSERT_EQ(length(reverse(cons(1, ShortList<int, 32>(2)))), 2);
  }

  // implementation details
  TEST(ShortList, ReverseList2IsReversed)
  {
    ASSERT_TRUE(isReversed(reverse(cons(1, ShortList<int, 32>(2)))));
  }

  TEST(ShortList, HeadReverseList2)
  {
    ASSERT_EQ(head(reverse(cons(1, ShortList<int, 32>(2)))), 2);
  }

  TEST(ShortList, ReverseList3)
  {
    ASSERT_EQ(length(reverse(cons(1, cons(2, ShortList<int, 32>(2))))), 3);
  }

  // implementation details
  TEST(ShortList, ReverseList3IsReversed)
  {
    ASSERT_TRUE(isReversed(reverse(cons(1, cons(2, ShortList<int, 32>(2))))));
  }

  TEST(ShortList, ReversedHead1Of3)
  {
    ASSERT_EQ(head(reverse(cons(1, cons(2, ShortList<int, 32>(3))))), 3);
  }

  TEST(ShortList, LengthTail1Reverse3)
  {
    ASSERT_EQ(length(tail(reverse(cons(1, cons(2, ShortList<int, 32>(3)))))), 2);
  }

  TEST(ShortList, LengthTail2Reverse3)
  {
    ASSERT_EQ(length(tail(tail(reverse(cons(1, cons(2, ShortList<int, 32>(3))))))), 1);
  }

  TEST(ShortList, HeadTail1Reverse3)
  {
    ASSERT_EQ(head(tail(reverse(cons(1, cons(2, ShortList<int, 32>(3)))))), 2);
  }

  TEST(ShortList, HeadTail2Reverse3)
  {
    ASSERT_EQ(head(tail(tail(reverse(cons(1, cons(2, ShortList<int, 32>(3))))))), 1);
  }

  TEST(ShortList, Access)
  {
    ASSERT_EQ(length(short_list<int, 32>(1, 2, 3, 4)), 4);
    ASSERT_EQ(head(short_list<int, 32>(1, 2, 3, 4)), 1);
    ASSERT_EQ(head(tail(short_list<int, 32>(1, 2, 3, 4))), 2);
    ASSERT_EQ(head(tail(tail(short_list<int, 32>(1, 2, 3, 4)))), 3);
    ASSERT_EQ(head(tail(tail(tail(short_list<int, 32>(1, 2, 3, 4))))), 4);

    ASSERT_EQ(listRef(short_list<int, 32>(1, 2, 3, 4), 0), 1);
    ASSERT_EQ(listRef(short_list<int, 32>(1, 2, 3, 4), 1), 2);
    ASSERT_EQ(listRef(short_list<int, 32>(1, 2, 3, 4), 2), 3);
    ASSERT_EQ(listRef(short_list<int, 32>(1, 2, 3, 4), 3), 4);

    ASSERT_EQ((short_list<int, 32>(1, 2, 3, 4)), (short_list<int, 32>(1, 2, 3, 4)));
    ASSERT_NE((short_list<int, 32>(1, 2, 3, 4)), (short_list<int, 32>(1, 2, 3)));
    ASSERT_NE((short_list<int, 32>(1, 2, 3, 4)), (short_list<int, 32>(1, 2, 3, 5)));

    ASSERT_EQ(drop(short_list<int, 32>(1, 2, 3, 4), 0), (short_list<int, 32>(1, 2, 3, 4)));
    ASSERT_EQ(drop(short_list<int, 32>(1, 2, 3, 4), 1), (short_list<int, 32>(2, 3, 4)));
    ASSERT_EQ(drop(short_list<int, 32>(1, 2, 3, 4), 2), (short_list<int, 32>(3, 4)));
    ASSERT_EQ(drop(short_list<int, 32>(1, 2, 3, 4), 3), (short_list<int, 32>(4)));

    ASSERT_EQ(take(short_list<int, 32>(1, 2, 3, 4), 4), (short_list<int, 32>(1, 2, 3, 4)));
    ASSERT_EQ(take(short_list<int, 32>(1, 2, 3, 4), 3), (short_list<int, 32>(1, 2, 3)));
    ASSERT_EQ(take(short_list<int, 32>(1, 2, 3, 4), 2), (short_list<int, 32>(1, 2)));
    ASSERT_EQ(take(short_list<int, 32>(1, 2, 3, 4), 1), (short_list<int, 32>(1)));
  }

  TEST(ShortList, ReverseAccess)
  {
    ASSERT_EQ(length(short_list<int, 32>(1, 2, 3, 4)), 4);
    ASSERT_EQ(head(reverse(short_list<int, 32>(1, 2, 3, 4))), 4);
    ASSERT_EQ(head(tail(reverse(short_list<int, 32>(1, 2, 3, 4)))), 3);
    ASSERT_EQ(head(tail(tail(reverse(short_list<int, 32>(1, 2, 3, 4))))), 2);
    ASSERT_EQ(head(tail(tail(tail(reverse(short_list<int, 32>(1, 2, 3, 4)))))), 1);

    ASSERT_EQ(listRef(reverse(short_list<int, 32>(1, 2, 3, 4)), 0), 4);
    ASSERT_EQ(listRef(reverse(short_list<int, 32>(1, 2, 3, 4)), 1), 3);
    ASSERT_EQ(listRef(reverse(short_list<int, 32>(1, 2, 3, 4)), 2), 2);
    ASSERT_EQ(listRef(reverse(short_list<int, 32>(1, 2, 3, 4)), 3), 1);
  }

  TEST(ShortList, Build)
  {
    constexpr size_type n = 10;
    auto xs = buildShortList<int, 32>([](auto i) { return i; }, n);

    ASSERT_EQ(length(xs), n);
    for (index_type i = 0; i < n; ++i) {
      ASSERT_EQ(listRef(xs, i), i);
    }
  }

  TEST(ShortList, FMap)
  {
    constexpr size_type n = 17;
    constexpr size_type nm1 = n - 1;
    constexpr auto a = 0.0;
    constexpr auto b = 1.0;

    ASSERT_EQ(
      fMap(
        [=, spacing = (b - a) / nm1](auto i) { return a + i * spacing; },
        buildShortList<index_type, 32>([](auto i) { return i; }, 10)),
      (short_list<double, 32>(0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625)));
  }

} // end of namespace ListProcessing::Testing
