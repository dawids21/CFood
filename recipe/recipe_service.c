//
// Created by dawids21 on 5/10/21.
//

#include <array.h>
#include <ingredient_service.h>
#include <string.h>
#include "recipe_service.h"

struct RecipeService {
    int id_recipes;
    Array recipes;
    char *filename;
    IngredientService ingredientService;
};

RecipeService new_recipe_service(char *filename, IngredientService ingredientService) {
    RecipeService service = (RecipeService) malloc(sizeof(struct RecipeService));
    service->id_recipes = 0;
    service->recipes = new_array();
    service->filename = malloc(sizeof(char) * (strlen(filename) + 1));
    strcpy(service->filename, filename);
    service->ingredientService = ingredientService;
    return service;
}

void delete_recipe_service(RecipeService service) {
    int num_of_recipes = get_num_of_recipes(service);
    ArrayItem deleted[num_of_recipes];
    delete_array(&(service->recipes), deleted);

    for (int i = 0; i < num_of_recipes; ++i) {
        Recipe to_delete = deleted[i].recipe_item;
        delete_recipe(&to_delete);
    }
    free(service->filename);
    free(service);
}

int get_num_of_recipes(RecipeService service) {
    return get_size(service->recipes);
}
