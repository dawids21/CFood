//
// Created by dawids21 on 5/19/21.
//

#include <recipe_service.h>
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