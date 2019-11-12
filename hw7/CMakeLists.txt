cmake_minimum_required(VERSION 3.15)
project(hw7 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw7 main.c nrutil.c jacobi.c eigsrt.c ran0.c)