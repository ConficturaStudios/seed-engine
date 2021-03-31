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
        // Initialize GLFW
        glfwSetErrorCallback([](int error, const char* description) -> void {
            // TODO: Error output to graphics logger here
            Logger errorTemp("Graphics");
            errorTemp.error("GLFW Error {0}: {1}", error, description);
        });
        Logger log("Graphics");
        log.info("Initializing GLFW...");
        if (!glfwInit()) {
            // TODO: Error output (GLFW failed)
            log.warn("Failed to initialize GLFW");
        } else {
            log.info("Initialized GLFW.");
        }
    }

    OpenGLGraphicsManager::~OpenGLGraphicsManager() {
        Logger log("Graphics");
        glfwTerminate();
        log.warn("Terminating GLFW");
    }

}