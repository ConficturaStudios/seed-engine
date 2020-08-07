### Copyright (c) 2020 Confictura Studios. All rights reserved.
### You may use, distribute, and modify this code under
### the terms of the MIT license.
### 
### This code is distributed as part of the Seed Engine project.
### 
### For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE

# Builds module into a shared library

cmake_minimum_required(VERSION 3.0)

message(STATUS "Building Runtime module Renderer")

set(LIBRARY_NAME RuntimeRenderer)
set(LIBRARY_NAME_UPPER RUNTIME_RENDERER)

set(${LIBRARY_NAME_UPPER}_SRC
	${CMAKE_CURRENT_LIST_DIR}/Private/Window.cpp
)

set(${LIBRARY_NAME_UPPER}_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/Public/Renderer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/RendererAPI.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Window.hpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/Public)

set(LIBRARY_SCOPE PUBLIC)

if(${LIBRARY_NAME_UPPER}_SRC)
    add_library(${LIBRARY_NAME} SHARED ${${LIBRARY_NAME_UPPER}_SRC})

    target_include_directories(${LIBRARY_NAME}
        ${LIBRARY_SCOPE} ${CMAKE_CURRENT_LIST_DIR}/Public
        PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Private)

    target_compile_definitions(${LIBRARY_NAME}
        PRIVATE BUILD_SHARED_LIBS=1
        PRIVATE ${LIBRARY_NAME_UPPER}_EXPORT=1)
else()
    message(STATUS "Building Runtime module Renderer as INTERFACE Library")
    add_library(${LIBRARY_NAME} INTERFACE)

    set(LIBRARY_SCOPE INTERFACE)

    target_include_directories(${LIBRARY_NAME}
        ${LIBRARY_SCOPE} ${CMAKE_CURRENT_LIST_DIR}/Public)
endif()

target_compile_definitions(${LIBRARY_NAME}
    ${LIBRARY_SCOPE} ENGINE_VERSION_MAJOR=${ENGINE_VERSION_MAJOR}
    ${LIBRARY_SCOPE} ENGINE_VERSION_MINOR=${ENGINE_VERSION_MINOR}
    ${LIBRARY_SCOPE} ENGINE_VERSION_PATCH=${ENGINE_VERSION_PATCH}
    ${LIBRARY_SCOPE} ENGINE_VERSION_EXTRA="${ENGINE_VERSION_EXTRA}"
    ${LIBRARY_SCOPE} ENGINE_GRAPHICS_OPENGL=${GRAPHICS_OPENGL_ENABLED}
    ${LIBRARY_SCOPE} ENGINE_GRAPHICS_DIRECTX=${GRAPHICS_DIRECTX_ENABLED}
    ${LIBRARY_SCOPE} ENGINE_GRAPHICS_VULKAN=${GRAPHICS_VULKAN_ENABLED}
    ${LIBRARY_SCOPE} ENGINE_GRAPHICS_METAL=${GRAPHICS_METAL_ENABLED})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${LIBRARY_NAME}
        ${LIBRARY_SCOPE} ENGINE_COMPILE_DEBUG=1)
endif()

add_dependencies(${LIBRARY_NAME} RuntimeGraphics)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeGraphics)
add_dependencies(${LIBRARY_NAME} RuntimeGameplayCore)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeGameplayCore)
add_dependencies(${LIBRARY_NAME} RuntimeMath)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeMath)
add_dependencies(${LIBRARY_NAME} RuntimeCommon)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeCommon)




# Install Library
install(TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/Lib
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/Lib
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/Bin)

# Install Library Headers
install(FILES ${${LIBRARY_NAME_UPPER}_HEADERS}
    DESTINATION ${PROJECT_SOURCE_DIR}/Lib/Include)

if(BUILD_TESTS)
    get_target_property(TARGET_TYPE ${LIBRARY_NAME} TYPE)
    if(NOT ${TARGET_TYPE} STREQUAL "EXECUTABLE")
        message(STATUS "Adding module Renderer to test suite")

        file(GLOB_RECURSE ${LIBRARY_NAME_UPPER}_TEST_SRC
            ${CMAKE_CURRENT_LIST_DIR}
            ${CMAKE_CURRENT_LIST_DIR}/Test/*.cpp)
            
        set(RUNTIME_TEST_SRC_FILES ${RUNTIME_TEST_SRC_FILES} ${${LIBRARY_NAME_UPPER}_TEST_SRC} PARENT_SCOPE)
        set(RUNTIME_TEST_LIBRARIES ${RUNTIME_TEST_LIBRARIES} ${LIBRARY_NAME} PARENT_SCOPE)
        set(RUNTIME_TEST_INCLUDES ${RUNTIME_TEST_INCLUDES} ${CMAKE_CURRENT_LIST_DIR}/Public PARENT_SCOPE)
        
    endif()
endif(BUILD_TESTS)