//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_CONTROLLER_H
#define CFOOD_RECIPE_SERVICE_CONTROLLER_H

#include <recipe_service.h>
#include <gtk/gtk.h>

void recipe_service_display_main_menu();

void recipe_service_handle_option(char option, RecipeService service, IngredientService ingredient_service);

void recipe_service_register_callbacks(GtkBuilder *builder);

#endif //CFOOD_RECIPE_SERVICE_CONTROLLER_H
