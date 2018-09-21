cmake_minimum_required(VERSION 3.12)
project(gVM2)

set(CMAKE_CXX_STANDARD 17)

add_library(util util.h util.cpp)
add_library(motherboard gvm_machine/Motherboard.h gvm_machine/Motherboard.cpp)

add_library(memory gvm_machine/Memory.h gvm_machine/Memory.cpp)
add_library(cpu gvm_machine/CPU.h gvm_machine/CPU.cpp)

add_executable(gvm main.cpp)
target_link_libraries(gvm motherboard)
target_link_libraries(gvm memory)
target_link_libraries(gvm cpu)
target_link_libraries(gvm util)

add_executable(gvmas gvm_compiler/Assembler.h gvm_compiler/Assembler.cpp)
target_link_libraries(gvmas util)