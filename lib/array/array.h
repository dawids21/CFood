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

void append(Array array, ArrayItem item);

void get_all_items(Array array, ArrayItem *result);

int get_size(Array array);

bool delete_at_index(Array array, int index, ArrayItem *deleted);

bool get(Array array, int index, ArrayItem *result);

void insert_at(Array array, int index, ArrayItem arrayItem);

#endif //CFOOD_ARRAY_H
