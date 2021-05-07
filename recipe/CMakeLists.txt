set(SOURCE_FILES recipe.c)

set(HEADER_FILE recipe.h)

add_library(lib_recipe STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_ingredient PUBLIC ${CMAKE_CURRENT_LIST_DIR})