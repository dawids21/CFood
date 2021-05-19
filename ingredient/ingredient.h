//
// Created by dawids21 on 4/28/21.
//

#ifndef CFOOD_INGREDIENT_H
#define CFOOD_INGREDIENT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    SOLID,
    LIQUID,
} IngredientType;

typedef struct Ingredient *Ingredient;

Ingredient create_new_ingredient(int id, char *name, int amount, IngredientType type);

void delete_ingredient(Ingredient *ingredient);

bool ingredient_get_id(Ingredient ingredient, int *result);

bool ingredient_get_name(Ingredient ingredient, char *result, int result_len);

bool ingredient_get_amount(Ingredient ingredient, int *result);

bool ingredient_get_type(Ingredient ingredient, IngredientType *result);

bool ingredient_modify(Ingredient ingredient, char *new_name, int new_amount, IngredientType new_type);

bool ingredient_modify_amount(Ingredient ingredient, int new_amount);

void save_ingredient(Ingredient ingredient, FILE *f);

Ingredient restore_ingredient(FILE *f);

#endif //CFOOD_INGREDIENT_H
