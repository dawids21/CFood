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

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(should_add_item_to_array);

    return UNITY_END();
}