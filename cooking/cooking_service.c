//
// Created by dawids21 on 5/19/21.
//

#include "cooking_service.h"

struct CookingService {
    IngredientService ingredient_service;
    RecipeService recipe_service;
};

CookingService new_cooking_service(IngredientService ingredient_service, RecipeService recipe_service) {
    CookingService service = malloc(sizeof(struct CookingService));
    service->ingredient_service = ingredient_service;
    service->recipe_service = recipe_service;
    return service;
}

void delete_cooking_service(CookingService service) {
    free(service);
}

bool cooking_service_prepare(CookingService service, int recipe_id) {
    if (!check_if_recipe_is_possible(service->recipe_service, recipe_id)) {
        return false;
    }

    RecipeReadModel recipe;
    get_recipe_by_id(service->recipe_service, recipe_id, &recipe);

    for (int i = 0; i < recipe.num_of_ingredients; ++i) {
        RecipeIngredient ingredient = recipe.ingredients[i];
        reduce_amount_of_ingredient(service->ingredient_service, ingredient->id,
                                    ingredient->amount);
    }

    recipe_service_add_use(service->recipe_service, recipe_id);

    return true;
}