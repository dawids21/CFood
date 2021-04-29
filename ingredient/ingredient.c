//
// Created by dawids21 on 4/28/21.
//

#include <stdlib.h>
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

};

IngredientService newIngredientService() {
    IngredientService service = (IngredientService) malloc(sizeof(struct IngredientService));
    return service;
}

void deleteIngredientService(IngredientService service) {
    free(service);
}

size_t get_size_of_ingredient_type() {
    return sizeof(struct Ingredient);
}