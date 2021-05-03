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
