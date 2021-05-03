//
// Created by dawids21 on 5/3/21.
//

#include <array.h>
#include "ingredient_service.h"

struct IngredientService {
    Array ingredients;
};

IngredientService new_ingredient_service() {
    IngredientService service = (IngredientService) malloc(sizeof(struct IngredientService));
    service->ingredients = new_array();
    return service;
}

void delete_ingredient_service(IngredientService service) {
    free(service);
}

int get_num_of_ingredients(IngredientService service) {
    return get_size(service->ingredients);
}

bool add_ingredient(IngredientService service, char *name, int amount, IngredientType type) {
    return true;
}