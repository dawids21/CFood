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

void return_false_when_name_not_given() {
    bool success = add_ingredient(service, "", 5, SOLID);

    TEST_ASSERT_FALSE(success);
    TEST_ASSERT_EQUAL(0, get_num_of_ingredients(service));
}

void return_false_when_amount_is_negative() {
    bool success = add_ingredient(service, "Bread", -1, SOLID);

    TEST_ASSERT_FALSE(success);
    TEST_ASSERT_EQUAL(0, get_num_of_ingredients(service));
}

void return_list_of_all_ingredients() {
    add_ingredient(service, "Bread", 5, SOLID);
    add_ingredient(service, "Water", 1000, LIQUID);

    IngredientReadModel ingredients[get_num_of_ingredients(service)];

    get_all_ingredients(service, ingredients);

    TEST_ASSERT_EQUAL_STRING("Bread", ingredients[0].name);
    TEST_ASSERT_EQUAL(5, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
    TEST_ASSERT_EQUAL_STRING("Water", ingredients[1].name);
    TEST_ASSERT_EQUAL(1000, ingredients[1].amount);
    TEST_ASSERT_EQUAL(LIQUID, ingredients[1].type);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(return_num_of_ingredients);
    RUN_TEST(should_add_item_to_array);
    RUN_TEST(return_false_when_name_not_given);
    RUN_TEST(return_false_when_amount_is_negative);
    RUN_TEST(return_list_of_all_ingredients);

    return UNITY_END();
}