project(CFood_lib)

set(SOURCE_FILES ingredient.c)

set(HEADER_FILE ingredient.h)

add_library(CFood_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})