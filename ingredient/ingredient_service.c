//
// Created by dawids21 on 5/3/21.
//

#include <array.h>
#include <string.h>
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
    if (strlen(name) == 0 || amount < 0) {
        return false;
    }
    ArrayItem to_add = {.ingredient_item = create_new_ingredient(get_num_of_ingredients(service), name, amount, type)};
    append(service->ingredients, to_add);
    return true;
}

void get_all_ingredients(IngredientService service, IngredientReadModel *result) {

    if (service == NULL || result == NULL) {
        return;
    }

    int num_of_ingredients = get_num_of_ingredients(service);
    ArrayItem ingredients[num_of_ingredients];
    get_all_items(service->ingredients, ingredients);
    for (int i = 0; i < num_of_ingredients; ++i) {
        Ingredient current = ingredients[i].ingredient_item;
        get_id(current, &(result[i].id));
        get_name(current, result[i].name, MAX_INGREDIENT_NAME_LEN);
        get_amount(current, &(result[i].amount));
        get_type(current, &(result[i].type));
    }
}

bool remove_ingredient(IngredientService service, int id) {
    return true;
}