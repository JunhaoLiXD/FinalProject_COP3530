cmake_minimum_required(VERSION 3.27)
project(FinalProject_COP3530)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(FinalProject_COP3530
        include/algorithm.h
        src/algorithm.cpp)
