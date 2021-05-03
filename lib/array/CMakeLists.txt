set(SOURCE_FILES array.c)

set(HEADER_FILE array.h)

add_library(lib_array STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_array PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(lib_array lib_ingredient)
