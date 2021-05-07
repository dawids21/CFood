//
// Created by dawids21 on 5/7/21.
//

#ifndef CFOOD_RECIPE_H
#define CFOOD_RECIPE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct Recipe *Recipe;

Recipe
create_new_recipe(int id, char *name, char *steps[], int num_of_steps, int ingredients[], int num_of_ingredients);

void delete_recipe(Recipe *recipe);

bool get_id(Recipe recipe, int *result);

bool get_name(Recipe recipe, char *result, int result_len);

bool get_ingredients(Recipe recipe, int *result, int result_len);

bool get_num_of_ingredients(Recipe recipe, int *result);

void print_steps(Recipe recipe);

void save_recipe(Recipe recipe, FILE *f);

Recipe restore_recipe(FILE *f);

#endif //CFOOD_RECIPE_H