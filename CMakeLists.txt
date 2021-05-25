cmake_minimum_required(VERSION 3.17)
project(LowLevelProgramming2021 C)

set(CMAKE_C_STANDARD 11)
add_library(graph STATIC Lab2/graph.c Lab2/graph.h Lab2/math.c Lab2/math.h Lab2/test.h Lab2/test.c)
add_executable(LowLevelProgramming2021 Lab2/main/main.c Lab2/main/main.h)
target_link_libraries(LowLevelProgramming2021 "C:/Users/Vadim/CLionProjects/LowLevelProgramming2021/Lab2/main/libgraph.a")

