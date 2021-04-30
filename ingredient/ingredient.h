//
// Created by dawids21 on 4/28/21.
//

#ifndef CFOOD_INGREDIENT_H
#define CFOOD_INGREDIENT_H

#include <stdlib.h>

typedef struct Ingredient *Ingredient;
typedef struct IngredientService *IngredientService;

size_t get_size_of_ingredient_type();

IngredientService new_ingredient_service();

void delete_ingredient_service(IngredientService service);

#endif //CFOOD_INGREDIENT_H
