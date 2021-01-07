//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>
#include <list_processing/operators.hpp>

using ListProcessing::Dynamic::empty_tree;



namespace ListProcessing::Testing
{
  namespace // anonymous
  {
    constexpr auto pipe = ListProcessing::Operators::pipe;
  } // end of anonymous namespace


  TEST(Tree, EmptyTreeIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_tree<int>));
  }

  TEST(Tree, InsertEmptyTreeNotEmpty)
  {
    ASSERT_FALSE(isEmpty(insert(empty_tree<char>, 'a')));
  }

  TEST(Tree, RemoveInsertEmptyIsEmpty)
  {
    ASSERT_TRUE(isEmpty(remove(insert(empty_tree<char>, 'a'))));
  }

  TEST(Tree, InsertBranchIsNotEmpty)
  {
    ASSERT_FALSE(isEmpty(insertBranch(empty_tree<char>)));
  }

  TEST(Tree, ReadValueIsInsertedValue)
  {
    ASSERT_EQ(read(insert(empty_tree<char>, 'a')), 'a');
  }

  TEST(Tree, ReadValueIsWrittenValue)
  {
    ASSERT_EQ(
      read(write(insert(empty_tree<char>, 'a'), 'b')),
      'b');

    auto xs = pipe(empty_tree<char>,
           [](auto tree){ return insert(tree, 'a'); },
           [](auto tree){ return write(tree, 'b'); },
           [](auto tree){ return read(tree); });
    ASSERT_EQ(xs, 'b');
  }

  TEST(Tree, EmptyTreeBranchIsEmpty)
  {
    ASSERT_TRUE(isBranchEmpty(empty_tree<char>));
  }

  TEST(Tree, InsertBranchIsBranch)
  {
    ASSERT_TRUE(isBranch(insertBranch(empty_tree<char>)));
  }

  TEST(Tree, InsertBranchIsNotLeaf)
  {
    ASSERT_FALSE(isLeaf(insertBranch(empty_tree<char>)));
  }

  TEST(Tree, InsertBranchOpenBranch)
  {
    ASSERT_TRUE(isBranchEmpty(open(insertBranch(empty_tree<char>))));
  }

} // end of namespace ListProcessing::Testing
