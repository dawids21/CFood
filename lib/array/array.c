//
// Created by dawids21 on 4/29/21.
//

#include <ingredient.h>
#include "array.h"

struct Array {
    ArrayType type;
    union {
        Ingredient *ingredient_data;
        int *int_data;
    } data;
    int size;
    int capacity;
};