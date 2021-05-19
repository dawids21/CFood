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
    GtkEntry *entry_ingredient_form_name;
    GtkSpinButton *entry_ingredient_form_amount;
    GtkRadioButton *entry_ingredient_form_type_solid;
    GtkRadioButton *entry_ingredient_form_type_liquid;
    GtkStack *stack_ingredient_form_button;

    GtkStack *stack_recipes;
    GtkTreeView *tree_view_recipes;
    GtkListStore *list_store_recipes;
    GtkTreeView *tree_view_add_recipe_ingredients;
    GtkTreeView *tree_view_add_recipe_steps;
    GtkListStore *list_store_add_recipe_ingredients;
    GtkListStore *list_store_add_recipe_steps;
    GtkEntry *entry_add_recipe_name;
    GtkLabel *lbl_recipe_details_name;
    GtkLabel *lbl_recipe_details_num_of_uses;
    GtkListBox *list_recipe_details_ingredients;
    GtkListBox *list_recipe_details_steps;

    GtkLabel *lbl_recipe_prepare_name;
    GtkListBox *list_recipe_prepare_ingredients;
    GtkListBox *list_recipe_prepare_steps;

    GtkMessageDialog *dialog_delete_ingredient;
    GtkMessageDialog *dialog_delete_recipe;
    GtkMessageDialog *dialog_insufficient_ingredients;

    int current_recommendation_index;
    int recipe_id_to_prepare;
} App;

#endif //CFOOD_APP_H
