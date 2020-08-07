/**
 * System.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_SYSTEM_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_SYSTEM_H_

#include "CommonAPI.hpp"
#include "Platform.hpp"
#include "GraphicsMode.hpp"
#include "String.hpp"

namespace seedengine {

    /**
     * @brief A static class for accessing system information.
     * 
     */
    class ENGINE_API System final {


        public:

            [[nodiscard]] static constexpr Platform GetCurrentPlatform() noexcept {
                #if defined(_WIN32)
                // Windows
                    return Platform::WINDOWS;
                #elif defined(__APPLE__) || defined(__MACH__)
                // Apple Preprocessor Definitions
                    #include "TargetConditionals.h"
                    #if TARGET_IPHONE_SIMULATOR
                    // iOS Simulator
                        return Platform::IOS_SIM;
                    #elif TARGET_OS_IPHONE
                    // iOS
                        return Platform::IOS;
                    #elif TARGET_OS_MAC
                    // Mac
                        return Platform::MAC_OS;
                    #else
                    // Unknown Apple Platform
                        return Platform::UNKOWN;
                    #endif
                #elif defined(__ANDROID__)
                // Android
                    return Platform::ANDROID;
                #elif defined(__linux__)
                // Linux
                    return Platform::LINUX;
                #elif defined(__gnu_linux__)
                // GNU Linux
                    return Platform::GNU_LINUX;
                #elif defined(unix) || defined(__unix) || defined(__unix__)
                // Unix
                    return Platform::UNIX;
                #else
                // Unknown Platform
                    return Platform::UNKOWN;
                #endif
            }

            [[nodiscard]] static constexpr Architecture GetCurrentArchitecture() noexcept  {

                // Current device's bit architecture
                    
                if constexpr (sizeof(void*) == 8) {
                    // 64 bit architecture
                    return Architecture::X64;
                }
                else if (sizeof(void*) == 4) {
                    // 32 bit architecture
                    return Architecture::X86;
                }
                else {
                    // Unknown architecture
                    return Architecture::UNKNOWN;
                }
            }

            [[nodiscard]] static String GetPlatformName(const Platform& platform) noexcept;


            [[nodiscard]] static constexpr GraphicsMode GetGraphicsMode() noexcept {
                return GraphicsMode::OPEN_GL;
                //TODO: Set graphics mode from ini, do compatibility check
            }

            [[nodiscard]] static String GetGraphicsModeName(const GraphicsMode& mode) noexcept;

    };

}

#endif