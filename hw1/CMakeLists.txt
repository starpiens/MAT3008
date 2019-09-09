cmake_minimum_required(VERSION 3.14)
project(hw1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hw1
        machar.c
        machar_double.c
        main.c)