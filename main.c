#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>
#include "ingredient_service_controller.h"
#include "input.h"

static void manage_ingredients_handler(IngredientService ingredient_service);

int main() {
    IngredientService ingredient_service = new_ingredient_service("./ingredient_service.bin");

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
