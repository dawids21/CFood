//
// Created by dawids21 on 5/10/21.
//

#include <array.h>
#include <ingredient_service.h>
#include "recipe_service.h"

struct RecipeService {
    int id_recipes;
    Array recipes;
    char *filename;
    IngredientService ingredientService;
};
