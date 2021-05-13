//
// Created by dawids21 on 5/3/21.
//

#ifndef CFOOD_INGREDIENT_SERVICE_CONTROLLER_H
#define CFOOD_INGREDIENT_SERVICE_CONTROLLER_H

#include <ingredient_service.h>
#include <gtk/gtk.h>
#include "app.h"

void ingredient_service_display_main_menu();

void ingredient_service_handle_option(char option, IngredientService service, RecipeService recipe_service);

void ingredient_service_register_callbacks(GtkBuilder *builder);

#endif //CFOOD_INGREDIENT_SERVICE_CONTROLLER_H
