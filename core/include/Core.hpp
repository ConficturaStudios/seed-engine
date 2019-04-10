#ifndef SEEDENGINE_INCLUDE_CORE_H_
#define SEEDENGINE_INCLUDE_CORE_H_

#define SEEDENGINE_VERSION_MAJOR 0
#define SEEDENGINE_VERSION_MINOR 0
#define SEEDENGINE_VERSION_PATCH 1

#ifdef ENGINE_COMPILE_DEBUG
    #define D3DCOMPILE_DEBUG 1
#endif

// Cross Platform Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if defined(_WIN32)
// Windows Preprocessor Definitions

    /*#ifndef ENGINE_API
        #define ENGINE_DLL __declspec(dllimport)
    #else
        #define ENGINE_DLL __declspec(dllexport)
    #endif*/

    #include <windows.h>
    #include <windowsx.h>
    #include <d2d1.h> // Direct2D
    #include <d3d11.h> // Direct3D 11
    #include <d3d12.h> // Direct3D 12

    // include the Direct3D Library files
    #pragma comment (lib, "d2d1.lib")
    #pragma comment (lib, "d3d12.lib")
    #pragma comment (lib, "d3d11.lib")

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

// STL Includes:

#include <iostream>
#include <fstream>

#include <string>

#include <thread>
#include <chrono>
#include <memory>

#include <queue>
#include <map>
#include <vector>
#include <iterator>

#include <regex>
#include <functional>
#include <algorithm>

// Custom Macros:

#define FLAG(x) (1 << x)

// Engine specific includes:

#include "Log.hpp"

#endif