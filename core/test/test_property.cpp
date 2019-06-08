// test_property.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Property.hpp"

TEST(PropertyTest, GeneralTest) {
    using namespace seedengine;
    Property<int> t = 0;
    EXPECT_EQ(t, 0);
    t = 3;
    EXPECT_EQ(t, 3);
    EXPECT_EQ(t + 5, 8);
    int i0 = 0;
    Property<int> t1(
            i0,
            GET(int) {
                return i0;
            },
            SET(int) {
                return i0 = value;
            }
        );
    EXPECT_EQ(i0, 0);
    EXPECT_EQ(t1, i0);
    t1 = 5;
    EXPECT_EQ(i0, 5);
    EXPECT_EQ(t1, 5);
    i0 = 7;
    EXPECT_EQ(i0, 7);
    EXPECT_EQ(t1, 7);
}