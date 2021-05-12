#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>
#include <unistd.h>
#include <recipe_service.h>
#include <recommendation_service.h>
#include "ingredient_service_controller.h"
#include "input.h"
#include "recipe_service_controller.h"
#include "recommendation_service_controller.h"

static void main_console();

static void manage_ingredients_handler(IngredientService ingredient_service, RecipeService recipe_service);

static void manage_recipe_handler(RecipeService recipe_service, IngredientService ingredient_service);

static void recommendation_handler(RecommendationService recommendation_service, RecipeService recipe_service);

#define INGREDIENT_SERVICE_FILENAME "./ingredient_service.bin"
#define RECIPE_SERVICE_FILENAME "./recipe_service.bin"

int main() {
    main_console();

    return 0;
}

static void main_console() {

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

    RecommendationService recommendation_service = new_recommendation_service(recipe_service, ingredient_service);

    while (true) {
        printf("***** CFood *****\n");
        printf("-----------------\n");
        printf("1. Recommendations\n");
        printf("2. Manage ingredients\n");
        printf("3. Manage recipes\n");
        printf("4. Exit program\n");
        printf("Choose option: ");
        char option;
        input_char(&option);
        if (option == '1') {
            recommendation_handler(recommendation_service, recipe_service);
        } else if (option == '2') {
            manage_ingredients_handler(ingredient_service, recipe_service);
        } else if (option == '3') {
            manage_recipe_handler(recipe_service, ingredient_service);
        } else if (option == '4') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }

    delete_recommendation_service(recommendation_service);

    save_recipe_service(recipe_service);
    delete_recipe_service(recipe_service);

    save_ingredient_service(ingredient_service);
    delete_ingredient_service(ingredient_service);
}

static void manage_ingredients_handler(IngredientService ingredient_service, RecipeService recipe_service) {
    while (true) {
        ingredient_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '4') {
            ingredient_service_handle_option(option, ingredient_service, recipe_service);
        } else if (option == '5') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void manage_recipe_handler(RecipeService recipe_service, IngredientService ingredient_service) {
    while (true) {
        recipe_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '4') {
            recipe_service_handle_option(option, recipe_service, ingredient_service);
        } else if (option == '5') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void recommendation_handler(RecommendationService recommendation_service, RecipeService recipe_service) {
    while (true) {
        recommendation_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '2') {
            recommendation_service_handle_option(option, recommendation_service, recipe_service);
        } else if (option == '3') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}
