//
// Created by dawids21 on 4/29/21.
//

#include <ingredient.h>
#include <stdlib.h>
#include "array.h"

struct Array {
    ArrayType type;
    ArrayItem *data;
    int size;
    int capacity;
};

Array new_array(ArrayType type) {
    Array array = malloc(sizeof(struct Array));
    array->type = type;
    array->size = 0;
    array->capacity = 10;

    array->data = malloc(sizeof(ArrayItem) * array->capacity);

    return array;
}

void delete_array(Array array) {
    switch (array->type) {
        case INT:
            break;
        case INGREDIENT:
            for (int i = 0; i < array->size; i++) {
                free(array->data[i].ingredient_item);
            }
            break;
        default:
            break;
    }
    free(array->data);
    free(array);
}