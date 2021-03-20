/**
 * @file Window.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Window.hpp"

namespace seedengine {

    UniquePtr<Window> Window::Create() {
        return seedengine::UniquePtr<Window>();
    }
}