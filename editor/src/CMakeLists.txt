# Editor source

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Editor src CMakeLists.txt")

set(PROJECT_SRC
    SampleApp.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/extern/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/core/include)
include_directories(${PROJECT_SOURCE_DIR}/editor/include)

add_executable(${EDITOR_PROJECT_NAME} ${PROJECT_SRC})

target_include_directories(${EDITOR_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/editor/include)


target_link_libraries(${EDITOR_PROJECT_NAME} ${CORE_PROJECT_NAME})

target_link_libraries(${EDITOR_PROJECT_NAME} glad)
target_link_libraries(${EDITOR_PROJECT_NAME} glfw ${GLFW_LIBRARIES})