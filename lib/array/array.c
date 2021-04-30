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

ArrayItem *delete_array(Array *array) {
    ArrayItem *current_items = get_all_items(*array);
    free(*array);
    *array = NULL;
    return current_items;
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

bool delete_at_index(Array array, int index) {
    if (index >= array->size) {
        return false;
    }

    ArrayItem to_delete = array->data[index];

    for (int i = index; i < array->size - 1; ++i) {
        array->data[i] = array->data[i + 1];
    }

    array->size--;
    return true;
}