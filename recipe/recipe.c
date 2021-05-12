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
    RecipeIngredient *ingredients;
    int num_of_ingredients;
    int num_of_uses;
};

Recipe
create_new_recipe(int id, char *name, char *steps[], int num_of_steps, RecipeIngredient ingredients[],
                  int num_of_ingredients) {
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

    recipe->ingredients = malloc(num_of_ingredients * sizeof(RecipeIngredient));
    for (int i = 0; i < num_of_ingredients; ++i) {
        recipe->ingredients[i] = malloc(sizeof(struct RecipeIngredient));
        memcpy(recipe->ingredients[i], ingredients[i], sizeof(struct RecipeIngredient));
    }

    recipe->num_of_ingredients = num_of_ingredients;

    recipe->num_of_uses = 0;

    return recipe;
}

void delete_recipe(Recipe *recipe) {
    for (int i = 0; i < (*recipe)->num_of_ingredients; ++i) {
        free((*recipe)->ingredients[i]);
    }
    free((*recipe)->ingredients);

    for (int i = 0; i < (*recipe)->num_of_steps; ++i) {
        free((*recipe)->steps[i]);
    }
    free((*recipe)->steps);
    free((*recipe)->name);
    free(*recipe);
    *recipe = NULL;
}

bool recipe_get_id(Recipe recipe, int *result) {
    if (recipe == NULL || result == false) {
        return false;
    }
    *result = recipe->id;
    return true;
}

bool recipe_get_name(Recipe recipe, char *result, int result_len) {
    if (recipe == NULL || result == false) {
        return false;
    }
    strncpy(result, recipe->name, result_len);
    return true;
}

bool recipe_get_ingredients(Recipe recipe, RecipeIngredient *result, int result_len) {
    if (recipe == NULL || result == NULL) {
        return false;
    }

    size_t bytes_to_copy =
            (result_len < recipe->num_of_ingredients ? result_len : recipe->num_of_ingredients) *
            sizeof(struct RecipeIngredient);

    memcpy(result, recipe->ingredients, bytes_to_copy);
    return true;
}

bool recipe_get_num_of_ingredients(Recipe recipe, int *result) {
    if (recipe == NULL || result == NULL) {
        return false;
    }
    *result = recipe->num_of_ingredients;
    return true;
}

void recipe_print_steps(Recipe recipe) {
    for (int i = 0; i < recipe->num_of_steps; ++i) {
        printf("%d. %s\n", i + 1, recipe->steps[i]);
    }
}

bool recipe_get_num_of_uses(Recipe recipe, int *result) {
    if (recipe == NULL || result == NULL) {
        return false;
    }
    *result = recipe->num_of_uses;
    return true;
}

void recipe_increase_num_of_uses(Recipe recipe) {
    recipe->num_of_uses++;
}

void recipe_reset_num_of_uses(Recipe recipe) {
    recipe->num_of_uses = 0;
}

void recipe_create_read_model(Recipe recipe, RecipeReadModel *result) {
    result->id = recipe->id;
    result->name = recipe->name;
    result->num_of_ingredients = recipe->num_of_ingredients;
    result->num_of_steps = recipe->num_of_steps;
    result->num_of_uses = recipe->num_of_uses;
    result->ingredients = recipe->ingredients;
    result->steps = recipe->steps;
}

void save_recipe(Recipe recipe, FILE *f) {
    fwrite(&recipe->id, sizeof(int), 1, f);

    size_t name_len = strlen(recipe->name) + 1;
    fwrite(&name_len, sizeof(size_t), 1, f);
    fwrite(recipe->name, sizeof(char), name_len, f);

    fwrite(&recipe->num_of_steps, sizeof(int), 1, f);

    for (int i = 0; i < recipe->num_of_steps; ++i) {
        size_t step_len = strlen(recipe->steps[i]) + 1;
        fwrite(&step_len, sizeof(size_t), 1, f);
        fwrite(recipe->steps[i], sizeof(char), step_len, f);
    }

    fwrite(&recipe->num_of_ingredients, sizeof(int), 1, f);
    for (int i = 0; i < recipe->num_of_ingredients; ++i) {
        fwrite(recipe->ingredients[i], sizeof(struct RecipeIngredient), 1, f);
    }

    fwrite(&recipe->num_of_uses, sizeof(int), 1, f);
}

Recipe restore_recipe(FILE *f) {
    int id;
    fread(&id, sizeof(int), 1, f);

    size_t name_len;
    fread(&name_len, sizeof(size_t), 1, f);
    char name[name_len];
    fread(name, sizeof(char), name_len, f);

    int num_of_steps;
    fread(&num_of_steps, sizeof(int), 1, f);

    char *steps[num_of_steps];
    for (int i = 0; i < num_of_steps; ++i) {
        size_t step_len;
        fread(&step_len, sizeof(size_t), 1, f);
        steps[i] = malloc(sizeof(char) * step_len);
        fread(steps[i], sizeof(char), step_len, f);
    }

    int num_of_ingredients;
    fread(&num_of_ingredients, sizeof(int), 1, f);
    RecipeIngredient ingredients[num_of_ingredients];
    for (int i = 0; i < num_of_ingredients; ++i) {
        ingredients[i] = malloc(sizeof(struct RecipeIngredient));
        fread(ingredients[i], sizeof(struct RecipeIngredient), 1, f);
    }

    Recipe recipe = create_new_recipe(id, name, steps, num_of_steps, ingredients, num_of_ingredients);

    fread(&recipe->num_of_uses, sizeof(int), 1, f);

    for (int i = 0; i < num_of_steps; ++i) {
        free(steps[i]);
    }

    for (int i = 0; i < num_of_ingredients; ++i) {
        free(ingredients[i]);
    }
    return recipe;
}