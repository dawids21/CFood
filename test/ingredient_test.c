//
// Created by dawids21 on 4/28/21.
//

#include <unity.h>
#include <ingredient_service.h>
#include <ingredient.h>

static IngredientService service;

void setUp() {
    service = new_ingredient_service();
}

void tearDown() {
    delete_ingredient_service(service);
}

void return_num_of_ingredients() {
    add_ingredient(service, "Bread", 5, SOLID);
    add_ingredient(service, "Water", 750, LIQUID);

    TEST_ASSERT_EQUAL(2, get_num_of_ingredients(service));
}

void should_add_item_to_array() {

    bool success = add_ingredient(service, "Bread", 5, SOLID);

    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL(1, get_num_of_ingredients(service));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(return_num_of_ingredients);
    RUN_TEST(should_add_item_to_array);

    return UNITY_END();
}