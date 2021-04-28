cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

set(TARGET_GROUP production CACHE STRING "Group to build")

add_subdirectory(CFood_lib)
add_subdirectory(main)