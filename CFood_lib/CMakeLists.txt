set(SOURCE_FILES ingredient.c)

set(HEADER_FILE ingredient.h)

add_library(CFood_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(CFood_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})