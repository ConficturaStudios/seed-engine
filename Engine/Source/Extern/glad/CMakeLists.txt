cmake_minimum_required(VERSION 3.0)
project(GLAD)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)