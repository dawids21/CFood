//
// Created by dawids21 on 5/11/21.
//

#ifndef CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
#define CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H

#include <gtk/gtk.h>
#include "app.h"

void cooking_service_controller_register_callbacks(GtkBuilder *builder);

void cooking_service_controller_display_recipe(App *app);

#endif //CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
