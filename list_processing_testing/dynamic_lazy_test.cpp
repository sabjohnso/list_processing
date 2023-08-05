//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_lazy.hpp>

namespace ListProcessing::Dynamic::Testing {
  TEST(DynamicLazy, ValueMem){
    auto x = lazy([=]{ return 3; });
    EXPECT_TRUE(x.isLazy());
  }

  TEST(DynamicLazy, ValueFriend){
    auto x = lazy([=]{ return 3; });
    EXPECT_TRUE(isLazy(x));
  }
}
