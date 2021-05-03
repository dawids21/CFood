//
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include "ingredient_service_controller.h"
#include "input.h"

static void list_ingredients(IngredientService service);

static void add_new_ingredient(IngredientService service);

void ingredient_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all ingredients\n");
    printf("2. Add new ingredient\n");
    printf("3. Modify existing ingredient\n");
    printf("4. Delete existing ingredient\n");
    printf("5. Return\n");
    printf("Choose option: ");
}

void ingredient_service_handle_option(char option, IngredientService service) {

    switch (option) {
        case '1':
            list_ingredients(service);
            break;
        case '2':
            add_new_ingredient(service);
            break;
        case '3':
            break;
        case '4':
            break;
        default:
            break;
    }

}

static void list_ingredients(IngredientService service) {
    int num_of_ingredients = get_num_of_ingredients(service);
    if (num_of_ingredients == 0) {
        printf("No ingredients\n");
        return;
    }
    IngredientReadModel to_list[num_of_ingredients];
    get_all_ingredients(service, to_list);
    printf("ID | Name | Amount\n");
    printf("------------------\n");
    for (int i = 0; i < num_of_ingredients; i++) {
        IngredientReadModel current = to_list[i];
        if (current.type == SOLID) {
            printf("%d | %s | %d\n", current.id, current.name, current.amount);
        } else {
            printf("%d | %s | %d ml\n", current.id, current.name, current.amount);
        }
    }
}

static void add_new_ingredient(IngredientService service) {

    char name[100];
    printf("Name: ");
    input_string(name, 100);

    int amount;
    printf("Amount: ");
    input_integer(&amount);

    char type_letter;
    printf("Type ([S]OLID/[L]IQUID): ");
    input_char(&type_letter);
    IngredientType type = type_letter == 'L' || type_letter == 'l' ? LIQUID : SOLID;

    bool success = add_ingredient(service, name, amount, type);
    if (success) {
        printf("Ingredient added");
    } else {
        printf("Problem with adding ingredient");
    }
}