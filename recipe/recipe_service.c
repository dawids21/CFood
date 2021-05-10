//
// Created by dawids21 on 5/10/21.
//

#include <array.h>
#include <ingredient_service.h>
#include <string.h>
#include "recipe_service.h"

struct RecipeService {
    int id_recipes;
    Array recipes;
    char *filename;
    IngredientService ingredientService;
};

RecipeService new_recipe_service(char *filename, IngredientService ingredientService) {
    RecipeService service = (RecipeService) malloc(sizeof(struct RecipeService));
    service->id_recipes = 0;
    service->recipes = new_array();
    service->filename = malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(service->filename, filename);
    service->ingredientService = ingredientService;
    return service;
}

void delete_recipe_service(RecipeService service) {
    int num_of_recipes = get_num_of_recipes(service);
    ArrayItem deleted[num_of_recipes];
    delete_array(&(service->recipes), deleted);

    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe to_delete = deleted[i].recipe_item;
        delete_recipe(&to_delete);
    }
    free(service->filename);
    free(service);
}

int get_num_of_recipes(RecipeService service) {
    return get_size(service->recipes);
}

bool add_recipe(RecipeService service, char *name, char *steps[], int num_of_steps, int ingredients[],
                int num_of_ingredients) {
    if (strlen(name) == 0 || num_of_steps <= 0 || num_of_ingredients <= 0) {
        return false;
    }

    ArrayItem to_add = {.recipe_item = create_new_recipe(service->id_recipes++, name, steps, num_of_steps, ingredients,
                                                         num_of_ingredients)};
    append(service->recipes, to_add);
    return true;
}

void get_all_recipes(RecipeService service, RecipeReadModel *result) {
    if (service == NULL || result == NULL) {
        return;
    }

    int num_of_recipes = get_num_of_recipes(service);
    ArrayItem recipes[num_of_recipes];
    get_all_items(service->recipes, recipes);
    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe current = recipes[i].recipe_item;
        recipe_get_id(current, &(result[i].id));
        recipe_get_name(current, result[i].name, MAX_RECIPE_NAME_LEN);
        recipe_get_steps(current, result[i].steps, MAX_NUM_OF_STEPS, MAX_LEN_OF_STEP);
        recipe_get_num_of_steps(current, &(result[i].num_of_steps));
        recipe_get_ingredients(current, result[i].ingredients, MAX_NUM_OF_INGREDIENTS);
        recipe_get_num_of_ingredients(current, &(result[i].num_of_ingredients));
    }
}