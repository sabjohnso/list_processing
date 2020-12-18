//
// ... Testing header files
//
#include <gtest/gtest.h>

#include <list_processing/dynamic.hpp>

using ListProcessing::Dynamic::empty_alist;
using ListProcessing::Dynamic::pipe;

namespace ListProcessing::Testing
{

  TEST(AList, EmptyIsEmpty)
  {
    ASSERT_TRUE(isEmpty(empty_alist<char,int>));
  }
} // end of namespace ListProcessing::Testing
