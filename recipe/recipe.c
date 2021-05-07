//
// Created by dawids21 on 5/7/21.
//

#include <malloc.h>
#include <string.h>
#include "recipe.h"

struct Recipe {
    int id;
    char *name;
    char **steps;
    int num_of_steps;
    int *ingredients;
    int num_of_ingredients;
};

Recipe
create_new_recipe(int id, char *name, char *steps[], int num_of_steps, int ingredients[], int num_of_ingredients) {
    Recipe recipe = malloc(sizeof(struct Recipe));

    recipe->id = id;

    recipe->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(recipe->name, name);

    recipe->steps = malloc(sizeof(char *) * num_of_steps);
    for (int i = 0; i < num_of_steps; ++i) {
        recipe->steps[i] = malloc((strlen(steps[i]) + 1) * sizeof(char));
        strcpy(recipe->steps[i], steps[i]);
    }

    recipe->num_of_steps = num_of_steps;

    recipe->ingredients = malloc(num_of_ingredients * sizeof(int));
    for (int i = 0; i < num_of_ingredients; ++i) {
        recipe->ingredients[i] = ingredients[i];
    }

    recipe->num_of_ingredients = num_of_ingredients;

    return recipe;
}

void delete_recipe(Recipe *recipe) {
    free((*recipe)->ingredients);

    for (int i = 0; i < (*recipe)->num_of_steps; ++i) {
        free((*recipe)->steps[i]);
    }
    free((*recipe)->steps);
    free((*recipe)->name);
    free(*recipe);
    *recipe = NULL;
}
