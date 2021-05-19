//
// Created by dawids21 on 4/29/21.
//

#include <stdlib.h>
#include "array.h"

struct Array {
    ArrayItem *data;
    int size;
    int capacity;
};

Array new_array() {
    Array array = malloc(sizeof(struct Array));
    array->size = 0;
    array->capacity = 10;

    array->data = malloc(sizeof(ArrayItem) * array->capacity);

    return array;
}

void delete_array(Array *array, ArrayItem *current_items) {
    if (current_items != NULL) {
        array_get_all_items(*array, current_items);
    }
    free((*array)->data);
    free(*array);
    *array = NULL;
}

void array_append(Array array, ArrayItem item) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * sizeof(ArrayItem));
    }
    array->data[array->size++] = item;
}

void array_get_all_items(Array array, ArrayItem *result) {
    for (int i = 0; i < array->size; i++) {
        result[i] = array->data[i];
    }
}

int array_get_size(Array array) {
    return array->size;
}

bool array_delete_at_index(Array array, int index, ArrayItem *deleted) {
    if (index >= array->size) {
        return false;
    }

    if (deleted != NULL) {
        *deleted = array->data[index];
    }

    for (int i = index; i < array->size - 1; ++i) {
        array->data[i] = array->data[i + 1];
    }

    array->size--;
    return true;
}

bool array_get(Array array, int index, ArrayItem *result) {
    if (result == NULL || index < 0 || index >= array->size) {
        return false;
    }
    *result = array->data[index];
    return true;
}

void array_insert_at(Array array, int index, ArrayItem arrayItem) {

    if (index < 0) {
        return;
    }

    if (index >= array->size) {
        array_append(array, arrayItem);
        return;
    }

    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * sizeof(ArrayItem));
    }

    for (int i = array->size - 1; i >= index; i--) {
        array->data[i + 1] = array->data[i];
    }

    array->data[index] = arrayItem;
    array->size++;
}
