//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_H
#define CFOOD_RECIPE_SERVICE_H

typedef struct RecipeService *RecipeService;

RecipeService new_recipe_service(char *filename, IngredientService ingredientService);

void delete_recipe_service(RecipeService service);

int get_num_of_recipes(RecipeService service);

bool add_recipe(RecipeService service, char *name, char *steps[], int num_of_steps, int ingredients[],
                int num_of_ingredients);

#endif //CFOOD_RECIPE_SERVICE_H
