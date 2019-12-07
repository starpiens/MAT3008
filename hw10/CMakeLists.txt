cmake_minimum_required(VERSION 3.15)
project(hw10 CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED PATHS "/usr/local/Cellar/opencv@3/3.4.5_6")

set(NRC_SRC_DIR ../nrc/src/)
add_executable(hw10
        main.cpp
        ${NRC_SRC_DIR}/mrqmin.c
        ${NRC_SRC_DIR}/mrqcof.c
        ${NRC_SRC_DIR}/nrutil.c
        ${NRC_SRC_DIR}/gaussj.c
        ${NRC_SRC_DIR}/covsrt.c)
target_include_directories(hw10 PUBLIC ${OpenCV_INCLUDE_DIRS} ../nrc/include)
target_link_libraries(hw10 PUBLIC ${OpenCV_LIBS})