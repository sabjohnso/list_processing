//
// ... Standard header files
//
#include <optional>
#include <stdexcept>

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
#include <list_processing/dynamic.hpp>
#include <list_processing/operators.hpp>

using std::optional;
using std::nullopt;

using FunctionUtility::rpart;

using ListProcessing::Dynamic::empty_alist;
using ListProcessing::Dynamic::pipe;


namespace ListProcessing::Testing
{

  TEST(AList, EmptyDoesNotHaveData){
    ASSERT_FALSE(hasData(empty_alist<char,int>));
  }

  TEST(AList, FObjEmptyDoesNotHaveData){
    using namespace ::ListProcessing::Operators;
    ASSERT_FALSE(hasData(empty_alist<char,int>));
  }

  TEST(AList, EmptyIsEmpty){
    ASSERT_TRUE(isEmpty(empty_alist<char,int>));
  }

  TEST(AList, FObjEmptyIsEmpty){
    using namespace ::ListProcessing::Operators;
    ASSERT_TRUE(isEmpty(empty_alist<char,int>));
  }

  TEST(AList, SetHasData){
    EXPECT_TRUE(hasData(set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, FObjSetHasData){
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(hasData(set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, SetIsNotEmpty){
    EXPECT_FALSE(isEmpty(set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, FObjSetIsNotEmpty){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(isEmpty(set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, SetHasKey){
    EXPECT_TRUE(hasKey('x', set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, FObjSetHasKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(empty_alist<char, int>,
                     set('x', 3),
                     hasKey('x')));
  }

  TEST(AList, SetDoesNotHaveKeyNotSet){
    EXPECT_FALSE(hasKey('y', set('x', 3, empty_alist<char,int>)));
  }

  TEST(AList, FObjSetDoesNotHaveKeyNotSet){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist<char,int>,
                      set('x', 3),
                      hasKey('y')));
  }

  TEST(AList, UnsetRemovesKey){
    EXPECT_FALSE(hasKey('x', unset('x', set('x', 3, empty_alist<char,int>))));
  }

  TEST(AList, FObjUnsetRemovesKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist<char,int>,
                      set('x', 3),
                      unset('x'),
                      hasKey('x')));
  }

  TEST(AList, UnsetOnlyRemovesFirstOccurance){
    EXPECT_TRUE(hasKey('x', unset('x', set('x', 4, set('x', 3, empty_alist<char,int>)))));
  }

  TEST(AList, FObjUnsetOnlyRemovesFirstOccurance){
    using namespace ::ListProcessing::Operators;
    EXPECT_TRUE(pipe(empty_alist<char,int>,
                     set('x', 3),
                     set('x', 4),
                     unset('x'),
                     hasKey('x')));
  }

  TEST(AList, RemoveRemovesAllOccurances){
    EXPECT_FALSE(hasKey('x', remove('x', set('x', 4, set('x', 3, empty_alist<char,int>)))));
  }

  TEST(AList, FObjRemoveRemovesAllOccurances){
    using namespace ::ListProcessing::Operators;
    EXPECT_FALSE(pipe(empty_alist<char,int>,
                      set('x', 3),
                      set('x', 4),
                      remove('x'),
                      hasKey('x')));
  }

  TEST(AList, ForceGetReturnsValueByKey){
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return forceGet('x', 0, alist); }),
      3);
  }

  TEST(AList, FObjForceGetReturnsValueByKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           set('x', 3),
           forceGet('x', 0)),
      3);
  }

  TEST(AList, ForceGetReturnsAlternateForMissingKey){
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return forceGet('y', 0, alist); }),
      0);
  }

  TEST(AList, FObjForceGetReturnsAlternateForMissingKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           set( 'x', 3),
           forceGet('y', 0)),
      0);
  }

  TEST(AList, MaybeGetReturnsOptionalValueByKey){
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return maybeGet('x', alist); }),
      optional(3));
  }

  TEST(AList, FObjMaybeGetReturnsOptionalValueByKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           set('x', 3),
           maybeGet('x')),
      optional(3));
  }

  TEST(AList, MaybeGetReturnsNullOptForMissingKey){
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return maybeGet('y', alist); }),
      nullopt);
  }

  TEST(AList, FObjMaybeGetReturnsNullOptForMissingKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           set( 'x', 3),
           maybeGet('y')),
      optional<int>{nullopt});
  }

  TEST(AList, TryGetReturnsValueByKey){
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return tryGet('x', alist); }),
      3);
  }

  TEST(AList, FObjTryGetReturnsValueByKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_EQ(
      pipe(empty_alist<char,int>,
           set('x', 3),
           tryGet('x')),
      3);
  }

  TEST(AList, TryGetReturnsThrowsForMissingKey){
    EXPECT_THROW(
      pipe(empty_alist<char,int>,
           [](auto alist){ return set('x', 3, alist); },
           [](auto alist){ return tryGet('y', alist); }),
      std::logic_error);
  }

  TEST(AList, FObjTryGetReturnsThrowsForMissingKey){
    using namespace ::ListProcessing::Operators;
    EXPECT_THROW(
      pipe(empty_alist<char,int>,
           set('x', 3),
           tryGet('y')),
      std::logic_error);
  }
} // end of namespace ListProcessing::Testing
