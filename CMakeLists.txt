cmake_minimum_required(VERSION 3.19)
project(CFood)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c)

add_executable(CFood_run ${SOURCE_FILES})

include_directories(CFood_lib)
add_subdirectory(CFood_lib)
target_link_libraries(CFood_run CFood_lib)

