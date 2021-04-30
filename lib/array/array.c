//
// Created by dawids21 on 4/29/21.
//

#include <ingredient.h>
#include <stdlib.h>
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

Array new_array(ArrayType type) {
    Array array = malloc(sizeof(struct Array));
    array->type = type;
    array->size = 0;
    array->capacity = 10;

    switch (type) {
        case INT:
            array->data.int_data = malloc(sizeof(int) * array->capacity);
            break;
        case INGREDIENT:
            array->data.ingredient_data = malloc(get_size_of_ingredient_type() * array->capacity);
            break;
        default:
            break;
    }

    return array;
}

void delete_array(Array array) {
    switch (array->type) {
        case INT:
            free(array->data.int_data);
            break;
        case INGREDIENT:
            for (int i = 0; i < array->size; i++) {
                free(array->data.ingredient_data[i]);
            }
            free(array->data.ingredient_data);
            break;
        default:
            break;
    }
    free(array);
}