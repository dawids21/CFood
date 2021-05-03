//
// Created by dawids21 on 4/28/21.
//

#ifndef CFOOD_INGREDIENT_H
#define CFOOD_INGREDIENT_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Ingredient *Ingredient;

bool get_name(Ingredient ingredient, char *result, int result_len);

bool get_amount(Ingredient ingredient, int *result);

#endif //CFOOD_INGREDIENT_H
