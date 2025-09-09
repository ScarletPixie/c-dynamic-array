cmake_minimum_required(VERSION 3.10)
project(c-dynamic-arrays)

set(SOURCES
    array.c
    sort/sort.c
)

add_library(array STATIC ${SOURCES})
target_include_directories(array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(BUILD_TESTS "Build test binaries" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()