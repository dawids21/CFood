add_executable(ingredient_test_run ingredient_test.c)

target_link_libraries(ingredient_test_run
        lib_ingredient
        unity
        )

add_test(ingredient_test ingredient_test_run)