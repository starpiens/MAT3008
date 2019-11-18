cmake_minimum_required(VERSION 3.15)
project(hw8)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED PATHS "/usr/local/Cellar/opencv@3/3.4.5_6")

add_executable(hw8 main.cpp)
target_include_directories(hw8 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(hw8 PUBLIC ${OpenCV_LIBS})