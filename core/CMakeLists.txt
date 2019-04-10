# Core

cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing Core CMakeLists.txt")

include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/extern/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glfw/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
add_subdirectory(src)

if(PACKAGE_TESTS)

    set(CORE_TEST_NAME ${PROJECT_NAME}-core-test)

    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include)
    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googlemock/include)
    
    file(GLOB_RECURSE CORE_TEST_SRC_FILES RELATIVE
        ${CMAKE_CURRENT_LIST_DIR}
        test/*.cpp)
    message(STATUS "Test case source files: " ${CORE_TEST_SRC_FILES})
    
    add_executable(${CORE_TEST_NAME} ${CORE_TEST_SRC_FILES})
    target_link_libraries(${CORE_TEST_NAME} google-test)
    target_link_libraries(${CORE_TEST_NAME} ${PROJECT_NAME}-core)
    
    add_dependencies(${CORE_TEST_NAME} ${PROJECT_NAME}-core)
    add_subdirectory(test)

endif(PACKAGE_TESTS)