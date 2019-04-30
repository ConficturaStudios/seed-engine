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
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/glfw)

#set(ASSIMP_BUILD_BOOST_WORKAROUND   ON CACHE BOOL "")
#set(BUILD_SHARED_LIBS               OFF CACHE BOOL "")
#set(ASSIMP_OPT_BUILD_PACKAGES       OFF CACHE BOOL "")
#set(ASSIMP_BUILD_ASSIMP_TOOLS       OFF CACHE BOOL "")
#set(ASSIMP_BUILD_TESTS              OFF CACHE BOOL "")
#set(ASSIMP_BUILD_SAMPLES            OFF CACHE BOOL "")
#set(ASSIMP_BUILD_ZLIB               OFF CACHE BOOL "")
#add_subdirectory(${PROJECT_SOURCE_DIR}/extern/assimp)

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