//
// Created by dawids21 on 5/3/21.
//

#include <array.h>
#include <string.h>
#include <stdio.h>
#include "ingredient_service.h"

struct IngredientService {
    int id_ingredients;
    Array ingredients;
    char *filename;
};

static int find_index_by_id(IngredientService service, int id);

static bool is_ingredient_with_name(IngredientService service, char *name);

static void convert_ingredient_to_read_model(Ingredient ingredient, IngredientReadModel *result);

IngredientService new_ingredient_service(char *filename) {
    IngredientService service = (IngredientService) malloc(sizeof(struct IngredientService));
    service->id_ingredients = 0;
    service->ingredients = new_array();
    service->filename = malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(service->filename, filename);
    return service;
}

void delete_ingredient_service(IngredientService service) {
    int num_of_ingredients = ingredient_service_get_num_of_ingredients(service);
    ArrayItem deleted[num_of_ingredients];
    delete_array(&(service->ingredients), deleted);

    for (int i = 0; i < num_of_ingredients; ++i) {
        Ingredient to_delete = deleted[i].ingredient_item;
        delete_ingredient(&to_delete);
    }
    free(service->filename);
    free(service);
}

int ingredient_service_get_num_of_ingredients(IngredientService service) {
    return array_get_size(service->ingredients);
}

int ingredient_service_add_ingredient(IngredientService service, char *name, int amount, IngredientType type) {
    if (strlen(name) == 0 || amount < 0 || is_ingredient_with_name(service, name)) {
        return -1;
    }

    int id = service->id_ingredients++;
    ArrayItem to_add = {.ingredient_item = create_new_ingredient(id, name, amount, type)};
    array_append(service->ingredients, to_add);
    return id;
}

void ingredient_service_get_all_ingredients(IngredientService service, IngredientReadModel *result) {

    if (service == NULL || result == NULL) {
        return;
    }

    int num_of_ingredients = ingredient_service_get_num_of_ingredients(service);
    ArrayItem ingredients[num_of_ingredients];
    array_get_all_items(service->ingredients, ingredients);
    for (int i = 0; i < num_of_ingredients; ++i) {
        Ingredient current = ingredients[i].ingredient_item;
        convert_ingredient_to_read_model(current, &result[i]);
    }
}

bool ingredient_service_get_ingredient_by_id(IngredientService service, int id, IngredientReadModel *result) {
    if (service == NULL || result == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }
    ArrayItem item;
    array_get(service->ingredients, index, &item);
    convert_ingredient_to_read_model(item.ingredient_item, result);
    return true;
}

bool ingredient_service_remove_ingredient(IngredientService service, int id) {
    if (service == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }

    ArrayItem deleted;
    array_delete_at_index(service->ingredients, index, &deleted);
    delete_ingredient(&deleted.ingredient_item);
    return true;
}

bool ingredient_service_modify_ingredient(IngredientService service, int id, char *new_name, int new_amount,
                                          IngredientType new_type) {

    if (service == NULL) {
        return false;
    }

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem ingredients[ingredient_service_get_num_of_ingredients(service)];
    array_get_all_items(service->ingredients, ingredients);
    bool success = ingredient_modify(ingredients[index].ingredient_item, new_name, new_amount, new_type);
    return success;
}

bool ingredient_service_reduce_amount_of_ingredient(IngredientService service, int id, int to_reduce) {

    if (service == NULL) {
        return false;
    }

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem ingredients[ingredient_service_get_num_of_ingredients(service)];
    array_get_all_items(service->ingredients, ingredients);
    Ingredient ingredient = ingredients[index].ingredient_item;
    int current_amount;
    ingredient_get_amount(ingredient, &current_amount);
    if (current_amount < to_reduce) {
        return false;
    }
    return ingredient_modify_amount(ingredient, current_amount - to_reduce);
}

void save_ingredient_service(IngredientService service) {
    if (strlen(service->filename) == 0) {
        return;
    }

    FILE *f = fopen(service->filename, "wb");

    const int size = array_get_size(service->ingredients);
    fwrite(&size, sizeof(int), 1, f);
    fwrite(&service->id_ingredients, sizeof(int), 1, f);
    ArrayItem items[size];
    array_get_all_items(service->ingredients, items);

    for (int i = 0; i < size; i++) {
        save_ingredient(items[i].ingredient_item, f);
    }
    fclose(f);
}

IngredientService restore_ingredient_service(char *filename) {
    IngredientService service = new_ingredient_service(filename);
    FILE *f = fopen(service->filename, "rb");
    int size;
    fread(&size, sizeof(int), 1, f);
    fread(&service->id_ingredients, sizeof(int), 1, f);

    for (int i = 0; i < size; ++i) {
        Ingredient ingredient = restore_ingredient(f);
        ArrayItem item = {.ingredient_item = ingredient};
        array_append(service->ingredients, item);
    }

    fclose(f);
    return service;
}

static int find_index_by_id(IngredientService service, int id) {
    int num_of_items = ingredient_service_get_num_of_ingredients(service);
    ArrayItem ingredients[num_of_items];
    array_get_all_items(service->ingredients, ingredients);

    for (int i = 0; i < num_of_items; ++i) {
        int current_id;
        ingredient_get_id(ingredients[i].ingredient_item, &current_id);
        if (current_id == id) {
            return i;
        }
    }

    return -1;
}

static bool is_ingredient_with_name(IngredientService service, char *name) {
    int size = array_get_size(service->ingredients);
    size_t name_len = strlen(name) + 1;
    ArrayItem ingredients[size];
    array_get_all_items(service->ingredients, ingredients);
    for (int i = 0; i < size; ++i) {
        char ingredient_name[name_len];
        ingredient_get_name(ingredients[i].ingredient_item, ingredient_name, (int) name_len);
        if (strcmp(ingredient_name, name) == 0) {
            return true;
        }
    }
    return false;
}

static void convert_ingredient_to_read_model(Ingredient ingredient, IngredientReadModel *result) {
    ingredient_get_id(ingredient, &(result->id));
    ingredient_get_name(ingredient, result->name, MAX_INGREDIENT_NAME_LEN);
    ingredient_get_amount(ingredient, &(result->amount));
    ingredient_get_type(ingredient, &(result->type));
}