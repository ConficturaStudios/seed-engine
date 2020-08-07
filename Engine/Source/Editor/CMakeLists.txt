#Runtime domain

cmake_minimum_required(VERSION 3.0)

message(STATUS "Building Editor modules")

get_subdirectories(SUB_DIRS ${CMAKE_CURRENT_LIST_DIR})

set(EDITOR_TEST_SRC_FILES CACHE INTERNAL "")
set(EDITOR_TEST_LIBRARIES CACHE INTERNAL "")
set(EDITOR_TEST_INCLUDES CACHE INTERNAL "")

foreach(dir ${SUB_DIRS})
    add_subdirectory(${dir})
endforeach()

if(BUILD_TESTS AND EDITOR_TEST_LIBRARIES)
    message(STATUS "Building Editor tests")
    set(EDITOR_TEST_SUITE ${EDITOR_NAME}Tests)
    add_executable(${EDITOR_TEST_SUITE} ${EDITOR_TEST_SRC_FILES})

    target_link_libraries(${EDITOR_TEST_SUITE} GoogleTest)
    target_link_libraries(${EDITOR_TEST_SUITE} ${EDITOR_TEST_LIBRARIES})

    target_include_directories(${EDITOR_TEST_SUITE} PUBLIC ${EDITOR_TEST_INCLUDES})

    add_dependencies(${EDITOR_TEST_SUITE} ${EDITOR_TEST_LIBRARIES})
endif(BUILD_TESTS AND EDITOR_TEST_LIBRARIES)