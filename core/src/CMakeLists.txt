# Core Source

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing src CMakeLists.txt")

set(PROJECT_SRC
    Event.cpp
    Image.cpp
    Log.cpp
    Mesh.cpp
    Parser.cpp
    Program.cpp
    Renderer.cpp
    Time.cpp
    Window.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/core/include)

add_library(${CORE_PROJECT_NAME} STATIC ${PROJECT_SRC})
target_include_directories(${CORE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/core/include)

target_compile_definitions(${CORE_PROJECT_NAME} PRIVATE ENGINE_EXPORT=1)
target_compile_definitions(${CORE_PROJECT_NAME} PUBLIC ENGINE_CORE_PATH="${PROJECT_SOURCE_DIR}/core")

target_link_libraries(${CORE_PROJECT_NAME} glad)
target_link_libraries(${CORE_PROJECT_NAME} glfw ${GLFW_LIBRARIES})