### Copyright (c) 2021 Confictura Studios. All rights reserved.
### You may use, distribute, and modify this code under
### the terms of the MIT license.
### 
### This code is distributed as part of the Seed Engine project.
### 
### For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE

# Builds module into a shared library

cmake_minimum_required(VERSION 3.0)

message(STATUS "Building Runtime module Graphics")

set(LIBRARY_NAME RuntimeGraphics)
set(LIBRARY_NAME_UPPER RUNTIME_GRAPHICS)

set(${LIBRARY_NAME_UPPER}_SRC
	${CMAKE_CURRENT_LIST_DIR}/Private/BufferObject.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Color.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/DepthBuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Framebuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/GBuffer.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Image.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Mesh.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/DirectX/DirectXShader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/DirectX/DirectXTexture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Metal/MetalShader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Metal/MetalTexture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/OpenGL/OpenGLShader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/OpenGL/OpenGLTexture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Vulkan/VulkanShader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/Vulkan/VulkanTexture.cpp
)

set(${LIBRARY_NAME_UPPER}_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/Public/BufferObject.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Color.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/DepthBuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Framebuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/GBuffer.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Graphics.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/GraphicsAPI.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Image.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Mesh.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Shader.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Texture.hpp
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
    message(STATUS "Building Runtime module Graphics as INTERFACE Library")
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

add_dependencies(${LIBRARY_NAME} RuntimeMath)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeMath)
add_dependencies(${LIBRARY_NAME} RuntimeCommon)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeCommon)


target_include_directories(${LIBRARY_NAME}
    ${LIBRARY_SCOPE} ${PROJECT_SOURCE_DIR}/Source/Extern/glm
    ${LIBRARY_SCOPE} ${PROJECT_SOURCE_DIR}/Source/Extern/glad/include
    ${LIBRARY_SCOPE} ${PROJECT_SOURCE_DIR}/Source/Extern/glfw/include
    ${LIBRARY_SCOPE} ${PROJECT_SOURCE_DIR}/Source/Extern/stb)

target_link_libraries(${LIBRARY_NAME}
    ${LIBRARY_SCOPE} glad
    ${LIBRARY_SCOPE} glfw ${GLFW_LIBRARIES}
)


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
        message(STATUS "Adding module Graphics to test suite")

        file(GLOB_RECURSE ${LIBRARY_NAME_UPPER}_TEST_SRC
            ${CMAKE_CURRENT_LIST_DIR}
            ${CMAKE_CURRENT_LIST_DIR}/Test/*.cpp)
            
        set(RUNTIME_TEST_SRC_FILES ${RUNTIME_TEST_SRC_FILES} ${${LIBRARY_NAME_UPPER}_TEST_SRC} PARENT_SCOPE)
        set(RUNTIME_TEST_LIBRARIES ${RUNTIME_TEST_LIBRARIES} ${LIBRARY_NAME} PARENT_SCOPE)
        set(RUNTIME_TEST_INCLUDES ${RUNTIME_TEST_INCLUDES} ${CMAKE_CURRENT_LIST_DIR}/Public PARENT_SCOPE)
        
    endif()
endif(BUILD_TESTS)