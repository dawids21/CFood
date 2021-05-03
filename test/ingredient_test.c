//
// Created by dawids21 on 4/28/21.
//

#include <ingredient.h>
#include <unity.h>

static IngredientService service;

void setUp() {
    service = new_ingredient_service();
}

void tearDown() {
    delete_ingredient_service(service);
}

int main(void) {
    UNITY_BEGIN();

    return UNITY_END();
}