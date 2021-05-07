//
// Created by dawids21 on 5/7/21.
//

#include "recipe.h"

struct Recipe {
    int id;
    char *name;
    char **steps;
    int num_of_steps;
    int *ingredients;
    int num_of_ingredients;
};
