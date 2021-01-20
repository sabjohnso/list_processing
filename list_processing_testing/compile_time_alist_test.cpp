//
// ... Testing header files
//
#include <gtest/gtest.h>
#include <list_processing_testing/static_checks.hpp>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>
#include <ctstring/ctstring.hpp>

//
// ... AList header files
//
#include <list_processing/compile_time_alist.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::CompileTime::empty_alist;
using ListProcessing::CompileTime::hasKeyByType;
using TypeUtility::type;


#define KEY(str) CTString::hoist([]{ return ::CTString::static_string(str); })

namespace ListProcessing::Testing
{

  TEST(CompileTimeAList, EmptyDoesNotHaveData){
    STATIC_EXPECT_FALSE(hasData(empty_alist));
  }

  TEST(CompileTimeAList, FObjEmptyDoesNotHaveData){
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_FALSE(hasData(empty_alist));
  }

  TEST(AList, EmptyIsEmpty){
    STATIC_EXPECT_TRUE(isEmpty(empty_alist));
  }

  TEST(AList, FObjEmptyIsEmpty){
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_TRUE(isEmpty(empty_alist));
  }

  TEST(AList, SetHasData){
    STATIC_EXPECT_TRUE(hasData(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetHasData){
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_TRUE(hasData(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, SetIsNotEmpty){
    STATIC_EXPECT_FALSE(isEmpty(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetIsNotEmpty){
    using namespace ::ListProcessing::Operators;
    STATIC_EXPECT_FALSE(isEmpty(set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, SetHasKey){
    EXPECT_TRUE(hasKey(KEY("x"), set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetHasKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(empty_alist,
                     set(KEY("x"), 3),
                     hasKey(KEY("x"))));
  }

  TEST(AList, SetDoesNotHaveKeyNotSet){
    EXPECT_FALSE(hasKey(KEY("y"), set(KEY("x"), 3, empty_alist)));
  }

  TEST(AList, FObjSetDoesNotHaveKeyNotSet){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist,
                      set(KEY("x"), 3),
                      hasKey(KEY("y"))));
  }

  TEST(AList, UnsetRemovesKey){
    EXPECT_FALSE(hasKey(KEY("x"), unset(KEY("x"), set(KEY("x"), 3, empty_alist))));
  }

  TEST(AList, FObjUnsetRemovesKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist,
                      set(KEY("x"), 3),
                      unset(KEY("x")),
                      hasKey(KEY("x"))));
  }

  TEST(AList, UnsetOnlyRemovesFirstOccurance){
    EXPECT_TRUE(hasKey(KEY("x"), unset(KEY("x"), set(KEY("x"), 4, set(KEY("x"), 3, empty_alist)))));
  }

  TEST(AList, FObjUnsetOnlyRemovesFirstOccurance){
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(empty_alist,
                     set(KEY("x"), 3),
                     set(KEY("x"), 4),
                     unset(KEY("x")),
                     hasKey(KEY("x"))));
  }

  TEST(AList, RemoveRemovesAllOccurances){
    EXPECT_FALSE(hasKey(KEY("x"), remove(KEY("x"), set(KEY("x"), 4, set(KEY("x"), 3, empty_alist)))));
  }

  TEST(AList, FObjRemoveRemovesAllOccurances){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist,
                      set(KEY("x"), 3),
                      set(KEY("x"), 4),
                      remove(KEY("x")),
                      hasKey(KEY("x"))));
  }


  TEST(AList, ForceGetReturnsValueByKey){
    EXPECT_EQ(
      empty_alist
      .set(KEY("x"), 3)
      .forceGet(KEY("x"), 0),
      3);
  }

  TEST(AList, FObjForceGetReturnsValueByKey){
    using namespace  ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist,
           set(KEY("x"), 3),
           forceGet(KEY("x"), 0)),
      3);
  }

  TEST(AList, ForceGetReturnsAlternateForMissingKey){
    EXPECT_EQ(forceGet(KEY("y"), 0, set(KEY("x"), 3, empty_alist)),
              0);
  }

  TEST(AList, FObjForceGetReturnsAlternateForMissingKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist,
           set(KEY("x"), 3),
           forceGet(KEY("y"), 0)),
      0);
  }

  TEST(AList, TryGetReturnsValueByKey){
    using ListProcessing::Operators::pipe;
    EXPECT_EQ(
      pipe(empty_alist,
           [](auto alist){ return set(KEY("x"), 3, alist); },
           [](auto alist){ return tryGet(KEY("x"), alist); }),
      3);
  }

  TEST(AList, FObjTryGetReturnsValueByKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist,
           set(KEY("x"), 3),
           tryGet(KEY("x"))),
      3);
  }

  TEST(AList, TryGetWillNotCompileForMissingKey){
    // FIXME: Find a better way to perform this check
    // Uncomment the following code to check for compilation failure

    // using ListProcessing::Operators::pipe;
    // pipe(empty_alist,
    //      [](auto alist){ return set(KEY("x"), 3, alist); },
    //      [](auto alist){ return tryGet(KEY("y"), alist); });
  }


  TEST(AList, HasKeyByTypeAffirmative){
    constexpr auto x = KEY("x");
    EXPECT_TRUE(
      (hasKeyByType<
       decltype(x),
       decltype(set(x, 3, empty_alist))>));
  }

  TEST(AList, HasKeyByTypeNegative){
    constexpr auto x = KEY("x");
    constexpr auto y = KEY("y");
    EXPECT_FALSE(
      (hasKeyByType<
       decltype(y),
       decltype(set(x, 3, empty_alist))>));
  }

} // end of namespace ListProcessing::Testing
