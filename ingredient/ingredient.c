//
// Created by dawids21 on 4/28/21.
//

#include <string.h>
#include "ingredient.h"

struct Ingredient {
    int id;
    char *name;
    int amount;
    IngredientType type;
};

Ingredient create_new_ingredient(int id, char *name, int amount, IngredientType type) {
    Ingredient ingredient = malloc(sizeof(struct Ingredient));

    ingredient->id = id;
    ingredient->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(ingredient->name, name);
    ingredient->amount = amount;
    ingredient->type = type;

    return ingredient;
}

void delete_ingredient(Ingredient *ingredient) {
    free((*ingredient)->name);
    free(*ingredient);
    *ingredient = NULL;
}

bool get_id(Ingredient ingredient, int *result) {
    if (ingredient == NULL) {
        return false;
    }
    *result = ingredient->id;
    return true;
}

bool get_name(Ingredient ingredient, char *result, int result_len) {
    if (ingredient == NULL) {
        return false;
    }
    strncpy(result, ingredient->name, result_len);
    return true;
}

bool get_amount(Ingredient ingredient, int *result) {
    if (ingredient == NULL) {
        return false;
    }
    *result = ingredient->amount;
    return true;
}

bool get_type(Ingredient ingredient, IngredientType *result) {
    if (ingredient == NULL) {
        return false;
    }
    *result = ingredient->type;
    return true;
}

bool modify(Ingredient ingredient, char *new_name, int new_amount, IngredientType new_type) {
    if (ingredient == NULL || strlen(new_name) == 0 || new_amount < 0) {
        return false;
    }

    ingredient->amount = new_amount;
    ingredient->type = new_type;
    ingredient->name = realloc(ingredient->name, (strlen(new_name) + 1) * sizeof(char));
    strcpy(ingredient->name, new_name);
    return true;
}