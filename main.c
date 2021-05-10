#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>
#include <unistd.h>
#include <recipe_service.h>
#include "ingredient_service_controller.h"
#include "input.h"
#include "recipe_service_controller.h"

static void manage_ingredients_handler(IngredientService ingredient_service);

static void manage_recipe_handler(RecipeService recipe_service);

#define INGREDIENT_SERVICE_FILENAME "./ingredient_service.bin"
#define RECIPE_SERVICE_FILENAME "./recipe_service.bin"

int main() {
    IngredientService ingredient_service;
    if (access(INGREDIENT_SERVICE_FILENAME, F_OK) == 0) {
        ingredient_service = restore_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    } else {
        ingredient_service = new_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    }

    RecipeService recipe_service;
    if (access(RECIPE_SERVICE_FILENAME, F_OK) == 0) {
        recipe_service = restore_recipe_service(RECIPE_SERVICE_FILENAME, ingredient_service);
    } else {
        recipe_service = new_recipe_service(RECIPE_SERVICE_FILENAME, ingredient_service);
    }

    while (true) {
        printf("***** CFood *****\n");
        printf("-----------------\n");
        printf("1. Manage ingredients\n");
        printf("2. Manage recipes\n");
        printf("3. Exit program\n");
        printf("Choose option: ");
        char option;
        input_char(&option);
        if (option == '1') {
            manage_ingredients_handler(ingredient_service);
        } else if (option == '2') {
            manage_recipe_handler(recipe_service);
        } else if (option == '3') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }

    save_recipe_service(recipe_service);
    delete_recipe_service(recipe_service);

    save_ingredient_service(ingredient_service);
    delete_ingredient_service(ingredient_service);
    return 0;
}

static void manage_ingredients_handler(IngredientService ingredient_service) {
    while (true) {
        ingredient_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '4') {
            ingredient_service_handle_option(option, ingredient_service);
        } else if (option == '5') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void manage_recipe_handler(RecipeService recipe_service) {
    while (true) {
        recipe_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '3') {
            recipe_service_handle_option(option, recipe_service);
        } else if (option == '4') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}
