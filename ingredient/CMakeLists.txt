set(SOURCE_FILES ingredient.c ingredient_service.c)

set(HEADER_FILE ingredient.h ingredient_service.h)

add_library(lib_ingredient STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_ingredient PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(lib_ingredient lib_array)