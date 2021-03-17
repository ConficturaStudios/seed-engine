### Copyright (c) 2021 Confictura Studios. All rights reserved.
### You may use, distribute, and modify this code under
### the terms of the MIT license.
### 
### This code is distributed as part of the Seed Engine project.
### 
### For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE

# Builds module into a shared library

cmake_minimum_required(VERSION 3.0)

message("Building Runtime module EventCore...")

set(LIBRARY_NAME RuntimeEventCore)
set(LIBRARY_NAME_UPPER RUNTIME_EVENT_CORE)

set(${LIBRARY_NAME_UPPER}_SRC
	${CMAKE_CURRENT_LIST_DIR}/Private/EventDispatcher.cpp
	${CMAKE_CURRENT_LIST_DIR}/Private/MouseEvent.cpp
)

set(${LIBRARY_NAME_UPPER}_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/Public/ClientEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/ControllerAxisEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/ControllerButtonEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/ControllerEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EngineEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EngineGameLoadEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EnginePostRenderEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EnginePreRenderEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EngineRenderEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EngineTickEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/Event.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EventCore.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EventCoreAPI.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/EventDispatcher.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/KeyboardEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/MouseButtonEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/MouseEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/MouseMovedEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/MouseScrolledEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/PeripheralEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/SystemEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowCloseEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowContentScaleEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowCreatedEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowFocusEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowMaximizeEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowMinimizeEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowPositionEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowRefreshEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowResizeEvent.hpp
	${CMAKE_CURRENT_LIST_DIR}/Public/WindowUpdateEvent.hpp
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
    add_library(${LIBRARY_NAME} INTERFACE)

    set(LIBRARY_SCOPE INTERFACE)

    target_include_directories(${LIBRARY_NAME}
        ${LIBRARY_SCOPE} ${CMAKE_CURRENT_LIST_DIR}/Public)
endif()

get_target_property(${LIBRARY_NAME_UPPER}_TYPE ${LIBRARY_NAME} TYPE)
message(STATUS "Built Runtime module EventCore as ${${LIBRARY_NAME_UPPER}_TYPE}")

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

add_dependencies(${LIBRARY_NAME} RuntimeInput)
target_link_libraries(${LIBRARY_NAME} ${LIBRARY_SCOPE} RuntimeInput)




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
        message(STATUS "Adding module EventCore to test suite")

        file(GLOB_RECURSE ${LIBRARY_NAME_UPPER}_TEST_SRC
            ${CMAKE_CURRENT_LIST_DIR}
            ${CMAKE_CURRENT_LIST_DIR}/Test/*.cpp)
            
        set(RUNTIME_TEST_SRC_FILES ${RUNTIME_TEST_SRC_FILES} ${${LIBRARY_NAME_UPPER}_TEST_SRC} PARENT_SCOPE)
        # TODO: Handle case where module has only empty cpp source files (no symbols)
        set(RUNTIME_TEST_LIBRARIES ${RUNTIME_TEST_LIBRARIES} ${LIBRARY_NAME} PARENT_SCOPE)

        set(RUNTIME_TEST_INCLUDES ${RUNTIME_TEST_INCLUDES} ${CMAKE_CURRENT_LIST_DIR}/Public PARENT_SCOPE)
        
    endif()
endif(BUILD_TESTS)