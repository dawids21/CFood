//
// Created by dawids21 on 5/3/21.
//

#ifndef CFOOD_INGREDIENT_SERVICE_H
#define CFOOD_INGREDIENT_SERVICE_H

#include <stdbool.h>
#include <ingredient.h>

#define MAX_INGREDIENT_NAME_LEN 100

typedef struct IngredientService *IngredientService;

typedef struct {
    char name[MAX_INGREDIENT_NAME_LEN];
    int amount;
    IngredientType type;
} IngredientReadModel;

IngredientService new_ingredient_service();

void delete_ingredient_service(IngredientService service);

int get_num_of_ingredients(IngredientService service);

bool add_ingredient(IngredientService service, char *name, int amount, IngredientType type);

void get_all_ingredients(IngredientService service, IngredientReadModel *result);

#endif //CFOOD_INGREDIENT_SERVICE_H
