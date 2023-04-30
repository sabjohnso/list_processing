//
// ... Standard header files
//
#include <cstdint>
#include <utility>

//
// ... Testing header files
//
#include <gtest/gtest.h>
#include <list_processing_testing/static_checks.hpp>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>

//
// ... AList header files
//
#include <list_processing/compile_time.hpp>
#include <list_processing/compile_time_alist.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::CompileTime::alist;
using ListProcessing::CompileTime::empty_alist;
using ListProcessing::CompileTime::hasKeyByType;
using ListProcessing::CompileTime::list;
using ListProcessing::CompileTime::nothing;
using std::pair;
using TypeUtility::type;

// to satisfy gtest
namespace std {
  template<typename T, typename U>
  ostream&
  operator<<(ostream& os, pair<T, U> const& pr)
  {
    return os << "(" << pr.first << " . " << pr.second << ")";
  }
} // namespace std

namespace ListProcessing::Testing {
  template<auto N>
  struct FixedString
  {
    constexpr FixedString(const char* input)
    {
      for (std::size_t i = 0; i < N; ++i) {
        value[i] = input[i];
      }
    }

    friend std::ostream&
    operator<<(std::ostream& os, const FixedString& str)
    {
      return os << str.value;
    }

    constexpr bool
    operator==(const FixedString& other) const
    {
      return [&]<auto... Indices>(std::index_sequence<Indices...>)
      {
        return ((value[Indices] == other.value[Indices]) && ...);
      }
      (std::make_index_sequence<N>());
    }

    constexpr bool
    operator!=(const FixedString& other) const
    {
      return !(*this == other);
    }

    template<auto M>
    constexpr bool
    operator==(const FixedString<M>&) const
    {
      return false;
    }

    template<auto M>
    constexpr bool
    operator!=(const FixedString<M>&) const
    {
      return true;
    }

    char value[N];
  };

  template<auto N>
  FixedString(const char (&)[N]) -> FixedString<N>;

  template<FixedString Str>
  struct Hoisted
  {
    friend std::ostream&
    operator<<(std::ostream& os, const Hoisted&)
    {
      return os << '"' << Str << '"' << "_key";
    }

    template<FixedString Str2>
    constexpr bool
    operator==(const Hoisted<Str2>&) const
    {
      return Str == Str2;
    }

    template<FixedString Str2>
    constexpr bool
    operator!=(const Hoisted<Str2>& other) const
    {
      return !(*this == other);
    }

    template<typename T>
    constexpr bool
    operator!=(const T&) const
    {
      return true;
    }
  };

  template<FixedString Str>
  constexpr Hoisted<Str> operator""_key()
  {
    return {};
  }

#define KEY(str)                                                               \
  Hoisted<str>                                                                 \
  {                                                                            \
  }

  TEST(CompileTimeAList, EmptyDoesNotHaveData)
  {
    STATIC_EXPECT_FALSE(hasData(empty_alist));
  }

  TEST(CompileTimeAList, FObjEmptyDoesNotHaveData)
  {
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_FALSE(hasData(empty_alist));
  }

  TEST(AList, EmptyIsEmpty) { STATIC_EXPECT_TRUE(isEmpty(empty_alist)); }

  TEST(AList, FObjEmptyIsEmpty)
  {
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_TRUE(isEmpty(empty_alist));
  }

  TEST(AList, Constructor)
  {
    constexpr auto xs =
      alist(pair("x"_key, 1.0), pair(KEY("y"), 2.0), pair(KEY("z"), 3.0));

    EXPECT_TRUE(hasKey(KEY("x"), xs));
    EXPECT_EQ(tryGet(KEY("x"), xs), 1.0);

    EXPECT_TRUE(hasKey(KEY("y"), xs));
    EXPECT_EQ(tryGet(KEY("y"), xs), 2.0);

    EXPECT_TRUE(hasKey(KEY("z"), xs));
    EXPECT_EQ(tryGet(KEY("z"), xs), 3.0);
  }

  TEST(AList, SetHasData)
  {
    STATIC_EXPECT_TRUE(hasData(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetHasData)
  {
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_TRUE(hasData(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, SetIsNotEmpty)
  {
    STATIC_EXPECT_FALSE(isEmpty(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetIsNotEmpty)
  {
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_FALSE(isEmpty(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, SetHasKey)
  {
    EXPECT_TRUE(hasKey(KEY("x"), set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetHasKey)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(empty_alist, set(KEY("x"), 3), hasKey(KEY("x"))));
  }

  TEST(AList, SetDoesNotHaveKeyNotSet)
  {
    EXPECT_FALSE(hasKey(KEY("y"), set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetDoesNotHaveKeyNotSet)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist, set(KEY("x"), 3), hasKey(KEY("y"))));
  }

  TEST(AList, UnsetRemovesKey)
  {
    EXPECT_FALSE(
      hasKey(KEY("x"), unset(KEY("x"), set(KEY("x"), 3, empty_alist))));
  }

  TEST(AList, FObjUnsetRemovesKey)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(
      pipe(empty_alist, set(KEY("x"), 3), unset(KEY("x")), hasKey(KEY("x"))));
  }

  TEST(AList, UnsetOnlyRemovesFirstOccurance)
  {
    EXPECT_TRUE(hasKey(
      KEY("x"),
      unset(KEY("x"), set(KEY("x"), 4, set(KEY("x"), 3, empty_alist)))));
  }

  TEST(AList, FObjUnsetOnlyRemovesFirstOccurance)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(
      empty_alist,
      set(KEY("x"), 3),
      set(KEY("x"), 4),
      unset(KEY("x")),
      hasKey(KEY("x"))));
  }

  TEST(AList, RemoveRemovesAllOccurances)
  {
    EXPECT_FALSE(hasKey(
      KEY("x"),
      remove(KEY("x"), set(KEY("x"), 4, set(KEY("x"), 3, empty_alist)))));
  }

  TEST(AList, FObjRemoveRemovesAllOccurances)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(
      empty_alist,
      set(KEY("x"), 3),
      set(KEY("x"), 4),
      remove(KEY("x")),
      hasKey(KEY("x"))));
  }

  TEST(AList, ForceGetReturnsValueByKey)
  {
    EXPECT_EQ(empty_alist.set(KEY("x"), 3).forceGet(KEY("x"), 0), 3);
  }

  TEST(AList, FObjForceGetReturnsValueByKey)
  {
    using namespace ListProcessing::Operators;
    EXPECT_EQ(pipe(empty_alist, set(KEY("x"), 3), forceGet(KEY("x"), 0)), 3);
  }

  TEST(AList, ForceGetReturnsAlternateForMissingKey)
  {
    EXPECT_EQ(forceGet(KEY("y"), 0, set(KEY("x"), 3, empty_alist)), 0);
  }

  TEST(AList, FObjForceGetReturnsAlternateForMissingKey)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(pipe(empty_alist, set(KEY("x"), 3), forceGet(KEY("y"), 0)), 0);
  }

  TEST(AList, TryGetReturnsValueByKey)
  {
    using ListProcessing::Operators::pipe;
    EXPECT_EQ(
      pipe(
        empty_alist,
        [](auto alist) { return set(KEY("x"), 3, alist); },
        [](auto alist) { return tryGet(KEY("x"), alist); }),
      3);
  }

  TEST(AList, FObjTryGetReturnsValueByKey)
  {
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(pipe(empty_alist, set(KEY("x"), 3), tryGet(KEY("x"))), 3);
  }

  TEST(AList, TryGetWillNotCompileForMissingKey)
  {
    // FIXME: Find a better way to perform this check
    // Uncomment the following code to check for compilation failure

    // using ListProcessing::Operators::pipe;
    // pipe(empty_alist,
    //      [](auto alist){ return set(KEY("x"), 3, alist); },
    //      [](auto alist){ return tryGet(KEY("y"), alist); });
  }

  TEST(AList, HasKeyByTypeAffirmative)
  {
    constexpr auto x = KEY("x");
    EXPECT_TRUE((hasKeyByType<decltype(x), decltype(set(x, 3, empty_alist))>));
  }

  TEST(AList, HasKeyByTypeNegative)
  {
    constexpr auto x = KEY("x");
    constexpr auto y = KEY("y");
    EXPECT_FALSE((hasKeyByType<decltype(y), decltype(set(x, 3, empty_alist))>));
  }

  TEST(AList, Keys)
  {
    EXPECT_EQ(
      keys(alist(pair(KEY("x"), 1), pair(KEY("y"), 2))),
      list(KEY("x"), KEY("y")));
  }

  TEST(AList, KeysEmpty) { EXPECT_EQ(keys(empty_alist), nothing); }

  TEST(AList, Vals)
  {
    EXPECT_EQ(vals(alist(pair(KEY("x"), 1), pair(KEY("y"), 2))), list(1, 2));
  }

  TEST(AList, ValsEmpty) { EXPECT_EQ(vals(empty_alist), nothing); }

  TEST(AList, toList)
  {
    EXPECT_EQ(
      toList(alist(pair(KEY("x"), 1), pair(KEY("y"), 2))),
      list(pair(KEY("x"), 1), pair(KEY("y"), 2)));
  }

  TEST(AList, toListEmpty) { EXPECT_EQ(toList(empty_alist), nothing); }

} // end of namespace ListProcessing::Testing
