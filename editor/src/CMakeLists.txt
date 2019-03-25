# Editor source

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Editor src CMakeLists.txt")

set(PROJECT_SRC
    SampleApp.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/core/include)
include_directories(${PROJECT_SOURCE_DIR}/editor/include)

add_executable(${PROJECT_NAME}-editor ${PROJECT_SRC})

target_include_directories(${PROJECT_NAME}-editor PRIVATE ${PROJECT_SOURCE_DIR}/editor/include)

target_link_libraries(${PROJECT_NAME}-editor ${PROJECT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/seed-engine-core.lib)