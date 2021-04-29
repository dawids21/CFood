//
// Created by dawids21 on 4/28/21.
//

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