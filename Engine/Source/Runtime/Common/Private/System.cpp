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

    // TODO: Move naming functionality to specialized toString method
    
    String System::GetPlatformName(const EPlatform& platform) noexcept {
        if (platform == EPlatform::WINDOWS) {
            return "Windows";
        }
        else if (platform == EPlatform::LINUX) {
            return "Linux";
        }
        else if (platform == EPlatform::GNU_LINUX) {
            return "GNU Linux";
        }
        else if (platform == EPlatform::MAC_OS) {
            return "Mac OS";
        }
        else if (platform == EPlatform::UNIX) {
            return "Unix";
        }
        else if (platform == EPlatform::ANDROID) {
            return "Android";
        }
        else if (platform == EPlatform::IOS) {
            return "iOS";
        }
        else if (platform == EPlatform::IOS_SIM) {
            return "iOS Simulator";
        }
        else if (platform == EPlatform::PS4) {
            return "Playstation 4";
        }
        else if (platform == EPlatform::PS5) {
            return "Playstation 5";
        }
        else if (platform == EPlatform::XBOX_ONE) {
            return "XBox One";
        }
        else if (platform == EPlatform::XBOX_X) {
            return "XBox Series X";
        }
        else if (platform == EPlatform::NINTENDO_SWITCH) {
            return "Nintendo Switch";
        }
        else {
            return "Unknown";
        }
    }

}