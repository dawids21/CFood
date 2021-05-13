//
// Created by dawids21 on 5/12/21.
//

#ifndef CFOOD_APP_H
#define CFOOD_APP_H

#include <gtk/gtk.h>

typedef struct {
    IngredientService ingredient_service;
    RecipeService recipe_service;
    RecommendationService recommendation_service;
    GtkStack *stack_main;
    GtkStack *stack_recommendations;
    GtkLabel *lbl_get_recommendations_recipe_name;
    GtkLabel *lbl_get_recommendations_num_of_uses;
    GtkListBox *list_get_recommendations_ingredients;
    GtkListBox *list_get_recommendations_steps;
    GtkLabel *lbl_try_something_new_recipe_name;
    GtkListBox *list_try_something_new_ingredients;
    GtkListBox *list_try_something_new_steps;

    int current_recommendation_index;
} App;

#endif //CFOOD_APP_H
