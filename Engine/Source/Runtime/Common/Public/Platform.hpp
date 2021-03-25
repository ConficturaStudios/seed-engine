/**
 * EPlatform.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_PLATFORM_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_PLATFORM_H_

#include "CommonAPI.hpp"

#include <cstdint>

#if defined(_WIN32)
    // Windows
    #define ENGINE_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    // Apple Preprocessor Definitions
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define ENGINE_PLATFORM_IOS_SIM
        #define ENGINE_PLATFORM_APPLE
    #elif TARGET_OS_IPHONE
        // iOS
        #define ENGINE_PLATFORM_IOS
        #define ENGINE_PLATFORM_APPLE
    #elif TARGET_OS_MAC
        // Mac
        #define ENGINE_PLATFORM_MAC
        #define ENGINE_PLATFORM_APPLE
    #else
        // Unknown Apple EPlatform
        #define ENGINE_PLATFORM_UNKNOWN
    #endif
#elif defined(__ANDROID__)
    // Android
    #define ENGINE_PLATFORM_ANDROID
#elif defined(__linux__)
    // Linux
    #define ENGINE_PLATFORM_LINUX
#elif defined(__gnu_linux__)
    // GNU Linux
    #define ENGINE_PLATFORM_GNU_LINUX
#elif defined(unix) || defined(__unix) || defined(__unix__)
    // Unix
    #define ENGINE_PLATFORM_UNIX
#else
    // Unknown EPlatform
    #define ENGINE_PLATFORM_UNKNOWN
#endif

// Handle unknown platforms
#ifdef ENGINE_PLATFORM_UNKNOWN
    #error "Unknown platform is not supported"
#endif

namespace seedengine {

    /**
     * @brief An enum containing available platforms.
     * 
     */
    enum class ENGINE_API EPlatform : uint32_t {

        UNKNOWN         = 0,

        DESKTOP         = 1,
        WINDOWS         = DESKTOP | DESKTOP << 1,
        LINUX           = DESKTOP | DESKTOP << 2,
        GNU_LINUX       = DESKTOP | DESKTOP << 3,
        MAC_OS          = DESKTOP | DESKTOP << 4,
        UNIX            = DESKTOP | DESKTOP << 5,

        MOBILE          = DESKTOP << 6,
        ANDROID         = MOBILE | MOBILE << 1,
        IOS             = MOBILE | MOBILE << 2,
        IOS_SIM         = MOBILE | MOBILE << 3,

        CONSOLE         = MOBILE << 4,

        PLAYSTATION     = CONSOLE | CONSOLE << 1,
        PS4             = PLAYSTATION | CONSOLE << 2,
        PS5             = PLAYSTATION | CONSOLE << 3,

        XBOX            = CONSOLE | CONSOLE << 4,
        XBOX_ONE        = XBOX | CONSOLE << 5,
        XBOX_X          = XBOX | CONSOLE << 6,

        NINTENDO        = CONSOLE | CONSOLE << 7,
        NINTENDO_SWITCH = NINTENDO | CONSOLE << 8
    };

    /**
     * @brief The memory architecture of the current platform.
     * 
     */
    enum class ENGINE_API EArchitecture : uint8_t {
        UNKNOWN = 0,
        X86     = 1,
        X64     = 2
    };


    

}

#endif