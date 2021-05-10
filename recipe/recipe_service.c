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

bool add_recipe(RecipeService service, char *name, char *steps[], int num_of_steps, RecipeIngredient ingredients[],
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

bool remove_recipe_with_ingredient_id(RecipeService service, int ingredient_id) {
    if (service == NULL) {
        return false;
    }
    int num_of_recipes = get_num_of_recipes(service);
    ArrayItem recipes[num_of_recipes];
    get_all_items(service->recipes, recipes);

    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe recipe = recipes[i].recipe_item;
        int num_of_ingredients;
        recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
        RecipeIngredient ingredients[num_of_ingredients];
        recipe_get_ingredients(recipe, ingredients, num_of_ingredients);
        for (int j = 0; j < num_of_ingredients; ++j) {
            if (ingredients[i]->id == ingredient_id) {
                delete_recipe(&recipe);
                break;
            }
        }
    }
    return true;
}

void save_recipe_service(RecipeService service) {
    if (strlen(service->filename) == 0) {
        return;
    }

    FILE *f = fopen(service->filename, "wb");

    const int size = get_size(service->recipes);
    fwrite(&size, sizeof(int), 1, f);
    fwrite(&service->id_recipes, sizeof(int), 1, f);
    ArrayItem items[size];
    get_all_items(service->recipes, items);

    for (int i = 0; i < size; i++) {
        save_recipe(items[i].recipe_item, f);
    }
    fclose(f);
}

RecipeService restore_recipe_service(char *filename, IngredientService ingredient_service) {
    RecipeService service = new_recipe_service(filename, ingredient_service);
    FILE *f = fopen(service->filename, "rb");
    int size;
    fread(&size, sizeof(int), 1, f);
    fread(&service->id_recipes, sizeof(int), 1, f);

    for (int i = 0; i < size; ++i) {
        Recipe recipe = restore_recipe(f);
        ArrayItem item = {.recipe_item = recipe};
        append(service->recipes, item);
    }

    fclose(f);
    return service;
}

static bool check_if_recipe_is_possible(RecipeService service, Recipe recipe) {
    int num_of_ingredients;
    recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
    RecipeIngredient ingredients[num_of_ingredients];
    recipe_get_ingredients(recipe, ingredients, num_of_ingredients);

    for (int i = 0; i < num_of_ingredients; ++i) {
        RecipeIngredient recipe_ingredient = ingredients[i];
        IngredientReadModel ingredient;
        get_ingredient_by_id(service->ingredientService, recipe_ingredient->id, &ingredient);
        if (ingredient.amount < recipe_ingredient->amount) {
            return false;
        }
    }
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