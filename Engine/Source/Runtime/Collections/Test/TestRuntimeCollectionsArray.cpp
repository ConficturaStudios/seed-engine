/**
 * @file TestRuntimeCollectionsArray.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include <iostream>
#include <gtest/gtest.h>
#include "Array.hpp"

TEST(TestRuntimeCollectionsArray, GeneralTest) {
    using namespace seedengine;

    Array<int> array({ 5, 3, 2, 22, -3 });

    EXPECT_EQ(5, array.size());

    EXPECT_EQ(5, array[0]);
    EXPECT_EQ(3, array[1]);
    EXPECT_EQ(2, array[2]);
    EXPECT_EQ(22, array[3]);
    EXPECT_EQ(-3, array[4]);

    EXPECT_EQ(3, array.find(22));
    Array<int> sub = array.subarray(0, 3);

    EXPECT_EQ(3, sub.size());

    EXPECT_EQ(5, sub[0]);
    EXPECT_EQ(3, sub[1]);
    EXPECT_EQ(2, sub[2]);

    EXPECT_EQ(array[0], sub[0]);
    EXPECT_EQ(array[1], sub[1]);
    EXPECT_EQ(array[2], sub[2]);

    int count = 0;
    int total = 0;

    for (const int& i : sub) {
        count++;
        total += i;
    }

    EXPECT_EQ(3, count);
    EXPECT_EQ(10, total);

    Array<int> con = sub.concat(array);

    EXPECT_EQ(8, con.size());

    EXPECT_EQ(5, con[0]);
    EXPECT_EQ(3, con[1]);
    EXPECT_EQ(2, con[2]);
    EXPECT_EQ(5, con[3]);
    EXPECT_EQ(3, con[4]);
    EXPECT_EQ(2, con[5]);
    EXPECT_EQ(22, con[6]);
    EXPECT_EQ(-3, con[7]);

    EXPECT_EQ(sub[0], con[0]);
    EXPECT_EQ(sub[1], con[1]);
    EXPECT_EQ(sub[2], con[2]);

    EXPECT_EQ(array[0], con[3]);
    EXPECT_EQ(array[1], con[4]);
    EXPECT_EQ(array[2], con[5]);
    EXPECT_EQ(array[3], con[6]);
    EXPECT_EQ(array[4], con[7]);

    array[3] = 27;

    EXPECT_EQ(27, array[3]);

    EXPECT_NE(array[3], con[6]);

}