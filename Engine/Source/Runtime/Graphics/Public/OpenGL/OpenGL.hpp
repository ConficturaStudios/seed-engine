/**
 * OpenGL.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_OPEN_GL_H_

#include "GraphicsAPI.hpp"

#if ENGINE_GRAPHICS_OPENGL

// Android Preprocessor Definitions
#if defined(__ANDROID__)
    #define GLFW_INCLUDE_ES2
    #define GLFW_INCLUDE_ES32
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif

#endif