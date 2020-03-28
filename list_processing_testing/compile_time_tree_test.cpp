//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/compile_time.hpp>

using ListProcessing::CompileTime::empty_tree;
using ListProcessing::CompileTime::list;
using ListProcessing::CompileTime::tree;

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

  TEST(CompileTimeTree, Make)
  {
    constexpr auto t = tree(
      tree('a', tree(1, 2, 3)),
      tree('b', tree(4, 5, 6)),
      tree('c', tree(7, 8, 9)));
    std::cout << list(1, 2, 3) << std::endl;
    ASSERT_FALSE(isEmpty(t));
    ASSERT_EQ(position(t), list(0L));
    ASSERT_EQ(open(open(t)), 'a');
    ASSERT_EQ(open(open(fwd(close(open(t))))), 'b');
  }

} // end of namespace ListProcessing::Testing
