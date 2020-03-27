//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_tree;

namespace ListProcessing::Testing
{

  TEST(CompileTimeTree, EmptyTreeIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_tree));
  }

  TEST(CompileTimeTree, EmptyTreeIsRoot)
  {
    ASSERT_TRUE(isRoot(empty_tree));
  }

  TEST(CompileTimeTree, InsertNotEmpty)
  {
    ASSERT_FALSE(isEmpty(insert(empty_tree, 'x')));
  }

  TEST(CompileTimeTee, ReadInsertedValue)
  {
    ASSERT_EQ(open(insert(empty_tree, 'x')), 'x');
  }

  TEST(CompileTimeTree, InsertBranch)
  {
    ASSERT_FALSE(isEmpty(insertBranch(empty_tree)));
  }

} // end of namespace ListProcessing::Testing
