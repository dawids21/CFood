//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_H
#define CFOOD_RECIPE_SERVICE_H

typedef struct RecipeService *RecipeService;

#define MAX_RECIPE_NAME_LEN 100
#define MAX_NUM_OF_STEPS 20
#define MAX_LEN_OF_STEP 100
#define MAX_NUM_OF_INGREDIENTS 20

typedef struct {
    int id;
    char name[MAX_RECIPE_NAME_LEN];
    char steps[MAX_NUM_OF_STEPS][MAX_LEN_OF_STEP];
    int num_of_steps;
    int ingredients[MAX_NUM_OF_INGREDIENTS];
    int num_of_ingredients;
} RecipeReadModel;

RecipeService new_recipe_service(char *filename, IngredientService ingredientService);

void delete_recipe_service(RecipeService service);

int get_num_of_recipes(RecipeService service);

bool add_recipe(RecipeService service, char *name, char *steps[], int num_of_steps, int ingredients[],
                int num_of_ingredients);

void get_all_recipes(RecipeService service, RecipeReadModel *result);

#endif //CFOOD_RECIPE_SERVICE_H
