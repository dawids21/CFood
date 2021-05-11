//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service.h"

struct RecommendationService {
    RecipeService recipe_service;
    IngredientService ingredient_service;
};

RecommendationService new_recommendation_service(RecipeService recipe_service, IngredientService ingredient_service) {
    RecommendationService service = malloc(sizeof(struct RecommendationService));
    service->recipe_service = recipe_service;
    service->ingredient_service = ingredient_service;
    return service;
}

void delete_recommendation_service(RecipeService service) {
    free(service);
}