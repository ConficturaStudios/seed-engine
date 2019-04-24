// test_transform.cpp

#include <iostream>
#include <gtest/gtest.h>
#include "Transform.hpp"

TEST (TransformTest, GeneralTest) {
    seedengine::Transform t0 = seedengine::Transform();
    EXPECT_EQ(t0.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(t0.getEulerAngles(), glm::vec3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(t0.getScale(), glm::vec3(1.0f, 1.0f, 1.0f));

    t0.setPosition(10.0f, 5.0f, 6.0f);

    EXPECT_EQ(t0.getPosition(), glm::vec3(10.0f, 5.0f, 6.0f));
    EXPECT_NE(t0.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
}
