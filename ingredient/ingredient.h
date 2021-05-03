//
// Created by dawids21 on 4/28/21.
//

#ifndef CFOOD_INGREDIENT_H
#define CFOOD_INGREDIENT_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    SOLID,
    LIQUID,
} IngredientType;

typedef struct Ingredient *Ingredient;

Ingredient create_new_ingredient(int id, char *name, int amount, IngredientType type);

void delete_ingredient(Ingredient *ingredient);

bool get_id(Ingredient ingredient, int *result);

bool get_name(Ingredient ingredient, char *result, int result_len);

bool get_amount(Ingredient ingredient, int *result);

bool get_type(Ingredient ingredient, IngredientType *result);

bool modify(Ingredient ingredient, char *new_name, int new_amount, IngredientType new_type);

#endif //CFOOD_INGREDIENT_H
