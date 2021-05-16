//
// Created by dawids21 on 5/12/21.
//

#ifndef CFOOD_APP_H
#define CFOOD_APP_H

#include <gtk/gtk.h>
#include <recommendation_service.h>
#include <recipe_service.h>
#include <ingredient_service.h>

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

    GtkStack *stack_ingredients;
    GtkTreeView *tree_view_ingredients;
    GtkTreeStore *tree_store_ingredients;
    GtkButton *btn_ingredients_list_add;
    GtkButton *btn_ingredients_list_modify;
    GtkButton *btn_ingredients_list_delete;
    GtkEntry *entry_ingredient_form_name;
    GtkSpinButton *entry_ingredient_form_amount;
    GtkRadioButton *entry_ingredient_form_type_solid;
    GtkRadioButton *entry_ingredient_form_type_liquid;
    GtkButton *btn_ingredient_form_cancel;
    GtkStack *stack_ingredient_form_button;
    GtkButton *btn_ingredient_form_add;
    GtkButton *btn_ingredient_form_modify;

    GtkMessageDialog *dialog_delete_ingredient;

    int current_recommendation_index;
} App;

#endif //CFOOD_APP_H
