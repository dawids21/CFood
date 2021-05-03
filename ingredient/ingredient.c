//
// Created by dawids21 on 4/28/21.
//

#include "ingredient.h"

typedef enum {
    Solid,
    Liquid,
} IngredientType;

struct Ingredient {
    int id;
    char *name;
    int amount;
    IngredientType type;
};
