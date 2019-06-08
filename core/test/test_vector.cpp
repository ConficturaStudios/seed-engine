// test_vector.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Vector.hpp"

TEST(Vector2Test, GeneralTest) {
    using namespace seedengine;
    Vector2 vec2_0 = Vector2();
    EXPECT_EQ(vec2_0, Vector2(0, 0));
    vec2_0.x = 1;
    EXPECT_EQ(vec2_0, Vector2(1, 0));
    EXPECT_EQ(Vector2::magnitude(vec2_0), 1);
}

TEST(Vector3Test, GeneralTest) {
    using namespace seedengine;
    Vector3 vec3_0 = Vector3();
    EXPECT_EQ(vec3_0, Vector3(0, 0, 0));
    vec3_0.x = 1;
    EXPECT_EQ(vec3_0, Vector3(1, 0, 0));
    EXPECT_EQ(Vector3::magnitude(vec3_0), 1);
}

TEST(Vector4Test, GeneralTest) {
    using namespace seedengine;
    Vector4 vec4_0 = Vector4();
    EXPECT_EQ(vec4_0, Vector4(0, 0, 0, 0));
    vec4_0.x = 1;
    EXPECT_EQ(vec4_0, Vector4(1, 0, 0, 0));
    EXPECT_EQ(Vector4::magnitude(vec4_0), 1);
}
