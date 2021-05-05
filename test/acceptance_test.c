//
// Created by dawids21 on 4/29/21.
//

#include <unity.h>
#include <ingredient_service.h>

static IngredientService ingredient_service;

void setUp() {
    ingredient_service = new_ingredient_service("");
}

void tearDown() {
    delete_ingredient_service(ingredient_service);
}

void standard_acceptance_test(void) {

    // when I add 2 bread, 3 cheese, 1000 ml of water
    add_ingredient(ingredient_service, "Bread", 2, SOLID);
    add_ingredient(ingredient_service, "Cheese", 3, SOLID);
    add_ingredient(ingredient_service, "Water", 1000, LIQUID);
    // then on the list of ingredients I see 2 bread, 3 cheese, 1000 ml of water
    IngredientReadModel ingredients[get_num_of_ingredients(ingredient_service)];
    get_all_ingredients(ingredient_service, ingredients);
    TEST_ASSERT_EQUAL_STRING("Bread", ingredients[0].name);
    TEST_ASSERT_EQUAL(2, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
    TEST_ASSERT_EQUAL_STRING("Cheese", ingredients[1].name);
    TEST_ASSERT_EQUAL(3, ingredients[1].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[1].type);
    TEST_ASSERT_EQUAL_STRING("Water", ingredients[2].name);
    TEST_ASSERT_EQUAL(1000, ingredients[2].amount);
    TEST_ASSERT_EQUAL(LIQUID, ingredients[2].type);

    // when I change the amount of cheese to 2
    modify_ingredient(ingredient_service, ingredients[1].id, ingredients[1].name, 2, ingredients[1].type);
    // then on the list of ingredients I see 2 bread and 2 cheese, 1000 ml of water.
    get_all_ingredients(ingredient_service, ingredients);
    TEST_ASSERT_EQUAL_STRING("Bread", ingredients[0].name);
    TEST_ASSERT_EQUAL(2, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
    TEST_ASSERT_EQUAL_STRING("Cheese", ingredients[1].name);
    TEST_ASSERT_EQUAL(2, ingredients[1].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[1].type);
    TEST_ASSERT_EQUAL_STRING("Water", ingredients[2].name);
    TEST_ASSERT_EQUAL(1000, ingredients[2].amount);
    TEST_ASSERT_EQUAL(LIQUID, ingredients[2].type);

    // when I add recipe for standard breakfast and premium breakfast
    // then on the list of recipes I see the recipes for standard breakfast and premium breakfast

    // when I open recommendations for meal
    // then I can see the recipe for standard breakfast

    // when I click the option to prepare standard breakfast
    // then I can see the recipe

    // when I click the meal is ready and ask for the list of ingredients
    // then on the list of ingredients I see 1 bread and 1 cheese, 750 ml of water.

    TEST_FAIL_MESSAGE("Standard acceptance test not implemented yet");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(standard_acceptance_test);

    return UNITY_END();
}
