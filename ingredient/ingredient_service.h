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
    int id;
    char name[MAX_INGREDIENT_NAME_LEN];
    int amount;
    IngredientType type;
} IngredientReadModel;

IngredientService new_ingredient_service(char *filename);

void delete_ingredient_service(IngredientService service);

int get_num_of_ingredients(IngredientService service);

bool add_ingredient(IngredientService service, char *name, int amount, IngredientType type);

void get_all_ingredients(IngredientService service, IngredientReadModel *result);

bool get_ingredient_by_id(IngredientService service, int id, IngredientReadModel *result);

bool remove_ingredient(IngredientService service, int id);

bool modify_ingredient(IngredientService service, int id, char *new_name, int new_amount, IngredientType new_type);

bool reduce_amount_of_ingredient(IngredientService service, int id, int to_reduce);

void save_ingredient_service(IngredientService service);

IngredientService restore_ingredient_service(char *filename);

#endif //CFOOD_INGREDIENT_SERVICE_H
