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

void get_available_recipes(RecommendationService service, int *result, int result_len);

int get_number_of_available_recipes(RecommendationService service);

#endif //CFOOD_RECOMMENDATION_SERVICE_H
