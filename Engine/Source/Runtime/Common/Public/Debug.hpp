/**
 * @file Debug.hpp
 * 
 * @copyright Copyright (c) 2021 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_DEBUG_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_DEBUG_H_

#include "CommonAPI.hpp"
#include "CommonDefinitions.hpp"
#include "Log.hpp"
#include "Platform.hpp"

// Debug Macros
#ifdef ENGINE_COMPILE_DEBUG
// TODO: Create separate macro (ENGINE_DEBUG or ENGINE_ENABLE_DEBUG) from ENGINE_COMPILE_DEBUG to allow debugging in release mode

    // Debug break macro

    #ifdef ENGINE_PLATFORM_WINDOWS
        #define ENGINE_DEBUG_BREAK() __debugbreak()
    #elif defined(ENGINE_PLATFORM_LINUX)
        #include <signal.h>
        #define ENGINE_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #warning "Platform does not support debug break"
        #define ENGINE_DEBUG_BREAK()
    #endif

    // Enable asserts when debugging is enabled
    #define ENGINE_ENABLE_ASSERTS

#else
    #define ENGINE_DEBUG_BREAK()
#endif

#ifdef ENGINE_ENABLE_ASSERTS

// TODO: Add compiler (MSVC, GCC, GXX, Clang, etc.) macros like ENGINE_COMPILE_GCC
// TODO: Use compiler macros to handle __VA_ARGS__ trailing comma (0 arguments) issue for gcc (__VA_OPT__(,)?)

// TODO: Clean up assert implementation
// TODO: Add macros for handling checks at runtime without crashing, but while still logging and debugging

#define ENGINE_INTERNAL_ASSERT_IMPL(condition, msg, ...) { if (!(condition)) { ENGINE_DEBUG_ERROR(msg, __VA_ARGS__); ENGINE_DEBUG_BREAK(); } }
#define ENGINE_INTERNAL_ASSERT_W_MSG(condition, ...) ENGINE_INTERNAL_ASSERT_IMPL(condition, "Assertion failed: {0}", __VA_ARGS__)
#define ENGINE_INTERNAL_ASSERT_NO_MSG(condition) ENGINE_INTERNAL_ASSERT_IMPL(condition, "Assertion '{0}' failed at {1} line {2}", STR(condition), std::filesystem::path(__FILE__).filename().string(), __LINE__)
#define ENGINE_GET_ASSERT_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ENGINE_GET_ASSERT_MACRO(...) EXPAND(ENGINE_GET_ASSERT_MACRO_NAME(__VA_ARGS__, ENGINE_INTERNAL_ASSERT_W_MSG, ENGINE_INTERNAL_ASSERT_NO_MSG))

/** Debug assertion with an optional message. */
#define ENGINE_ASSERT(condition, ...) EXPAND(ENGINE_GET_ASSERT_MACRO((condition), __VA_ARGS__))((condition), __VA_ARGS__)
#else
/** Debug assertion with an optional message. */
#define ENGINE_ASSERT(condition, ...)
#endif

#endif