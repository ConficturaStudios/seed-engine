# Root

cmake_minimum_required(VERSION 3.0)
project(seed-engine VERSION 0.0.1)

message(STATUS "Processing Root CMakeLists.txt")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(core)

option(CORE_BUILT "Core has been built" OFF)
if(CORE_BUILT)
    add_subdirectory(editor)
    #add_subdirectory(shell)
endif(CORE_BUILT)

option(PACKAGE_TESTS "Build all tests" ON)
if(PACKAGE_TESTS)
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")
    
    enable_testing()
    set(PROJECT_TEST_NAME ${PROJECT_NAME}_TEST)

    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googletest/include)
    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googletest/lib)
    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googlemock/include)
    include_directories(${PROJECT_SOURCE_DIR}/extern/googletest/googlemock/lib)
    
    file(GLOB_RECURSE TEST_SRC_FILES RELATIVE
        ${CMAKE_CURRENT_LIST_DIR}
        core/test/*.cpp)
    message(STATUS "Test case source files: " ${TEST_SRC_FILES})
    
    add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
    target_link_libraries(${PROJECT_TEST_NAME} google-test)
    target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME}-core)
    
    add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_NAME}-core)
    add_subdirectory(core/test)
endif(PACKAGE_TESTS)