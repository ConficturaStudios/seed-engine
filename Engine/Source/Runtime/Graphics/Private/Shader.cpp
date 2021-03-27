/**
 * Shader.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "Shader.hpp"
#include "GraphicsManager.hpp"

#if ENGINE_GRAPHICS_OPENGL
    #include "OpenGL/OpenGLShader.hpp"
#endif
#if ENGINE_GRAPHICS_DIRECTX
    #include "DirectX/DirectXShader.hpp"
#endif
#if ENGINE_GRAPHICS_VULKAN
    #include "Vulkan/VulkanShader.hpp"
#endif
#if ENGINE_GRAPHICS_METAL
    #include "Metal/MetalShader.hpp"
#endif

namespace seedengine {

    Shader::~Shader() {
        //cleanUp();
        //TODO: determine how to force cleanup on destruction (add to implementation destructors?)
    }

    SharedPtr<Shader> Shader::Create(const String& filepath) {
        SharedPtr<Shader> shader;
        switch (GraphicsManager::GetFramework()) {
#if ENGINE_GRAPHICS_OPENGL
            case EGraphicsFramework::OPEN_GL:
                shader = CreateSharedPtr<OpenGLShader>();
                break;
#endif
#if ENGINE_GRAPHICS_DIRECTX
            case EGraphicsFramework::DIRECT_X:
                shader = CreateSharedPtr<DirectXShader>();
                break;
#endif
#if ENGINE_GRAPHICS_VULKAN
            case EGraphicsFramework::VULKAN:
                shader = CreateSharedPtr<VulkanShader>();
                break;
#endif
#if ENGINE_GRAPHICS_METAL
            case EGraphicsFramework::METAL:
                shader = CreateSharedPtr<MetalShader>();
                break;
#endif
            default:
                // Error: unknown graphics framework
                return nullptr;
        }
        if (shader->init(filepath)) return shader;
        else return nullptr;
    }

    SharedPtr<Shader> Shader::Create(const String& name, const String& vs_filepath, const String& fs_filepath) {
        SharedPtr<Shader> shader;
        switch (GraphicsManager::GetFramework()) {
#if ENGINE_GRAPHICS_OPENGL
            case EGraphicsFramework::OPEN_GL:
                shader = CreateSharedPtr<OpenGLShader>();
                break;
#endif
#if ENGINE_GRAPHICS_DIRECTX
                case EGraphicsFramework::DIRECT_X:
                shader = CreateSharedPtr<DirectXShader>();
                break;
#endif
#if ENGINE_GRAPHICS_VULKAN
                case EGraphicsFramework::VULKAN:
                shader = CreateSharedPtr<VulkanShader>();
                break;
#endif
#if ENGINE_GRAPHICS_METAL
                case EGraphicsFramework::METAL:
                shader = CreateSharedPtr<MetalShader>();
                break;
#endif
            default:
                // Error: unknown graphics framework
                return nullptr;
        }
        if (shader->init(name, vs_filepath, fs_filepath)) return shader;
        else return nullptr;
    }

}