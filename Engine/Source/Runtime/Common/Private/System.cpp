/**
 * System.cpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#include "System.hpp"

namespace seedengine {

    // TODO: Make these toString like methods into dedicated functions for each enum
    // TODO: Look into possible compile time solutions to reduce execution time for name lookup
    
    String System::GetPlatformName(const Platform& platform) noexcept {
        if (platform == Platform::WINDOWS) {
            return "Windows";
        }
        else if (platform == Platform::LINUX) {
            return "Linux";
        }
        else if (platform == Platform::GNU_LINUX) {
            return "GNU Linux";
        }
        else if (platform == Platform::MAC_OS) {
            return "Mac OS";
        }
        else if (platform == Platform::UNIX) {
            return "Unix";
        }
        else if (platform == Platform::ANDROID) {
            return "Android";
        }
        else if (platform == Platform::IOS) {
            return "iOS";
        }
        else if (platform == Platform::IOS_SIM) {
            return "iOS Simulator";
        }
        else if (platform == Platform::PS4) {
            return "Playstation 4";
        }
        else if (platform == Platform::PS5) {
            return "Playstation 5";
        }
        else if (platform == Platform::XBOX_ONE) {
            return "XBox One";
        }
        else if (platform == Platform::XBOX_X) {
            return "XBox Series X";
        }
        else if (platform == Platform::NINTENDO_SWITCH) {
            return "Nintendo Switch";
        }
        else {
            return "Unknown";
        }
    }

    String System::GetGraphicsModeName(const GraphicsMode& mode) noexcept {
        if (mode == GraphicsMode::OPEN_GL) {
            return "Open GL";
        }
        else if (mode == GraphicsMode::DIRECT_X) {
            return "DirectX";
        }
        else if (mode == GraphicsMode::VULKAN) {
            return "Vulkan";
        }
        else if (mode == GraphicsMode::METAL) {
            return "Metal";
        }
        else {
            return "Unknown";
        }
    }

}