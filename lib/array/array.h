//
// Created by dawids21 on 4/29/21.
//

#ifndef CFOOD_ARRAY_H
#define CFOOD_ARRAY_H

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

void deleteArray(Array array);

#endif //CFOOD_ARRAY_H
