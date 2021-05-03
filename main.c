#include <stdio.h>
#include <ingredient_service.h>

int main() {
    IngredientService ingredient_service = new_ingredient_service();

    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. Manage ingredients");
    printf("2. Exit program");

    delete_ingredient_service(ingredient_service);
    return 0;
}

static void manage_ingredients_handler(IngredientService ingredient_service) {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all ingredients");
    printf("2. Add new ingredient");
    printf("3. Modify existing ingredient");
    printf("4. Delete existing ingredient");
}