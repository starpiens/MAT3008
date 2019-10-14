cmake_minimum_required(VERSION 3.14)
project(hw5 C)

set(CMAKE_C_STANDARD 11)
file(GLOB_RECURSE NR "../nr/src/*.c")

include_directories(../nr/include)

add_executable(hw5 ${NR} main.c)