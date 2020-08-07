/**
 * GraphicsMode.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_GRAPHICS_MODE_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_GRAPHICS_MODE_H_

#include "CommonAPI.hpp"

namespace seedengine {

    /**
     * @brief The available graphics frameworks.
     * 
     */
    enum class ENGINE_API GraphicsMode : uint8_t {
        OPEN_GL = 0,
        VULKAN = 1,
        DIRECT_X = 2,
        METAL = 3
    };

}

#endif