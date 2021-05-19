//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_CONTROLLER_H
#define CFOOD_RECIPE_SERVICE_CONTROLLER_H

#include <recipe_service.h>
#include <gtk/gtk.h>
#include "app.h"

void recipe_service_controller_register_callbacks(GtkBuilder *builder);

void recipe_service_controller_init_list_store(App *app);

void recipe_service_controller_update_recipe_by_id(App *app, int id);

#endif //CFOOD_RECIPE_SERVICE_CONTROLLER_H
