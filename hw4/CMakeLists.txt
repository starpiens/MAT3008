cmake_minimum_required(VERSION 3.14)
project(hw4 C)

set(CMAKE_C_STANDARD 11)
file(GLOB_RECURSE NR "../nr/src/*.c")

include_directories(../nr/include)

add_executable(hw4 main.c ${NR} problem1.c problem2.c run_funcs.c problem3.c)