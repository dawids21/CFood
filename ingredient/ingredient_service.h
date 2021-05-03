//
// Created by dawids21 on 5/3/21.
//

#ifndef CFOOD_INGREDIENT_SERVICE_H
#define CFOOD_INGREDIENT_SERVICE_H

#include <stdbool.h>
#include <ingredient.h>

typedef struct IngredientService *IngredientService;

IngredientService new_ingredient_service();

void delete_ingredient_service(IngredientService service);

int get_num_of_ingredients(IngredientService service);

bool add_ingredient(IngredientService service, char *name, int amount, IngredientType type);

#endif //CFOOD_INGREDIENT_SERVICE_H
