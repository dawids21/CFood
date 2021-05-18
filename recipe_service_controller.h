//
// Created by dawids21 on 5/10/21.
//

#ifndef CFOOD_RECIPE_SERVICE_CONTROLLER_H
#define CFOOD_RECIPE_SERVICE_CONTROLLER_H

#include <recipe_service.h>
#include <gtk/gtk.h>
#include "app.h"

void recipe_service_register_callbacks(GtkBuilder *builder);

void recipe_service_init_list_store(App *app);

#endif //CFOOD_RECIPE_SERVICE_CONTROLLER_H
