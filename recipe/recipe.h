//
// Created by dawids21 on 5/7/21.
//

#ifndef CFOOD_RECIPE_H
#define CFOOD_RECIPE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct Recipe *Recipe;

Recipe
create_new_recipe(int id, char *name, char *steps[], int num_of_steps, int ingredients[], int ingredient_amounts[],
                  int num_of_ingredients);

void delete_recipe(Recipe *recipe);

bool recipe_get_id(Recipe recipe, int *result);

bool recipe_get_name(Recipe recipe, char *result, int result_len);

bool recipe_get_ingredients(Recipe recipe, int *result, int result_len);

bool recipe_get_ingredients_amounts(Recipe recipe, int *result, int result_len);

bool recipe_get_num_of_ingredients(Recipe recipe, int *result);

void recipe_print_steps(Recipe recipe);

void save_recipe(Recipe recipe, FILE *f);

Recipe restore_recipe(FILE *f);

#endif //CFOOD_RECIPE_H
