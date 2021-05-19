//
// Created by dawids21 on 4/29/21.
//

#ifndef CFOOD_ARRAY_H
#define CFOOD_ARRAY_H

#include <ingredient.h>
#include <stdbool.h>
#include <recipe.h>

typedef union {
    int int_item;
    Ingredient ingredient_item;
    Recipe recipe_item;
} ArrayItem;

typedef struct Array *Array;

Array new_array();

void delete_array(Array *array, ArrayItem *current_items);

void array_append(Array array, ArrayItem item);

void array_get_all_items(Array array, ArrayItem *result);

int array_get_size(Array array);

bool array_delete_at_index(Array array, int index, ArrayItem *deleted);

bool array_get(Array array, int index, ArrayItem *result);

void array_insert_at(Array array, int index, ArrayItem arrayItem);

#endif //CFOOD_ARRAY_H
