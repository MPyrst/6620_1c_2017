cmake_minimum_required(VERSION 3.5)
project(6620_1c_2017)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

set(SOURCE_FILES
    archivos/alice.txt
    archivos/beowulf.txt
    archivos/cyclopedia.txt
    archivos/elquijote.txt
    lorem
    main.c
    README.md
    Sorter.sh
    sorters.c
    sorters.h
    tp0.pdf
    "Usar Gxemul")

add_executable(6620_1c_2017 ${SOURCE_FILES})