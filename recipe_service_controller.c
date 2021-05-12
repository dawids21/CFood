//
// Created by dawids21 on 5/10/21.
//

#include "recipe_service_controller.h"
#include "input.h"
#include "ingredient_service_controller.h"
#include "recipe.h"
#include <stdlib.h>
#include <ingredient_service.h>

static void list_recipes(RecipeService service);

static void print_info_about_recipe(RecipeService service);

static void add_new_recipe(RecipeService service, IngredientService ingredient_service);

static void delete_existing_recipe(RecipeService service);

void recipe_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all recipes\n");
    printf("2. Detailed information about recipe\n");
    printf("3. Add new recipe\n");
    printf("4. Delete existing recipe\n");
    printf("5. Return\n");
    printf("Choose option: ");
}

void recipe_service_handle_option(char option, RecipeService service, IngredientService ingredient_service) {
    switch (option) {
        case '1':
            list_recipes(service);
            break;
        case '2':
            print_info_about_recipe(service);
            break;
        case '3':
            add_new_recipe(service, ingredient_service);
            break;
        case '4':
            delete_existing_recipe(service);
            break;
        default:
            break;
    }
    printf("\n");
}

static void list_recipes(RecipeService service) {
    int num_of_recipes = get_num_of_recipes(service);
    if (num_of_recipes == 0) {
        printf("No recipes\n");
        return;
    }
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service, recipes);
    printf("ID | Name | Is possible? | Number of uses\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < num_of_recipes; i++) {
        RecipeReadModel current = recipes[i];
        printf("%d | %s | %s | %d\n", current.id, current.name, current.is_possible ? "YES" : "NO",
               current.num_of_uses);
    }
}

static void print_info_about_recipe(RecipeService service) {
    list_recipes(service);
    printf("Choose ID: ");
    int id;
    input_integer(&id);
    print_detailed_info_about_recipe(service, id);
}

static void add_new_recipe(RecipeService service, IngredientService ingredient_service) {
    char name[100];
    printf("Name: ");
    input_string(name, 100);

    int num_of_steps;
    printf("Num of steps: ");
    input_integer(&num_of_steps);

    char *steps[num_of_steps];
    for (int i = 0; i < num_of_steps; ++i) {
        steps[i] = malloc(sizeof(char) * 200);
        printf("Step %d: ", i);
        input_string(steps[i], 200);
    }

    ingredient_service_handle_option('1', ingredient_service, service);
    int num_of_ingredients;
    printf("Num of ingredients: ");
    input_integer(&num_of_ingredients);

    RecipeIngredient ingredients[num_of_ingredients];
    for (int i = 0; i < num_of_ingredients; ++i) {
        ingredients[i] = malloc(sizeof(struct RecipeIngredient));
        printf("Ingredient %d id: ", i);
        input_integer(&ingredients[i]->id);
        printf("Ingredient %d amount: ", i);
        input_integer(&ingredients[i]->amount);
    }

    bool success = add_recipe(service, name, steps, num_of_steps, ingredients, num_of_ingredients);
    if (success) {
        printf("Recipe added\n");
    } else {
        printf("Problem with adding recipe\n");
    }
}

static void delete_existing_recipe(RecipeService service) {
    list_recipes(service);
    printf("Choose ID to delete: ");
    int id;
    input_integer(&id);

    bool success = remove_recipe(service, id);
    if (success) {
        printf("Recipe deleted\n");
    } else {
        printf("Problem with deleting recipe\n");
    }
}