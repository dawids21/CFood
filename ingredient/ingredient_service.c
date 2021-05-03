//
// Created by dawids21 on 5/3/21.
//

#include <array.h>
#include <string.h>
#include "ingredient_service.h"

struct IngredientService {
    Array ingredients;
};

static int find_index_by_id(IngredientService service, int id);

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
    if (service == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }

    ArrayItem deleted;
    delete_at_index(service->ingredients, index, &deleted);
    delete_ingredient(&deleted.ingredient_item);
    return true;
}

bool modify_ingredient(IngredientService service, int id, char *new_name, int new_amount, IngredientType new_type) {

    if (service == NULL) {
        return false;
    }

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem ingredients[get_num_of_ingredients(service)];
    get_all_items(service->ingredients, ingredients);
    bool success = modify(ingredients[index].ingredient_item, new_name, new_amount, new_type);
    return success;
}

static int find_index_by_id(IngredientService service, int id) {
    int num_of_items = get_num_of_ingredients(service);
    ArrayItem ingredients[num_of_items];
    get_all_items(service->ingredients, ingredients);

    for (int i = 0; i < num_of_items; ++i) {
        int current_id;
        get_id(ingredients[i].ingredient_item, &current_id);
        if (current_id == id) {
            return i;
        }
    }

    return -1;
}