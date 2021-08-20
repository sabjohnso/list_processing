// Bucket is a nonuserfacing class.  As such, these tests can be safely deleted
// if their maintenance becomes expensive.

//
// ... Standard header files
//
#include <string>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic/Bucket.hpp>

using std::string;
using namespace std::literals;

namespace ListProcessing::Dynamic::Details::Testing {
  TEST(Bucket, DefaultConstruction)
  {
    Bucket<string, int> bucket{};
    for (auto i = 0; i < bucket.extent; ++i) {
      EXPECT_FALSE(bucket.slotPopulated(i));
    }
  }

  TEST(Bucket, AddOnePair)
  {
    Bucket<string, int> bucket{};
    auto response = bucket.set(0, pair("x"s, 3));
    EXPECT_EQ(response, BucketResponse::injection);
    EXPECT_TRUE(bucket.slotPopulated(0));
    EXPECT_EQ(bucket.get(0).first, "x"s);
    EXPECT_EQ(bucket.get(0).second, 3);
  }

  TEST(Bucket, AttemptChangeMappedValue)
  {
    Bucket<string, int> bucket{};
    bucket.set(0, pair("x"s, 3));
    auto response = bucket.set(0, pair("x"s, 4));
    EXPECT_EQ(response, BucketResponse::mutation);
    EXPECT_EQ(bucket.get(0).first, "x"s);
    EXPECT_EQ(bucket.get(0).second, 3);
  }

  TEST(Bucket, AttemptToCollideKeys)
  {
    Bucket<string, int> bucket{};
    bucket.set(0, pair("x"s, 3));
    auto response = bucket.set(0, pair("y"s, 4));
    EXPECT_EQ(response, BucketResponse::collision);
    EXPECT_EQ(bucket.get(0).first, "x"s);
    EXPECT_EQ(bucket.get(0).second, 3);
  }

} // namespace ListProcessing::Dynamic::Details::Testing
