cmake_minimum_required(VERSION 3.15)
project(hw7 C)

set(CMAKE_C_STANDARD 11)

include_directories(../nrc/include)

add_executable(hw7
        main.c
        ../nrc/src/nrutil.c
        ../nrc/src/jacobi.c
        ../nrc/src/eigsrt.c
        ../nrc/src/ran0.c)