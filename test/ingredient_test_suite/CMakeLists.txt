add_executable(ingredient_test_suite_run ingredient_test.c)

target_link_libraries(ingredient_test_suite_run
        CFood_lib
        Unity
        )

add_test(ingredient_test_suite ingredient_test_suite_run)