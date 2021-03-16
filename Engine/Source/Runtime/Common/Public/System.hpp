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

        // Platform

            /**
             * @brief Gets the current platform that the application is running on.
             * 
             * @return The platform the application is running on.
             */
            [[nodiscard]] static constexpr EPlatform GetCurrentPlatform() noexcept {
                #ifdef ENGINE_PLATFORM_WINDOWS
                // Windows
                    return EPlatform::WINDOWS;
                #elif defined(ENGINE_PLATFORM_IOS_SIM)
                    return EPlatform::IOS_SIM;
                #elif defined(ENGINE_PLATFORM_IOS)
                    return EPlatform::IOS;
                #elif defined(ENGINE_PLATFORM_MAC)
                    return EPlatform::MAC_OS;
                #elif defined(ENGINE_PLATFORM_ANDROID)
                    return EPlatform::ANDROID;
                #elif defined(ENGINE_PLATFORM_LINUX)
                    return EPlatform::LINUX;
                #elif defined(ENGINE_PLATFORM_GNU_LINUX)
                    return EPlatform::GNU_LINUX;
                #elif defined(ENGINE_PLATFORM_UNIX)
                    return EPlatform::UNIX;
                #elif defined(ENGINE_PLATFORM_UNKNOWN)
                    return EPlatform::UNKOWN;
                #else
                    return EPlatform::UNKOWN;
                #endif
            }

            /**
             * @brief Returns the system architecture of the machine the application is running on.
             * 
             * @return The system architecture that the application is running on.
             */
            [[nodiscard]] static constexpr EArchitecture GetCurrentArchitecture() noexcept  {

                // Current device's bit architecture
                    
                if constexpr (sizeof(void*) == 8) {
                    // 64 bit architecture
                    return EArchitecture::X64;
                }
                else if (sizeof(void*) == 4) {
                    // 32 bit architecture
                    return EArchitecture::X86;
                }
                else {
                    // Unknown architecture
                    return EArchitecture::UNKNOWN;
                }
            }

            /**
             * @brief Returns the name of the provided system platform.
             * 
             * @param platform The platform to check.
             * @return String The name of the provided platform.
             */
            [[nodiscard]] static String GetPlatformName(const EPlatform& platform) noexcept;

            /**
             * @brief Returns the graphics mode being used by the engine.
             * 
             * @return GraphicsMode The graphics mode used by the engine.
             */
            [[nodiscard]] static constexpr GraphicsMode GetGraphicsMode() noexcept {
                return GraphicsMode::OPEN_GL;
                //TODO: Set graphics mode from ini, do compatibility check
            }

            /**
             * @brief Returns the name of the provided graphics mode.
             * 
             * @param mode The Graphics Mode to check.
             * @return String The name of the graphics mode.
             */
            [[nodiscard]] static String GetGraphicsModeName(const GraphicsMode& mode) noexcept;

        // IO

            // TODO: Add Log and Time functionality to System class

    };

}

#endif