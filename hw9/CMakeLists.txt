cmake_minimum_required(VERSION 3.15)
project(hw9)

set(CMAKE_C_STANDARD 11)

include_directories(../nrc/include)

add_executable(hw9
        main.c
        ../nrc/src/nrutil.c
        ../nrc/src/gaussj.c)