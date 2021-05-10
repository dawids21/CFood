add_executable(ingredient_test_run ingredient_test.c)

target_link_libraries(ingredient_test_run
        lib_ingredient
        unity
        )

add_test(ingredient_test ingredient_test_run)

add_executable(acceptance_test_run acceptance_test.c)

target_link_libraries(acceptance_test_run
        lib_ingredient
        lib_recipe
        unity
        )

add_test(acceptance_test acceptance_test_run)

add_executable(array_test_run array_test.c)

target_link_libraries(array_test_run
        lib_array
        unity
        )

add_test(array_test array_test_run)
