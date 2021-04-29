//
// Created by dawids21 on 4/29/21.
//

#ifndef CFOOD_ARRAY_H
#define CFOOD_ARRAY_H

typedef enum {
    INGREDIENT,
    INT
} ArrayType;
typedef struct Array *Array;

Array newArray(ArrayType type);

void deleteArray(Array array);

#endif //CFOOD_ARRAY_H
