//
// ... Standard header files
//
#include <iostream>
#include <sstream>

//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... List Processing header files
//
#include <list_processing/dynamic_shared_list.hpp>

using std::stringstream;
using ListProcessing::Dynamic::Shared;
using ListProcessing::Dynamic::sharedList;


namespace ListProcessing::Testing
{
  TEST(Shared, Construction){
    Shared x(3);
    EXPECT_EQ(*x, 3);
  }

  TEST(Shared, ExplicitCast)
  {
    Shared x(3);
    EXPECT_EQ(int(x), 3);
  }

  TEST(Shared, Addition)
  {
    Shared a(3);
    Shared b(4);
    auto c = a + b;
    EXPECT_EQ(*c, *a + *b);
  }

  TEST(Shared, AdditionLeft)
  {
    Shared a(3);
    auto c = a + 4;
    EXPECT_EQ(*c, *a + 4);
  }

  TEST(Shared, AdditionRight)
  {
    Shared b(4);
    auto c = 3 + b;
    EXPECT_EQ(*c, 3 + *b);
  }

  TEST(Shared, Subtraction)
  {
    Shared a(3);
    Shared b(4);
    auto c = a - b;
    EXPECT_EQ(*c, *a - *b);
  }

  TEST(Shared, SubtractionLeft)
  {
    Shared a(3);
    auto c = a - 4;
    EXPECT_EQ(*c, *a - 4);
  }

  TEST(Shared, SubtractionRight)
  {
    Shared b(4);
    auto c = 3 - b;
    EXPECT_EQ(*c, 3 - *b);
  }



  TEST(Shared, Multiplication)
  {
    Shared a(3);
    Shared b(4);
    auto c = a * b;
    EXPECT_EQ(*c, *a * *b);
  }

  TEST(Shared, MultiplicationLeft)
  {
    Shared a(3);
    auto c = a * 4;
    EXPECT_EQ(*c, *a * 4);
  }

  TEST(Shared, MultiplicationRight)
  {
    Shared b(4);
    auto c = 3 * b;
    EXPECT_EQ(*c, 3 * *b);
  }


  TEST(Shared, Division)
  {
    Shared a(3);
    Shared b(4);
    auto c = a / b;
    EXPECT_EQ(*c, *a / *b);
  }

  TEST(Shared, DivisionLeft)
  {
    Shared a(3);
    auto c = a / 4;
    EXPECT_EQ(*c, *a / 4);
  }

  TEST(Shared, DivisionRight)
  {
    Shared b(4);
    auto c = 3 / b;
    EXPECT_EQ(*c, 3 / *b);
  }


  TEST(Shared, Show){
    Shared x = 3;
    stringstream ss;
    ss << x;
    EXPECT_EQ(ss.str(), "3");
  }

  TEST(Shared, ListConstruction){
    auto xs = sharedList(1, 2, 3);
    EXPECT_EQ(length(xs), 3);
    EXPECT_EQ(*head(xs), 1);
    EXPECT_EQ(*head(tail(xs)), 2);
    EXPECT_EQ(*head(tail(tail(xs))), 3);
  }
} // end of namespace ListProcessing::Testing
