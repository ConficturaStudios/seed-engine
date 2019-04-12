# Root

cmake_minimum_required(VERSION 3.0)
project(seed-engine VERSION 0.0.1)

message(STATUS "Processing Root CMakeLists.txt")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/glfw)

add_subdirectory(core)

option(CORE_BUILT "Core has been built" OFF)
if(CORE_BUILT)
    add_subdirectory(editor)
    #add_subdirectory(shell)
endif(CORE_BUILT)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_COMPILE_DEBUG=1)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

set(GRAPHICS_API "OPENGL" CACHE STRING "The graphics API to build with")

if (GRAPHICS_API STREQUAL "OPENGL")
    message(STATUS "Building with OpenGL...")
    target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_GRAPHICS_API=1)
elseif (GRAPHICS_API STREQUAL "VULKAN")
    message(FATAL_ERROR "The program does not yet support vulkan.")
    message(STATUS "Building with Vulkan...")
    target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_GRAPHICS_API=2)
elseif (GRAPHICS_API STREQUAL "D3DX")
    if (WIN32)
        message(STATUS "Building with DirectX...")
        target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_GRAPHICS_API=3)
    else()
        message(FATAL_ERROR "The program cannot build with DirectX on a non-Windows platform.")
    endif (WIN32)
elseif (GRAPHICS_API STREQUAL "METAL")
    if (APPLE)
        message(STATUS "Building with Metal...")
        target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_GRAPHICS_API=4)
    else()
        message(FATAL_ERROR "The program cannot build with DirectX on a non-Apple platform.")
    endif (APPLE)
else()
    target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_GRAPHICS_API=-1)
endif ()

option(PACKAGE_TESTS "Build all tests" ON)
if(PACKAGE_TESTS)
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    
    enable_testing()

endif(PACKAGE_TESTS)