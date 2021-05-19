//
// Created by dawids21 on 5/11/21.
//

#ifndef CFOOD_RECOMMENDATION_SERVICE_H
#define CFOOD_RECOMMENDATION_SERVICE_H

#include <recipe_service.h>
#include <ingredient_service.h>

typedef struct RecommendationService *RecommendationService;

RecommendationService new_recommendation_service(RecipeService recipe_service, IngredientService ingredient_service);

void delete_recommendation_service(RecommendationService service);

void recommendation_service_get_available_recipes(RecommendationService service, int *result, int result_len);

int recommendation_service_get_number_of_available_recipes(RecommendationService service);

void recommendation_service_get_unused_available_recipes(RecommendationService service, int *result, int result_len);

int recommendation_service_get_number_of_unused_available_recipes(RecommendationService service);

#endif //CFOOD_RECOMMENDATION_SERVICE_H
