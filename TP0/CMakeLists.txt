cmake_minimum_required(VERSION 3.5)
project(tp0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

set(SOURCE_FILES
        main.c
        sorters.c)

set(HEADER_FILES sorters.h)

add_executable(tp0 ${SOURCE_FILES})