/**
 * @file OpenGLGraphicsManager.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "OpenGL/OpenGLGraphicsManager.hpp"
#include "OpenGL/OpenGL.hpp"

namespace seedengine {

    OpenGLGraphicsManager::OpenGLGraphicsManager() : GraphicsManager(EGraphicsFramework::OPEN_GL) {
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description) -> void {
            // TODO: Error output to graphics logger here
        });
    }

    OpenGLGraphicsManager::~OpenGLGraphicsManager() {
        glfwTerminate();
    }

}