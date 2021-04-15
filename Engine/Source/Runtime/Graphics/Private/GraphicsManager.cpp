/**
 * @file GraphicsManager.cpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "GraphicsManager.hpp"

#if ENGINE_GRAPHICS_OPENGL
    #include "OpenGL/OpenGLGraphicsManager.hpp"
#endif
#if ENGINE_GRAPHICS_DIRECTX
    #include "DirectX/DirectXGraphicsManager.hpp"
#endif
#if ENGINE_GRAPHICS_VULKAN
    #include "Vulkan/VulkanGraphicsManager.hpp"
#endif
#if ENGINE_GRAPHICS_METAL
    #include "Metal/MetalGraphicsManager.hpp"
#endif

namespace seedengine {

    GraphicsManager* GraphicsManager::s_instance = nullptr;

    GraphicsManager::GraphicsManager(EGraphicsFramework framework) {
        m_framework = framework;
    }

    GraphicsManager::~GraphicsManager() = default;

    EGraphicsFramework GraphicsManager::GetFramework() {
        return s_instance->m_framework;
    }

    void GraphicsManager::SetFramework(EGraphicsFramework framework) {
        // Ensure the passed framework is available
        if (GetAvailableFrameworks().find(framework) != -1) {
            if (Initialized() && framework != GetFramework()) {
                Shutdown();
                Startup(framework);
            }
            else if (!Initialized()) {
                // TODO: Error output, graphics are currently uninitialized
            }
        }
        else {
            // TODO: Error output here, invalid graphics framework
        }
    }

    Array<EGraphicsFramework> GraphicsManager::GetAvailableFrameworks() noexcept {
        return {
#if ENGINE_GRAPHICS_OPENGL
            EGraphicsFramework::OPEN_GL,
#endif
#if ENGINE_GRAPHICS_DIRECTX
            EGraphicsFramework::DIRECT_X,
#endif
#if ENGINE_GRAPHICS_VULKAN
            EGraphicsFramework::VULKAN,
#endif
#if ENGINE_GRAPHICS_METAL
            EGraphicsFramework::METAL,
#endif
        };
    }

    bool GraphicsManager::Startup() {
        // TODO: Load default from config
        return Startup(GetAvailableFrameworks()[0]);
    }

    bool GraphicsManager::Startup(EGraphicsFramework framework) {
        if (Initialized()) return false; // TODO: Add warning here
        switch (framework) {
#if ENGINE_GRAPHICS_OPENGL
            case EGraphicsFramework::OPEN_GL:
                s_instance = new OpenGLGraphicsManager();
                break;
#endif
#if ENGINE_GRAPHICS_DIRECTX
            case EGraphicsFramework::DIRECT_X:
                s_instance = new DirectXGraphicsManager();
                break;
#endif
#if ENGINE_GRAPHICS_VULKAN
            case EGraphicsFramework::VULKAN:
                s_instance = new VulkanGraphicsManager();
                break;
#endif
#if ENGINE_GRAPHICS_METAL
            case EGraphicsFramework::METAL:
                s_instance = new MetalGraphicsManager();
                break;
#endif
            default:
                // Error: unknown graphics framework
                break;
        }
        return s_instance;
    }

    void GraphicsManager::Shutdown() {
        delete s_instance;
        s_instance = nullptr;
    }

    bool GraphicsManager::Initialized() {
        return s_instance;
    }

}