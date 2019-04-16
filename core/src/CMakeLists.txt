# Core Source

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing src CMakeLists.txt")

set(PROJECT_SRC
    Event.cpp
    Log.cpp
    Parser.cpp
    Program.cpp
    Time.cpp
    Window.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/core/include)

add_library(${PROJECT_NAME}-core STATIC ${PROJECT_SRC})
#set_target_properties(${PROJECT_NAME}-core PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME}-core PUBLIC ${PROJECT_SOURCE_DIR}/core/include)

target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_EXPORT=1)
target_compile_definitions(${PROJECT_NAME}-core PUBLIC ENGINE_CORE_PATH="${PROJECT_SOURCE_DIR}/core")

target_link_libraries(${PROJECT_NAME}-core glad)
target_link_libraries(${PROJECT_NAME}-core glfw ${GLFW_LIBRARIES})