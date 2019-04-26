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

option(PACKAGE_TESTS "Build all tests" ON)
if(PACKAGE_TESTS)
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    include(cmake/google-test.cmake)

    find_package (Threads)

endif(PACKAGE_TESTS)

set (CORE_PROJECT_NAME ${PROJECT_NAME}-core)
set (EDITOR_PROJECT_NAME ${PROJECT_NAME}-editor)

add_subdirectory(core)

add_subdirectory(editor)