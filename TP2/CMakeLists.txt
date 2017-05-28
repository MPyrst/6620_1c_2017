cmake_minimum_required(VERSION 3.5)

# Set project name and path
set(PROJECT_NAME "tp2")
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

include_directories(src)
add_subdirectory(src)

