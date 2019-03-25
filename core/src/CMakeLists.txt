# Core Source

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing src CMakeLists.txt")

set(PROJECT_SRC
    Log.cpp
    Program.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/core/include)

add_library(${PROJECT_NAME}-core SHARED ${PROJECT_SRC})
#set_target_properties(${PROJECT_NAME}-core PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME}-core PUBLIC ${PROJECT_SOURCE_DIR}/core/include)

target_compile_definitions(${PROJECT_NAME}-core PRIVATE ENGINE_EXPORT=1)