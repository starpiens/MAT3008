cmake_minimum_required(VERSION 3.15)
project(hw6 C)

set(CMAKE_C_STANDARD 99)

include_directories(../nrc/include)

add_executable(hw6
        main.c
        ../nrc/src/ran0.c
        ../nrc/src/gasdev.c)