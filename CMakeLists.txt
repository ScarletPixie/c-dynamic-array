cmake_minimum_required(VERSION 3.10)
project(c-dynamic-arrays)

set(SOURCES
    array.c
    sort/sort.c
)

add_library(array STATIC ${SOURCES})
