# Editor

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Editor CMakeLists.txt")

include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(src)