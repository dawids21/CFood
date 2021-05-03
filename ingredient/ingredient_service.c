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
    int num_of_ingredients = get_num_of_ingredients(service);
    ArrayItem deleted[num_of_ingredients];
    delete_array(&(service->ingredients), deleted);

    for (int i = 0; i < num_of_ingredients; ++i) {
        Ingredient to_delete = deleted[i].ingredient_item;
        delete_ingredient(&to_delete);
    }

    free(service);
}

int get_num_of_ingredients(IngredientService service) {
    return get_size(service->ingredients);
}

bool add_ingredient(IngredientService service, char *name, int amount, IngredientType type) {
    ArrayItem to_add = {.ingredient_item = create_new_ingredient(get_num_of_ingredients(service), name, amount, type)};
    append(service->ingredients, to_add);
    return true;
}