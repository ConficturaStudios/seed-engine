# Source CMakeLists.txt

cmake_minimum_required(VERSION 3.0)

# Add All Domains

# External Dependencies
add_subdirectory(Extern)

# Runtime Modules
add_subdirectory(Runtime)

# Editor Modules
if (BUILD_EDITOR)
    add_subdirectory(Editor)
endif(BUILD_EDITOR)

# Developer/Experimental Modules
if(BUILD_DEV)
    add_subdirectory(Dev)
endif(BUILD_DEV)

# Documentation
if (DOXYGEN_FOUND AND BUILD_DOCS)
    add_subdirectory(Docs)
endif()

# Handle creating executables for test suites