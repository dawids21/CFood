//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service.h"
#include "recipe.h"

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

void delete_recommendation_service(RecommendationService service) {
    free(service);
}

void get_available_recipes(RecommendationService service, int *result, int result_len) {
    int num_of_recipes = get_num_of_recipes(service->recipe_service);
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service->recipe_service, recipes);
    int result_index = 0;
    for (int i = 0; i < result_len && i < num_of_recipes; ++i) {
        if (check_if_recipe_is_possible(service->recipe_service, recipes[i].id)) {
            result[result_index++] = recipes[i].id;
        }
    }
}

int get_number_of_available_recipes(RecommendationService service) {
    int num_of_recipes = get_num_of_recipes(service->recipe_service);
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service->recipe_service, recipes);
    int result = 0;
    for (int i = 0; i < num_of_recipes; ++i) {
        if (check_if_recipe_is_possible(service->recipe_service, recipes[i].id)) {
            result++;
        }
    }
    return result;
}

void get_unused_available_recipes(RecommendationService service, int *result, int result_len) {
    int num_of_recipes = get_num_of_recipes(service->recipe_service);
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service->recipe_service, recipes);
    int result_index = 0;
    for (int i = 0; i < result_len && i < num_of_recipes; ++i) {
        if (check_if_recipe_is_possible(service->recipe_service, recipes[i].id) && recipes[i].num_of_uses == 0) {
            result[result_index++] = recipes[i].id;
        }
    }
}

int get_number_of_unused_available_recipes(RecommendationService service) {
    int num_of_recipes = get_num_of_recipes(service->recipe_service);
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service->recipe_service, recipes);
    int result = 0;
    for (int i = 0; i < num_of_recipes; ++i) {
        if (check_if_recipe_is_possible(service->recipe_service, recipes[i].id) && recipes[i].num_of_uses == 0) {
            result++;
        }
    }
    return result;
}