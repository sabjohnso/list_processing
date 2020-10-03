//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_tree;

namespace ListProcessing::Testing
{

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

    ASSERT_EQ(
      pipe(empty_tree<char>,
           [](auto tree){ return insert(tree, 'a'); },
           [](auto tree){ return write(tree, 'b'); },
           [](auto tree){ return read(tree); }),
      'b');
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
