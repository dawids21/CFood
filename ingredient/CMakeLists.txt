set(SOURCE_FILES ingredient.c)

set(HEADER_FILE ingredient.h)

add_library(lib_ingredient STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_ingredient PUBLIC .)