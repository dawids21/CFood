cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

option(DEV "" TRUE)

add_subdirectory(lib/array)
add_subdirectory(ingredient)
add_subdirectory(main)


if (DEV)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
endif (DEV)
unset(DEV CACHE)