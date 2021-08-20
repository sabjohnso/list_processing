//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_hash_table.hpp>

namespace ListProcessing::Dynamic::Testing {

  TEST(DynamicHashTable, FriendEmptyNotHasData)
  {
    EXPECT_FALSE(hasData(HashTable<int, double>{}));
  }

  TEST(DynamicHashTable, FriendEmptyIsEmpty)
  {
    EXPECT_TRUE(isEmpty(HashTable<int, double>{}));
  }

  TEST(DynamicHashTable, FriendOneItemHasData)
  {
    EXPECT_TRUE(hasData(HashTable<int, double>{{1, 2.3}, {3, 4.2}}));
  }

} // end of namespace ListProcessing::Dynamic::Testing
