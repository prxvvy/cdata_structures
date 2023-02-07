cmake_minimum_required(VERSION 3.24)
project(cdata_structures_tests C)

set(CMAKE_C_STANDARD 23)

file(GLOB LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)

add_executable(cdata_structures_tests  main.c)
target_include_directories(cdata_structures_tests  PUBLIC ${LIB_HEADERS})

target_link_directories(cdata_structures_tests  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(cdata_structures_tests cdata_structures)
