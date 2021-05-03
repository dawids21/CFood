#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>

static void input_char(char *dest);

static void manage_ingredients_handler(IngredientService ingredient_service);

int main() {
    IngredientService ingredient_service = new_ingredient_service();

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
            printf("Unknown option");
        }
    }

    delete_ingredient_service(ingredient_service);
    return 0;
}

static void input_char(char *dest) {
    char input[3];
    do {
        fgets(input, 3, stdin);
    } while (input[0] == '\n');

    *dest = input[0];
}

static void manage_ingredients_handler(IngredientService ingredient_service) {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all ingredients\n");
    printf("2. Add new ingredient\n");
    printf("3. Modify existing ingredient\n");
    printf("4. Delete existing ingredient\n");
    printf("Choose option: ");
}
