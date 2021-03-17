/**
 * @file TestRuntimeCollectionsLinkedList.cpp
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
#include "LinkedList.hpp"

TEST(TestRuntimeCollectionsLinkedList, GeneralTest) {
    using namespace seedengine;

    List<int>* list = new LinkedList<int>();

    EXPECT_EQ(0, list->size());
    EXPECT_EQ(true, list->isEmpty());

    list->add(0, 18);

    EXPECT_EQ(1, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test accessors

    EXPECT_EQ(18, list->get(0));
    EXPECT_EQ(18, (*list)[0]);
    EXPECT_EQ(18, list->first());
    EXPECT_EQ(18, list->last());

    EXPECT_EQ(18, list->set(0, 12));

    EXPECT_EQ(12, list->remove(0));

    EXPECT_EQ(0, list->size());
    EXPECT_EQ(true, list->isEmpty());

    // Test addFirst

    list->addFirst(4);
    list->addFirst(2);
    list->addFirst(0);

    EXPECT_EQ(0, list->get(0));
    EXPECT_EQ(2, list->get(1));
    EXPECT_EQ(4, list->get(2));

    EXPECT_EQ(3, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test addLast

    list->addLast(7);
    list->addLast(10);
    list->addLast(11);

    EXPECT_EQ(0, list->get(0));
    EXPECT_EQ(2, list->get(1));
    EXPECT_EQ(4, list->get(2));
    EXPECT_EQ(7, list->get(3));
    EXPECT_EQ(10, list->get(4));
    EXPECT_EQ(11, list->get(5));

    EXPECT_EQ(6, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test insertion

    list->add(3, 5);

    EXPECT_EQ(0, list->get(0));
    EXPECT_EQ(2, list->get(1));
    EXPECT_EQ(4, list->get(2));
    EXPECT_EQ(5, list->get(3));
    EXPECT_EQ(7, list->get(4));
    EXPECT_EQ(10, list->get(5));
    EXPECT_EQ(11, list->get(6));

    EXPECT_EQ(7, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test removeIf

    list->removeIf([](const int& element) -> bool { return element % 2 == 1; });

    EXPECT_EQ(0, list->get(0));
    EXPECT_EQ(2, list->get(1));
    EXPECT_EQ(4, list->get(2));
    EXPECT_EQ(10, list->get(3));

    EXPECT_EQ(4, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test contains

    EXPECT_EQ(true, list->contains(4));
    EXPECT_EQ(false, list->contains(-10));

    // Test removal

    EXPECT_EQ(4, list->remove(2));

    EXPECT_EQ(3, list->size());
    EXPECT_EQ(false, list->isEmpty());

    EXPECT_EQ(10, list->removeLast());

    EXPECT_EQ(2, list->size());
    EXPECT_EQ(false, list->isEmpty());

    EXPECT_EQ(0, list->removeFirst());

    EXPECT_EQ(1, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test add at size()

    list->add(1, 3);

    EXPECT_EQ(2, list->size());
    EXPECT_EQ(false, list->isEmpty());

    // Test clear

    list->clear();

    EXPECT_EQ(0, list->size());
    EXPECT_EQ(true, list->isEmpty());

    // Test toArray and iterator

    list->addFirst(2);
    list->addFirst(1);
    list->addFirst(0);

    EXPECT_EQ(3, list->size());
    EXPECT_EQ(false, list->isEmpty());

    int count = 0;
    int total = 0;

    for (const int& i : *list) {
        count++;
        total += i;
    }

    EXPECT_EQ(list->size(), count);
    EXPECT_EQ(3, count);

    EXPECT_EQ(3, total);

    Array<int> array = list->toArray();

    EXPECT_EQ(3, array.size());

    EXPECT_EQ(list->get(0), array[0]);
    EXPECT_EQ(list->get(1), array[1]);
    EXPECT_EQ(list->get(2), array[2]);

    int aCount = 0;
    int aTotal = 0;

    for (const int& i : array) {
        aCount++;
        aTotal += i;
    }

    EXPECT_EQ(count, aCount);
    EXPECT_EQ(total, aTotal);

    // Test modifying the new array

    EXPECT_EQ(0, array[0]);
    EXPECT_EQ(list->get(0), array[0]);
    array[0] = 100;
    EXPECT_EQ(0, list->get(0));
    EXPECT_EQ(100, array[0]);
    EXPECT_NE(list->get(0), array[0]);

    EXPECT_EQ(1, list->get(1));
    EXPECT_EQ(1, array[1]);
    (*list)[1] = 200;
    EXPECT_EQ(200, list->get(1));
    EXPECT_EQ(1, array[1]);
    EXPECT_NE(list->get(1), array[1]);

}