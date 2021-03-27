/**
 * @file Graphics.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MODULE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_MODULE_H_

#include "GraphicsAPI.hpp"


#include "Color.hpp"
#include "Framebuffer.hpp"
#include "GraphicsManager.hpp"
#include "Image.hpp"
#include "Mesh.hpp"
#include "Renderbuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "DirectX/DirectX.hpp"
#include "Metal/Metal.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Vulkan/Vulkan.hpp"

#ifdef ENGINE_API
    #undef ENGINE_API
#endif

#endif