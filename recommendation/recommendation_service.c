//
// Created by dawids21 on 5/11/21.
//

#include <recipe_service.h>
#include <ingredient_service.h>
#include "recommendation_service.h"

struct RecommendationService {
    RecipeService recipe_service;
    IngredientService ingredient_service;
};
