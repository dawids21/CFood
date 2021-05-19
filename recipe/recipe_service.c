//
// Created by dawids21 on 5/10/21.
//

#include <array.h>
#include <string.h>
#include "recipe_service.h"
#include "recipe.h"

struct RecipeService {
    int id_recipes;
    Array recipes;
    char *filename;
    IngredientService ingredientService;
};

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
    int num_of_recipes = recipe_service_get_num_of_recipes(service);
    ArrayItem deleted[num_of_recipes];
    delete_array(&(service->recipes), deleted);

    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe to_delete = deleted[i].recipe_item;
        delete_recipe(&to_delete);
    }
    free(service->filename);
    free(service);
}

int recipe_service_get_num_of_recipes(RecipeService service) {
    return array_get_size(service->recipes);
}

int recipe_service_add_recipe(RecipeService service, char *name, char **steps, int num_of_steps,
                              RecipeIngredient *ingredients,
                              int num_of_ingredients) {
    if (strlen(name) == 0 || num_of_steps <= 0 || num_of_ingredients <= 0) {
        return -1;
    }

    int id = service->id_recipes;
    ArrayItem to_add = {.recipe_item = create_new_recipe(service->id_recipes++, name, steps, num_of_steps, ingredients,
                                                         num_of_ingredients)};
    array_append(service->recipes, to_add);
    return id;
}

void recipe_service_get_all_recipes(RecipeService service, RecipeReadModel *result) {
    if (service == NULL || result == NULL) {
        return;
    }

    int num_of_recipes = recipe_service_get_num_of_recipes(service);
    ArrayItem recipes[num_of_recipes];
    array_get_all_items(service->recipes, recipes);
    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe current = recipes[i].recipe_item;
        recipe_create_read_model(current, &result[i]);
    }
}

bool recipe_service_get_recipe_by_id(RecipeService service, int id, RecipeReadModel *result) {
    if (service == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }

    ArrayItem item;
    array_get(service->recipes, index, &item);
    Recipe recipe = item.recipe_item;

    recipe_create_read_model(recipe, result);

    return true;
}

bool recipe_service_remove_recipe(RecipeService service, int id) {
    if (service == NULL) {
        return false;
    }
    int index = find_index_by_id(service, id);
    if (index == -1) {
        return false;
    }

    ArrayItem deleted;
    array_delete_at_index(service->recipes, index, &deleted);
    delete_recipe(&deleted.recipe_item);
    return true;
}

bool recipe_service_remove_ingredients_from_recipe(RecipeService service, int id) {
    if (service == NULL) {
        return false;
    }

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem recipeItem;
    array_get(service->recipes, index, &recipeItem);
    Recipe recipe = recipeItem.recipe_item;

    int num_of_ingredients;
    recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
    RecipeIngredient ingredients[num_of_ingredients];
    recipe_get_ingredients(recipe, ingredients, num_of_ingredients);

    for (int i = 0; i < num_of_ingredients; ++i) {
        RecipeIngredient ingredient = ingredients[i];
        ingredient_service_reduce_amount_of_ingredient(service->ingredientService, ingredient->id, ingredient->amount);
    }

    return true;
}

bool recipe_service_check_if_recipe_is_possible(RecipeService service, int id) {

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem recipeItem;
    array_get(service->recipes, index, &recipeItem);
    Recipe recipe = recipeItem.recipe_item;

    int num_of_ingredients;
    recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
    RecipeIngredient ingredients[num_of_ingredients];
    recipe_get_ingredients(recipe, ingredients, num_of_ingredients);

    for (int i = 0; i < num_of_ingredients; ++i) {
        RecipeIngredient recipe_ingredient = ingredients[i];
        IngredientReadModel ingredient;
        ingredient_service_get_ingredient_by_id(service->ingredientService, recipe_ingredient->id, &ingredient);
        if (ingredient.amount < recipe_ingredient->amount) {
            return false;
        }
    }
    return true;
}

void recipe_service_add_use(RecipeService service, int id) {
    int index = find_index_by_id(service, id);

    if (index == -1) {
        return;
    }

    ArrayItem recipeItem;
    array_get(service->recipes, index, &recipeItem);
    Recipe recipe = recipeItem.recipe_item;

    recipe_increase_num_of_uses(recipe);
}

void save_recipe_service(RecipeService service) {
    if (strlen(service->filename) == 0) {
        return;
    }

    FILE *f = fopen(service->filename, "wb");

    const int size = array_get_size(service->recipes);
    fwrite(&size, sizeof(int), 1, f);
    fwrite(&service->id_recipes, sizeof(int), 1, f);
    ArrayItem items[size];
    array_get_all_items(service->recipes, items);

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
        array_append(service->recipes, item);
    }

    fclose(f);
    return service;
}

static int find_index_by_id(RecipeService service, int id) {
    int num_of_items = recipe_service_get_num_of_recipes(service);
    ArrayItem recipes[num_of_items];
    array_get_all_items(service->recipes, recipes);

    for (int i = 0; i < num_of_items; ++i) {
        int current_id;
        recipe_get_id(recipes[i].recipe_item, &current_id);
        if (current_id == id) {
            return i;
        }
    }

    return -1;
}