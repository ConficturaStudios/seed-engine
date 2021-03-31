#External Modules

cmake_minimum_required(VERSION 3.0)

message(STATUS "Building external modules")

add_subdirectory(glad)
option(GLFW_BUILD_EXAMPLES "Disable GLFW examples" OFF)
option(GLFW_BUILD_TESTS "Disable GLFW tests" OFF)
option(BUILD_SHARED_LIBS "Disable shared library output for GLFW" OFF)
add_subdirectory(glfw)

#set(ASSIMP_BUILD_BOOST_WORKAROUND   ON CACHE BOOL "")
#set(BUILD_SHARED_LIBS               OFF CACHE BOOL "")
#set(ASSIMP_OPT_BUILD_PACKAGES       OFF CACHE BOOL "")
#set(ASSIMP_BUILD_ASSIMP_TOOLS       OFF CACHE BOOL "")
#set(ASSIMP_BUILD_TESTS              OFF CACHE BOOL "")
#set(ASSIMP_BUILD_SAMPLES            OFF CACHE BOOL "")
#set(ASSIMP_BUILD_ZLIB               OFF CACHE BOOL "")
#add_subdirectory(assimp)