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

static bool check_if_recipe_is_possible(RecipeService service, Recipe recipe);

static int find_index_by_id(RecipeService service, int id);

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
        result[i].is_possible = check_if_recipe_is_possible(service, current);
    }
}

bool remove_recipe(RecipeService service, int id) {
    if (service == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }

    ArrayItem deleted;
    delete_at_index(service->recipes, index, &deleted);
    delete_ingredient(&deleted.ingredient_item);
    return true;
}

static bool check_if_recipe_is_possible(RecipeService service, Recipe recipe) {
    //TODO
    return true;
}

static int find_index_by_id(RecipeService service, int id) {
    int num_of_items = get_num_of_recipes(service);
    ArrayItem recipes[num_of_items];
    get_all_items(service->recipes, recipes);

    for (int i = 0; i < num_of_items; ++i) {
        int current_id;
        recipe_get_id(recipes[i].recipe_item, &current_id);
        if (current_id == id) {
            return i;
        }
    }

    return -1;
}