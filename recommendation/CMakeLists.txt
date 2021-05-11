set(SOURCE_FILES recommendation_service.c)

set(HEADER_FILE recommendation_service.h)

add_library(lib_recommendation STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(lib_recommendation PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(lib_recommendation lib_recipe lib_ingredient)