//
// Created by dawids21 on 5/10/21.
//

#include <array.h>
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
        recipe_get_num_of_uses(current, &(result[i].num_of_uses));
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
    delete_recipe(&deleted.recipe_item);
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
            if (ingredients[j]->id == ingredient_id) {
                int id;
                recipe_get_id(recipe, &id);
                remove_recipe(service, id);
                break;
            }
        }
    }
    return true;
}

void print_detailed_info_about_recipe(RecipeService service, int id) {
    int index = find_index_by_id(service, id);
    if (index == -1) {
        printf("Recipe not found\n");
        return;
    }

    ArrayItem item;
    get(service->recipes, index, &item);
    Recipe recipe = item.recipe_item;

    char name[MAX_RECIPE_NAME_LEN];
    recipe_get_name(recipe, name, MAX_RECIPE_NAME_LEN);

    int num_of_ingredients;
    recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
    RecipeIngredient recipe_ingredients[num_of_ingredients];
    recipe_get_ingredients(recipe, recipe_ingredients, num_of_ingredients);
    IngredientReadModel ingredients[num_of_ingredients];
    for (int i = 0; i < num_of_ingredients; ++i) {
        get_ingredient_by_id(service->ingredientService, recipe_ingredients[i]->id, &ingredients[i]);
    }

    int num_of_uses;
    recipe_get_num_of_uses(recipe, &num_of_uses);

    printf("Name: %s\n", name);
    printf("Number of usage: %d\n", num_of_uses);
    printf("\nIngredients\n");
    for (int i = 0; i < num_of_ingredients; ++i) {
        IngredientReadModel ingredient = ingredients[i];
        if (ingredient.type == SOLID) {
            printf("%d %s\n", recipe_ingredients[i]->amount, ingredient.name);
        } else {
            printf("%d ml %s\n", recipe_ingredients[i]->amount, ingredient.name);
        }
    }
    printf("\nSteps\n");
    recipe_print_steps(recipe);
}

bool remove_ingredients_from_recipe(RecipeService service, int id) {
    if (service == NULL) {
        return false;
    }

    int index = find_index_by_id(service, id);

    if (index == -1) {
        return false;
    }

    ArrayItem recipeItem;
    get(service->recipes, index, &recipeItem);
    Recipe recipe = recipeItem.recipe_item;

    int num_of_ingredients;
    recipe_get_num_of_ingredients(recipe, &num_of_ingredients);
    RecipeIngredient ingredients[num_of_ingredients];
    recipe_get_ingredients(recipe, ingredients, num_of_ingredients);

    for (int i = 0; i < num_of_ingredients; ++i) {
        RecipeIngredient ingredient = ingredients[i];
        reduce_amount_of_ingredient(service->ingredientService, ingredient->id, ingredient->amount);
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