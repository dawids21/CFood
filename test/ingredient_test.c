//
// Created by dawids21 on 4/28/21.
//

#include <unity.h>
#include <ingredient_service.h>

static IngredientService service;

void setUp() {
    service = new_ingredient_service();
}

void tearDown() {
    delete_ingredient_service(service);
}

void should_add_item_to_array() {

    bool success = add_solid_ingredient(service, "Bread", 5);

    TEST_ASSERT_TRUE(success);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_add_item_to_array);

    return UNITY_END();
}