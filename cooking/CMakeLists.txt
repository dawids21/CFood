set(SOURCE_FILES cooking_service.c)

set(HEADER_FILE cooking_service.h)

add_library(lib_cooking STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_cooking PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(lib_cooking lib_recipe)