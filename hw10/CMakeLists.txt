cmake_minimum_required(VERSION 3.15)
project(hw10 C)

set(CMAKE_C_STANDARD 11)

include_directories(../nrc/include)

add_executable(hw10
        main.c
        ../nrc/src/mrqmin.c
        ../nrc/src/mrqcof.c
        ../nrc/src/nrutil.c
        ../nrc/src/gaussj.c
        ../nrc/src/covsrt.c)