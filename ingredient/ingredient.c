//
// Created by dawids21 on 4/28/21.
//

#include <stdlib.h>
#include "ingredient.h"

typedef enum {
    Solid,
    Liquid,
} IngredientType;

typedef struct {
    char *name;
    int amount;
    IngredientType type;
} Ingredient;

struct IngredientService {

};

IngredientService newIngredientService() {
    IngredientService service = (IngredientService) malloc(sizeof(struct IngredientService));
    return service;
}

void deleteIngredientService(IngredientService service) {
    free(service);
}