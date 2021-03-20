/**
 * DirectX.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_H_
#define SEEDENGINE_INCLUDE_RUNTIME_GRAPHICS_DIRECT_X_H_

#include "GraphicsAPI.hpp"

#if ENGINE_GRAPHICS_DIRECTX

#ifdef ENGINE_COMPILE_DEBUG
    #define D3DCOMPILE_DEBUG 1
#endif

#include <d2d1.h> // Direct2D
#include <d3d11.h> // Direct3D 11
#include <d3d12.h> // Direct3D 12

// Include the Direct3D Library files
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "d3d11.lib")

#endif

#endif