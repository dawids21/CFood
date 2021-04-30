//
// Created by dawids21 on 4/29/21.
//

#ifndef CFOOD_ARRAY_H
#define CFOOD_ARRAY_H

#include <ingredient.h>

typedef enum {
    INGREDIENT,
    INT
} ArrayType;

typedef union {
    int int_item;
    Ingredient ingredient_item;
} ArrayItem;

typedef struct Array *Array;

Array new_array(ArrayType type);

void delete_array(Array array);

void append(Array array, ArrayItem item);

ArrayItem *get_all_items(Array array);

int get_size(Array array);

#endif //CFOOD_ARRAY_H
