cmake_minimum_required(VERSION 3.15)
project(hw10 CXX)

set(OPENCV_DIR "/usr/local/Cellar/opencv@3/3.4.5_6")
set(NRC_INCLUDE_DIR "../nrc/include")
set(NRC_SRC_DIR "../nrc/src/")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(${NRC_INCLUDE_DIR})
find_package(OpenCV REQUIRED PATHS ${OPENCV_DIR})

add_library(NRC_OBJ OBJECT
        ${NRC_SRC_DIR}/nrutil.c
        ${NRC_SRC_DIR}/mrqmin.c
        ${NRC_SRC_DIR}/mrqcof.c
        ${NRC_SRC_DIR}/gaussj.c
        ${NRC_SRC_DIR}/covsrt.c)
set_target_properties(NRC_OBJ PROPERTIES LANGUAGE C)

add_executable(hw10
        ${NRC_OBJ}
        main.cpp)
set_target_properties(hw10 PROPERTIES LANGUAGE CXX)
target_include_directories(hw10 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(hw10 PUBLIC ${OpenCV_LIBS})