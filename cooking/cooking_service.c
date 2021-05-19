//
// Created by dawids21 on 5/19/21.
//

#include "cooking_service.h"

struct CookingService {
    RecipeService recipe_service;
};

CookingService new_cooking_service(RecipeService recipe_service) {
    CookingService service = malloc(sizeof(struct CookingService));
    service->recipe_service = recipe_service;
    return service;
}

void delete_cooking_service(CookingService service) {
    free(service);
}

bool cooking_service_prepare(CookingService service, int recipe_id) {
    if (!recipe_service_check_if_recipe_is_possible(service->recipe_service, recipe_id)) {
        return false;
    }

    recipe_service_remove_ingredients_from_recipe(service->recipe_service, recipe_id);
    recipe_service_add_use(service->recipe_service, recipe_id);

    return true;
}