//
// Created by dawids21 on 5/3/21.
//

#ifndef CFOOD_INGREDIENT_SERVICE_CONTROLLER_H
#define CFOOD_INGREDIENT_SERVICE_CONTROLLER_H

#include <ingredient_service.h>
#include <gtk/gtk.h>
#include "app.h"

void ingredient_service_controller_register_callbacks(GtkBuilder *builder);

void ingredient_service_controller_init_tree(App *app);

void ingredient_service_controller_update_ingredient_by_id(App *app, int id);

#endif //CFOOD_INGREDIENT_SERVICE_CONTROLLER_H
