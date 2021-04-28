cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

set(PROFILE dev)

add_subdirectory(ingredient)
add_subdirectory(main)


if (${PROFILE} STREQUAL dev)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
endif ()