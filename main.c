#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>
#include <unistd.h>
#include "ingredient_service_controller.h"
#include "input.h"

static void manage_ingredients_handler(IngredientService ingredient_service);

#define INGREDIENT_SERVICE_FILENAME "./ingredient_service.bin"

int main() {
    IngredientService ingredient_service;
    if (access(INGREDIENT_SERVICE_FILENAME, F_OK) == 0) {
        ingredient_service = restore_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    } else {
        ingredient_service = new_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    }

    while (true) {
        printf("***** CFood *****\n");
        printf("-----------------\n");
        printf("1. Manage ingredients\n");
        printf("2. Exit program\n");
        printf("Choose option: ");
        char option;
        input_char(&option);
        if (option == '1') {
            manage_ingredients_handler(ingredient_service);
        } else if (option == '2') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }

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
