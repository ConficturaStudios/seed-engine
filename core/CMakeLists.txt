# Core

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Core CMakeLists.txt")

#include_directories(${PROJECT_SOURCE_DIR}/extern/assimp/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glm)
include_directories(${PROJECT_SOURCE_DIR}/extern/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/stb)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(src)

if(PACKAGE_TESTS)

    set(CORE_TEST_NAME ${CORE_PROJECT_NAME}-tests)
    
    file(GLOB_RECURSE CORE_TEST_SRC_FILES RELATIVE
        ${CMAKE_CURRENT_LIST_DIR}
        test/*.cpp)
    message(STATUS "Test case source files: " ${CORE_TEST_SRC_FILES})
    
    add_executable(${CORE_TEST_NAME} ${CORE_TEST_SRC_FILES})
    target_link_libraries(${CORE_TEST_NAME} google-test)
    target_link_libraries(${CORE_TEST_NAME} ${CORE_PROJECT_NAME})
    
    add_dependencies(${CORE_TEST_NAME} ${CORE_PROJECT_NAME})
    add_subdirectory(test)

endif(PACKAGE_TESTS)

message(STATUS "Build mode: " ${CMAKE_BUILD_TYPE})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_COMPILE_DEBUG=1)
    message(STATUS "Enabled Debug options")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")



set(GRAPHICS_API "OPENGL" CACHE STRING "The graphics API to build with")

if (GRAPHICS_API STREQUAL "OPENGL")
    message(STATUS "Building with OpenGL...")
    target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_GRAPHICS_API=1)
elseif (GRAPHICS_API STREQUAL "VULKAN")
    message(FATAL_ERROR "The program does not yet support vulkan.")
    message(STATUS "Building with Vulkan...")
    target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_GRAPHICS_API=2)
elseif (GRAPHICS_API STREQUAL "DIRECTX")
    if (WIN32)
        message(STATUS "Building with DirectX...")
        target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_GRAPHICS_API=3)
    else()
        message(FATAL_ERROR "The program cannot build with DirectX on a non-Windows platform.")
    endif (WIN32)
elseif (GRAPHICS_API STREQUAL "METAL")
    if (APPLE)
        message(STATUS "Building with Metal...")
        target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_GRAPHICS_API=4)
    else()
        message(FATAL_ERROR "The program cannot build with DirectX on a non-Apple platform.")
    endif (APPLE)
else()
    target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_GRAPHICS_API=-1)
endif ()