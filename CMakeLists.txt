cmake_minimum_required(VERSION 3.24)
project(cdata_structures C)

set(CMAKE_C_STANDARD 23)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_compile_options(-g -Wall -lm -ldl -fPIC -rdynamic)
add_library(cdata_structures SHARED ${sources})

add_subdirectory(tests)
