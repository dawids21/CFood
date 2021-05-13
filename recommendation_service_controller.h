//
// Created by dawids21 on 5/11/21.
//

#ifndef CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
#define CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H

#include <recommendation_service.h>
#include <recipe_service.h>
#include <gtk/gtk.h>
#include "app.h"

void recommendation_service_display_main_menu();

void recommendation_service_handle_option(char option, RecommendationService service, RecipeService recipe_service);

void recommendation_service_display_recipe_get_recommendations(int index, App *app);

void recommendation_service_display_recipe_try_something_new(int index, App *app);

void recommendation_service_register_callbacks(GtkBuilder *builder);

#endif //CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
