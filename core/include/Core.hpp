#ifndef SEEDENGINE_INCLUDE_CORE_H_
#define SEEDENGINE_INCLUDE_CORE_H_

#define SEEDENGINE_VERSION_MAJOR 0
#define SEEDENGINE_VERSION_MINOR 0
#define SEEDENGINE_VERSION_PATCH 1

#ifdef ENGINE_COMPILE_DEBUG
    #define D3DCOMPILE_DEBUG 1
#endif

#define ENGINE_GRAPHICS_OPGL 1
#define ENGINE_GRAPHICS_VLKN 2
#define ENGINE_GRAPHICS_D3DX 3
#define ENGINE_GRAPHICS_METL 4

#if ENGINE_GRAPHICS_API == -1
    #error Graphics API not defined.
#endif

// Cross Platform Libraries

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


// Platform specific

#if defined(_WIN32)
// Windows Preprocessor Definitions

    /*#ifndef ENGINE_API
        #define ENGINE_DLL __declspec(dllimport)
    #else
        #define ENGINE_DLL __declspec(dllexport)
    #endif*/

    #include <winsock2.h>

    #include <windows.h>
    #include <windowsx.h>

    //Check for DirectX
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_D3DX
        #include <d2d1.h> // Direct2D
        #include <d3d11.h> // Direct3D 11
        #include <d3d12.h> // Direct3D 12

        // include the Direct3D Library files
        #pragma comment (lib, "d2d1.lib")
        #pragma comment (lib, "d3d12.lib")
        #pragma comment (lib, "d3d11.lib")
    #endif

    #if defined(_WIN64)
    // x64 Windows Specific Preprocessor Definitions

    #else
    // x86 Windows Specific Preprocessor Definitions
    
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
// Apple Preprocessor Definitions
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
    // iOS Simulator

    #elif TARGET_OS_IPHONE
    // iOS

    #elif TARGET_OS_MAC
    // Mac OS

    #else
    #   error "Unkown Apple Platform"
    #endif
#elif defined(__ANDROID__)
// Android Preprocessor Definitions
    //Check for OpenGL
    #if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
        #define GLFW_INCLUDE_ES2
        #define GLFW_INCLUDE_ES32
    #endif

#elif defined(__linux__)
// Linux Preprocessor Definitions

#elif defined(__gnu_linux__)
// GNU Linux Preprocessor Definitions

#elif defined(unix) || defined(__unix) || defined(__unix__)
// Unix Preprocessor Definitions

#else
// No OS Specific Predefinied Macros Found, unsupported OS
#   error "Unknown Platform"

#endif

//Check for Vulkan
#if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_VLKN
    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>
#endif

//Check for OpenGL
#if ENGINE_GRAPHICS_API == ENGINE_GRAPHICS_OPGL
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
#endif

// STL Includes:

#include <iostream>
#include <fstream>
#include <stdio.h>

#ifndef _WIN32
    #include <arpa/inet.h>

    inline float ntohf(uint32_t net) {
        union {
            uint32_t bytes;
            float value;
        } pair;
        pair.bytes = ntohl(net);
        return pair.value;
    }

    inline uint32_t htonf(float host) {
        union {
            uint32_t bytes;
            float value;
        } pair;
        pair.value = host;
        return htonl(pair.bytes);
    }

#endif

#include <string>
#include <sstream>

#include <stdexcept>
#include <cstdarg>

#include <thread>
#include <chrono>
#include <memory>
#include <mutex>

#include <array>
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <initializer_list>

#include <regex>
#include <functional>
#include <algorithm>

#include <exception>
#include <type_traits>

// Namespace using directives

using string = ::std::string;

// Custom Macros:

/**
 * @brief Creates an absolute file path within the engine core folder.
 */
#define CORE_PATH(x) string(ENGINE_CORE_PATH "/" x)

/**
 * @brief Creates a bitwise flag.
 */
#define FLAG(x) (1 << x)
/**
 * @brief Checks if the option has the flag enabled.
 */
#define CHECK_FLAG(option, flag) (option & flag) == flag

// STL Extensions

namespace std {

#ifndef _WIN32

    template<typename T, typename... Args>
    inline unique_ptr<T> make_unique(Args&& ... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

#endif

}

// Compile Time Traits

template < template <typename...> class Base, typename Derived>
struct is_base_of_t_impl
{
    template<typename... T>
    static constexpr std::true_type  check(const Base<T...>*);
    static constexpr std::false_type check(...);
    using type = decltype(check(std::declval<Derived*>()));
};

template < template <typename...> class Base, typename Derived>
using is_base_of_t = typename is_base_of_t_impl<Base, Derived>::type;

// Engine specific includes:

#include "Log.hpp"
#include "Property.hpp"

#include "Random.hpp"
#include "Math.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Color.hpp"
#include "Noise.hpp"


#endif