// test_math.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Math.hpp"

TEST(MathTest, GeneralTest) {
    using namespace seedengine;
    EXPECT_EQ(math::abs(-2), 2);
    EXPECT_EQ(math::abs(2), 2);
    EXPECT_EQ(math::abs(-2.0), 2.0);
    EXPECT_EQ(math::abs(-2.0f), 2.0f);
}