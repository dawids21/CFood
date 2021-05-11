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

void get_available_recipes(RecommendationService service, int *result, int result_len) {
    int num_of_recipes = get_num_of_recipes(service->recipe_service);
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service->recipe_service, recipes);
    int result_index = 0;
    for (int i = 0; i < result_len && i < num_of_recipes; ++i) {
        if (recipes[i].is_possible) {
            result[result_index++] = recipes[i].id;
        }
    }
}