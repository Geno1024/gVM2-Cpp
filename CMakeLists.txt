cmake_minimum_required(VERSION 3.12)
project(gVM2)

set(CMAKE_CXX_STANDARD 17)

add_library(memory Memory.h Memory.cpp)
add_library(cpu CPU.h CPU.cpp)

add_executable(gVM2 main.cpp)
target_link_libraries(gVM2 memory)
target_link_libraries(gVM2 cpu)