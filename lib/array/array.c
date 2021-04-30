//
// Created by dawids21 on 4/29/21.
//

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

void append(Array array, ArrayItem item) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * sizeof(ArrayItem));
    }
    array->data[array->size++] = item;
}

ArrayItem *get_all_items(Array array) {
    ArrayItem *result = malloc(sizeof(ArrayItem) * array->size);
    for (int i = 0; i < array->size; i++) {
        result[i] = array->data[i];
    }
    return result;
}

int get_size(Array array) {
    return array->size;
}

void delete_at_index(Array array, int index) {

}