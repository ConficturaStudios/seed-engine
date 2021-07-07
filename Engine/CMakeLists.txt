# Root CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

# Project Info

set(ENGINE_NAME SeedEngine)
set(ENGINE_NAME_PROPER "Seed Engine")

set(ENGINE_VERSION_MAJOR 0)
set(ENGINE_VERSION_MINOR 1)
set(ENGINE_VERSION_PATCH 0)
set(ENGINE_VERSION_EXTRA "")

set(ENGINE_VERSION ${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}.${ENGINE_VERSION_PATCH})
set(ENGINE_VERSION_FULL "${ENGINE_VERSION}${ENGINE_VERSION_EXTRA}")

set(ENGINE_NAME_FULL "${ENGINE_NAME_PROPER} ${ENGINE_VERSION_FULL}")

# Standard Includes

include(CMake/Standard.cmake)

# Project Setup

message(STATUS "Building ${ENGINE_NAME_FULL}")

project(${ENGINE_NAME} VERSION ${ENGINE_VERSION})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options

# Feature Switches
option(BUILD_EDITOR "Build editor features" ON)
option(BUILD_DEV "Build developer (experimental) features" OFF)
# Documentation switch
option(BUILD_DOCS "Build documentation" OFF)
# Testing and coverage switches
option(BUILD_TESTS "Build all tests" OFF)
option(ENABLE_COVERAGE "Enable coverage report generation" OFF)

# Compiler flags

if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS --coverage)
endif()

# Architecture Specific Configuration

if (NOT ${CMAKE_GENERATOR_PLATFORM} STREQUAL "x64")
    message(WARNING "Editor builds only support x64 platform architectures, disabling editor modules for this build")
    set(BUILD_EDITOR OFF)
endif()

# Compiler Specific Configuration

if (MSVC)
    # Force multithreading; Disabled due to poor performance with -j 16 option
    # add_definitions(/MP16)
    # Suppress suggestions/warnings to use Microsoft secure functions like fopen_s
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Graphics options

option(ENABLE_OPENGL "Enable Open GL features and rendering in this build" ON)
option(ENABLE_DIRECTX "[Unavailable] Enable Direct X features and rendering in this build. Windows only." OFF)
option(ENABLE_VULKAN "[Unavailable] Enable Vulkan features and rendering in this build" OFF)
option(ENABLE_METAL "[Unavailable] Enable Metal features and rendering in this build. MacOS and iOS only." OFF)

set(GRAPHICS_OPENGL_ENABLED 0)
set(GRAPHICS_DIRECTX_ENABLED 0)
set(GRAPHICS_VULKAN_ENABLED 0)
set(GRAPHICS_METAL_ENABLED 0)

# Force flags to only handle implemented graphics options

set(ENABLE_DIRECTX OFF CACHE BOOL "[Unavailable] Enable Direct X features and rendering in this build. Windows only." FORCE)
set(ENABLE_VULKAN OFF CACHE BOOL "[Unavailable] Enable Vulkan features and rendering in this build" FORCE)
set(ENABLE_METAL OFF CACHE BOOL "[Unavailable] Enable Metal features and rendering in this build. MacOS and iOS only." FORCE)

# Check OS compatibility and set flags

if (ENABLE_DIRECTX)
    if (WIN32)
        message(STATUS "Direct X rendering enabled")
        set(GRAPHICS_DIRECTX_ENABLED 1)
    else()
        message(WARNING "Direct X is only available on Microsoft platforms")
        set(ENABLE_DIRECTX OFF CACHE BOOL "Enable Direct X features and rendering in this build. Windows only." FORCE)
    endif()
endif()
if (ENABLE_VULKAN)
    message(STATUS "Vulkan rendering enabled")
    set(GRAPHICS_VULKAN_ENABLED 1)
endif()
if (ENABLE_METAL)
    if (APPLE)
        message(STATUS "Metal rendering enabled")
        set(GRAPHICS_METAL_ENABLED 1)
    else()
        message(WARNING "Metal is only available on Apple platforms")
        set(ENABLE_METAL OFF CACHE BOOL "Enable Metal features and rendering in this build. MacOS and iOS only." FORCE)
    endif()
endif()

# Fallback to Open GL if other APIs are not available

if ((NOT ENABLE_OPENGL) AND (NOT ENABLE_DIRECTX) AND (NOT ENABLE_VULKAN) AND (NOT ENABLE_METAL))
    message(WARNING "No valid graphics api selected. Defaulting to Open GL.")
    set(ENABLE_OPENGL ON CACHE BOOL "Enable Open GL features and rendering in this build" FORCE)
endif()

if (ENABLE_OPENGL)
    message(STATUS "OpenGL rendering enabled")
    set(GRAPHICS_OPENGL_ENABLED 1)
endif()

# Documentation

if(BUILD_DOCS)

    message(STATUS "Documentation will build")
    #set(DOXYGEN_SKIP_DOT TRUE)
    #find_package(Doxygen 1.8)
    #if(DOXYGEN_FOUND)
        #add_subdirectory(Docs)
    #endif(DOXYGEN_FOUND)

endif(BUILD_DOCS)

# Testing

if(BUILD_TESTS)
    message(STATUS "Tests will build")
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    include(CMake/GoogleTest.cmake)

    find_package (Threads REQUIRED)

endif(BUILD_TESTS)

# Output Info

set(RUNTIME_NAME ${ENGINE_NAME}-${ENGINE_VERSION})
set(EDITOR_NAME ${ENGINE_NAME}-${ENGINE_VERSION}Editor)

# Engine Source
add_subdirectory(Source)