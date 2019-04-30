# Editor

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Editor CMakeLists.txt")

#include_directories(${PROJECT_SOURCE_DIR}/extern/assimp/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/extern/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/stb)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(src)