# cmake_minimum_required(VERSION <specify CMake version here>)
project(ThreeCommuntcation C)

set(CMAKE_C_STANDARD 99)

add_executable(ThreeCommuntcation A.c MusicTool.h MusicTool.c B.c)