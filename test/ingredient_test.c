//
// Created by dawids21 on 4/28/21.
//

#include <unity.h>
#include <ingredient_service.h>
#include <ingredient.h>

static IngredientService service;

void setUp() {
    service = new_ingredient_service("");
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

void remove_ingredient_deletes_ingredient_at_given_index() {
    add_ingredient(service, "Bread", 5, SOLID);
    add_ingredient(service, "Water", 1000, LIQUID);
    add_ingredient(service, "Cheese", 2, SOLID);

    IngredientReadModel ingredients[get_num_of_ingredients(service)];
    get_all_ingredients(service, ingredients);
    bool success = remove_ingredient(service, ingredients[1].id);
    get_all_ingredients(service, ingredients);

    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL(2, get_num_of_ingredients(service));
}

void remove_ingredient_returns_false_when_id_not_exists() {
    add_ingredient(service, "Bread", 5, SOLID);
    add_ingredient(service, "Cheese", 2, SOLID);

    IngredientReadModel ingredients[get_num_of_ingredients(service)];
    get_all_ingredients(service, ingredients);
    bool success = remove_ingredient(service, 6);
    get_all_ingredients(service, ingredients);

    TEST_ASSERT_FALSE(success);
    TEST_ASSERT_EQUAL(2, get_num_of_ingredients(service));
}

void modify_ingredient_change_the_name_amount_and_type() {
    add_ingredient(service, "Bread", 5, SOLID);
    int id = 0;

    bool success = modify_ingredient(service, id, "Cheese", 2, SOLID);
    IngredientReadModel ingredients[get_num_of_ingredients(service)];
    get_all_ingredients(service, ingredients);

    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL(id, ingredients[0].id);
    TEST_ASSERT_EQUAL_STRING("Cheese", ingredients[0].name);
    TEST_ASSERT_EQUAL(2, ingredients[0].amount);
    TEST_ASSERT_EQUAL(SOLID, ingredients[0].type);
}

void modify_ingredient_return_false_when_id_not_exists() {
    add_ingredient(service, "Bread", 5, SOLID);
    int id = 5;

    bool success = modify_ingredient(service, id, "Cheese", 2, SOLID);

    TEST_ASSERT_FALSE(success);
}

void save_ingredient_service_should_save_data_in_a_file() {
    IngredientService test_service = new_ingredient_service("./test.bin");
    add_ingredient(service, "Bread", 5, SOLID);

    save_ingredient_service(test_service);

    delete_ingredient_service(test_service);
    test_service = restore_ingredient_service("./test.bin");

    int num_of_ingredients = get_num_of_ingredients(test_service);
    TEST_ASSERT_EQUAL(1, num_of_ingredients);

    IngredientReadModel result[get_num_of_ingredients(test_service)];
    get_all_ingredients(test_service, result);

    delete_ingredient_service(test_service);

//    TEST_ASSERT_EQUAL(0, result[0].id);
//    TEST_ASSERT_EQUAL_STRING("Bread", result[0].name);
//    TEST_ASSERT_EQUAL(5, result[0].amount);
//    TEST_ASSERT_EQUAL(SOLID, result[0].type);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(return_num_of_ingredients);
    RUN_TEST(should_add_item_to_array);
    RUN_TEST(return_false_when_name_not_given);
    RUN_TEST(return_false_when_amount_is_negative);
    RUN_TEST(return_list_of_all_ingredients);
    RUN_TEST(remove_ingredient_deletes_ingredient_at_given_index);
    RUN_TEST(remove_ingredient_returns_false_when_id_not_exists);
    RUN_TEST(modify_ingredient_change_the_name_amount_and_type);
    RUN_TEST(modify_ingredient_return_false_when_id_not_exists);
    RUN_TEST(save_ingredient_service_should_save_data_in_a_file);

    return UNITY_END();
}