// test_nullable.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Nullable.hpp"
#include "Object.hpp"

TEST(NullableTest, NullObjTest) {
    using namespace seedengine;

    EXPECT_EQ(nullobj, nullobj);

    Object o = Object();

    EXPECT_NE(o, nullobj);
    o = nullobj;
    EXPECT_EQ(o, nullobj);

    EXPECT_NE(Object("Test"), nullobj);
    
}