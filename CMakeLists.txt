cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

option(DEV "Use dev profile" TRUE)

add_subdirectory(lib/array)
add_subdirectory(ingredient)

if (DEV)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
endif (DEV)
unset(DEV CACHE)

add_executable(cfood main.c)

target_link_libraries(cfood lib_ingredient)
