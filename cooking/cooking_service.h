//
// Created by dawids21 on 5/19/21.
//

#ifndef CFOOD_COOKING_SERVICE_H
#define CFOOD_COOKING_SERVICE_H

#include <stdbool.h>
#include <recipe_service.h>
#include <ingredient_service.h>

typedef struct CookingService *CookingService;

CookingService new_cooking_service(IngredientService ingredient_service, RecipeService recipe_service);

void delete_cooking_service(CookingService service);

bool cooking_service_prepare(CookingService service, int recipe_id);

#endif //CFOOD_COOKING_SERVICE_H
