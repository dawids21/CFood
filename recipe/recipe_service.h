//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_H
#define CFOOD_RECIPE_SERVICE_H

typedef struct RecipeService *RecipeService;

RecipeService new_recipe_service(char *filename, IngredientService ingredientService);

void delete_recipe_service(RecipeService service);

int get_num_of_recipes(RecipeService service);

#endif //CFOOD_RECIPE_SERVICE_H
