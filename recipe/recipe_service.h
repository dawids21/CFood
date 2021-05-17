//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_H
#define CFOOD_RECIPE_SERVICE_H

#include <stdbool.h>
#include <recipe.h>
#include <ingredient_service.h>

typedef struct RecipeService *RecipeService;

#define MAX_RECIPE_NAME_LEN 100

RecipeService new_recipe_service(char *filename, IngredientService ingredientService);

void delete_recipe_service(RecipeService service);

int get_num_of_recipes(RecipeService service);

int add_recipe(RecipeService service, char *name, char *steps[], int num_of_steps, RecipeIngredient ingredients[],
               int num_of_ingredients);

void get_all_recipes(RecipeService service, RecipeReadModel *result);

bool get_recipe_by_id(RecipeService service, int id, RecipeReadModel *result);

bool remove_recipe(RecipeService service, int id);

bool remove_recipe_with_ingredient_id(RecipeService service, int ingredient_id);

void print_detailed_info_about_recipe(RecipeService service, int id);

bool remove_ingredients_from_recipe(RecipeService service, int id);

bool check_if_recipe_is_possible(RecipeService service, int id);

void save_recipe_service(RecipeService service);

RecipeService restore_recipe_service(char *filename, IngredientService ingredient_service);

#endif //CFOOD_RECIPE_SERVICE_H
