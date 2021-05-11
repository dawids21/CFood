cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

option(DEV "Use dev profile" false)

add_subdirectory(lib/array)
add_subdirectory(ingredient)
add_subdirectory(recipe)
add_subdirectory(recommendation)

if (DEV)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
endif (DEV)
unset(DEV CACHE)

set(SOURCE_FILES main.c input.c ingredient_service_controller.c recipe_service_controller.c)
set(HEADER_FILES input.h ingredient_service_controller.h recipe_service_controller.h)

add_executable(cfood ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(cfood lib_ingredient lib_recipe lib_recommendation)
