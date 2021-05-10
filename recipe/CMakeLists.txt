set(SOURCE_FILES recipe.c recipe_service.c)

set(HEADER_FILE recipe.h recipe_service.h)

add_library(lib_recipe STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_ingredient PUBLIC ${CMAKE_CURRENT_LIST_DIR})