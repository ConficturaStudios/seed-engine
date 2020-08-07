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
#include "GraphicsMode.hpp"
#include "System.hpp"

#include "OpenGL/OpenGLShader.hpp"
#include "DirectX/DirectXShader.hpp"
#include "Vulkan/VulkanShader.hpp"
#include "Metal/MetalShader.hpp"

namespace seedengine {

    Shader::~Shader() {
        //cleanUp();
        //TODO: determine how to force cleanup on destruction (add to implementation destructors?)
    }

    SharedPtr<Shader> Shader::Create(const String& filepath) {
        if constexpr (System::GetGraphicsMode() == GraphicsMode::OPEN_GL) {
            auto shader = CreateSharedPtr<OpenGLShader>();
            if (shader->init(filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::DIRECT_X) {
            auto shader = CreateSharedPtr<DirectXShader>();
            if (shader->init(filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::VULKAN) {
            auto shader = CreateSharedPtr<VulkanShader>();
            if (shader->init(filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::METAL) {
            auto shader = CreateSharedPtr<MetalShader>();
            if (shader->init(filepath)) return shader;
            else return nullptr;
        }
        else {
            // Error
            return nullptr;
        }
    }

    SharedPtr<Shader> Shader::Create(const String& name, const String& vs_filepath, const String& fs_filepath) {
        if constexpr (System::GetGraphicsMode() == GraphicsMode::OPEN_GL) {
            auto shader = CreateSharedPtr<OpenGLShader>();
            if (shader->init(name, vs_filepath, fs_filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::DIRECT_X) {
            auto shader = CreateSharedPtr<DirectXShader>();
            if (shader->init(name, vs_filepath, fs_filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::VULKAN) {
            auto shader = CreateSharedPtr<VulkanShader>();
            if (shader->init(name, vs_filepath, fs_filepath)) return shader;
            else return nullptr;
        }
        else if (System::GetGraphicsMode() == GraphicsMode::METAL) {
            auto shader = CreateSharedPtr<MetalShader>();
            if (shader->init(name, vs_filepath, fs_filepath)) return shader;
            else return nullptr;
        }
        else {
            // Error
            return nullptr;
        }
    }

}