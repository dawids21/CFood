cmake_minimum_required(VERSION 3.19)
project(CFood C)

set(CMAKE_C_STANDARD 99)

option(DEV "Use dev profile" false)

add_subdirectory(lib/array)
add_subdirectory(ingredient)
add_subdirectory(recipe)
add_subdirectory(recommendation)
add_subdirectory(cooking)

if (DEV)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
endif (DEV)
unset(DEV CACHE)

set(SOURCE_FILES main.c ingredient_service_controller.c recipe_service_controller.c recommendation_service_controller.c cooking_service_controller.c)
set(HEADER_FILES app.h ingredient_service_controller.h recipe_service_controller.h recommendation_service_controller.h cooking_service_controller.h)

add_executable(cfood ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(cfood lib_ingredient lib_recipe lib_recommendation)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(cfood ${GTK3_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/glade/window_main.glade ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)