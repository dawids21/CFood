//
// Created by dawids21 on 4/28/21.
//

#include <array.h>
#include "ingredient.h"

typedef enum {
    Solid,
    Liquid,
} IngredientType;

struct Ingredient {
    char *name;
    int amount;
    IngredientType type;
};

struct IngredientService {
    Array ingredients;
};

IngredientService new_ingredient_service() {
    IngredientService service = (IngredientService) malloc(sizeof(struct IngredientService));
    return service;
}

void delete_ingredient_service(IngredientService service) {
    free(service);
}