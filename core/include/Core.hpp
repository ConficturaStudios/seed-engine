#ifndef SEEDENGINE_INCLUDE_CORE_H_
#define SEEDENGINE_INCLUDE_CORE_H_

#define SEEDENGINE_VERSION_MAJOR 0
#define SEEDENGINE_VERSION_MINOR 0
#define SEEDENGINE_VERSION_PATCH 1

#if defined(_WIN32)
// Windows Preprocessor Definitions

    #ifndef ENGINE_EXPORT
        #define ENGINE_DLL __declspec(dllimport)
    #else
        #define ENGINE_DLL __declspec(dllexport)
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

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <vector>
#include <iterator>
#include <regex>

#endif