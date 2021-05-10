//
// Created by dawids21 on 5/10/21.
//

#include "recipe_service_controller.h"

static void list_recipes(RecipeService service);

static void add_new_recipe(RecipeService service);

static void delete_existing_recipe(RecipeService service);

void recipe_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all recipes\n");
    printf("2. Add new recipe\n");
    printf("3. Delete existing recipe\n");
    printf("4. Return\n");
    printf("Choose option: ");
}

void recipe_service_handle_option(char option, RecipeService service) {
    switch (option) {
        case '1':
            list_recipes(service);
            break;
        case '2':
            add_new_recipe(service);
            break;
        case '3':
            delete_existing_recipe(service);
            break;
        default:
            break;
    }
    printf("\n");
}

static void list_recipes(RecipeService service) {

}

static void add_new_recipe(RecipeService service) {

}

static void delete_existing_recipe(RecipeService service) {

}