cmake_minimum_required(VERSION 3.14)
project(hw3 C)

set(CMAKE_C_STANDARD 11)

include_directories(nr)

add_executable(
        hw3
        main.c
        nr/rtbis.c
        nr/rtflsp.c
        nr/rtsec.c
        nr/rtnewt.c
        nr/rtsafe.c
        nr/bessj0.c
        nr/nrerror.c
        nr/zbrak.c nr/bessj1.c)