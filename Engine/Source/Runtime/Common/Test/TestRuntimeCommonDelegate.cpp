/**
 * @file TestRuntimeCommonDelegate.cpp
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

#include "Delegate.hpp"

struct DelegateTestObject {

    int value;

    void func1(int i) const {
        std::cout << "F1: Member value: (" << value << "); Argument: (" << i << ")" << std::endl;
    }

    void func2(int i) const {
        std::cout << "F2: Member value: (" << value << "); Argument: (" << i << ")" << std::endl;
    }

    void func3(int i) {
        std::cout << "F3: Member value + 1: (" << ++value << "); Argument: (" << i << ")" << std::endl;
    }
};

void DelegateTestGlobalFunc(int i) {
    std::cout << "Global: Argument: (" << i << ")" << std::endl;
}

TEST(TestRuntimeCommonDelegate, GeneralTest) {
    using namespace seedengine;

    Delegate<int> delegate;

    delegate += &DelegateTestGlobalFunc;

    DelegateTestObject obj1 = { 5 };
    DelegateTestObject obj2 = { 10 };
    DelegateTestObject obj3 = { 15 };
    DelegateTestObject obj4 = { 20 };

    delegate.bindObject<DelegateTestObject, &DelegateTestObject::func1>(&obj1);
    delegate.bindObject<DelegateTestObject, &DelegateTestObject::func1>(&obj2);
    delegate.bindObject<DelegateTestObject, &DelegateTestObject::func2>(&obj3);
    delegate.bindObject<DelegateTestObject, &DelegateTestObject::func3>(&obj4);
    //delegate.bindObject(&obj2, &DelegateTestObject::func1);
    //delegate.bindObject(&obj3, &DelegateTestObject::func2);

    delegate.broadcast(3);
    delegate.broadcast(7);

}