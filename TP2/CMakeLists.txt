cmake_minimum_required(VERSION 3.5)

# Set project name and path
set(PROJECT_NAME "tp2")
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -Wno-unused-variable -O0")

include_directories(.)

set(SOURCE_FILES
        main.cpp
        moduleExecutor.cpp
        parser.cpp)

add_executable(tp2 ${SOURCE_FILES})

include_directories(modules/blockSize)
add_subdirectory(modules/blockSize)

include_directories(modules/cacheSize)
add_subdirectory(modules/cacheSize)

include_directories(modules/cacheAssociativity)
add_subdirectory(modules/cacheAssociativity)
