cmake_minimum_required(VERSION 2.8)
project(projec3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

set(SOURCE_FILES main.cpp Piggy_Bank.cpp Piggy_Bank.h)
add_executable(project3 ${SOURCE_FILES})