#External Modules

cmake_minimum_required(VERSION 3.0)

message(STATUS "Building external modules")

add_subdirectory(glad)
option(GLFW_BUILD_EXAMPLES "Disable GLFW examples" OFF)
option(GLFW_BUILD_TESTS "Disable GLFW tests" OFF)
option(BUILD_SHARED_LIBS "Disable shared library output for GLFW" OFF)
add_subdirectory(glfw)

if (BUILD_EDITOR)
    option(ASSIMP_BUILD_BOOST_WORKAROUND "" ON)
    option(BUILD_SHARED_LIBS "" OFF)
    option(ASSIMP_OPT_BUILD_PACKAGES "" OFF)
    option(ASSIMP_BUILD_ASSIMP_TOOLS "" OFF)
    option(ASSIMP_BUILD_TESTS "" OFF)
    option(ASSIMP_BUILD_DOCS "" OFF)
    option(ASSIMP_BUILD_SAMPLES "" OFF)
    option(ASSIMP_BUILD_ZLIB "" ON)
    option(ASSIMP_INSTALL "" OFF)
    add_subdirectory(assimp)
endif(BUILD_EDITOR)