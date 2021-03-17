#Runtime domain

cmake_minimum_required(VERSION 3.0)

message("Building Runtime modules")

get_subdirectories(SUB_DIRS ${CMAKE_CURRENT_LIST_DIR})

set(RUNTIME_TEST_SRC_FILES CACHE INTERNAL "")
set(RUNTIME_TEST_LIBRARIES CACHE INTERNAL "")
set(RUNTIME_TEST_INCLUDES CACHE INTERNAL "")

foreach(dir ${SUB_DIRS})
    add_subdirectory(${dir})
endforeach()

if(BUILD_TESTS AND RUNTIME_TEST_SRC_FILES)
    message("Building Runtime tests")
    set(RUNTIME_TEST_SUITE ${RUNTIME_NAME}Tests)
    add_executable(${RUNTIME_TEST_SUITE} ${RUNTIME_TEST_SRC_FILES})

    target_link_libraries(${RUNTIME_TEST_SUITE} GoogleTest)

    if (RUNTIME_TEST_LIBRARIES)
        target_link_libraries(${RUNTIME_TEST_SUITE} ${RUNTIME_TEST_LIBRARIES})
        add_dependencies(${RUNTIME_TEST_SUITE} ${RUNTIME_TEST_LIBRARIES})
    endif()

    target_include_directories(${RUNTIME_TEST_SUITE} PUBLIC ${RUNTIME_TEST_INCLUDES})

endif()