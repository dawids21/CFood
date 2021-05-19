//
// Created by dawids21 on 5/11/21.
//

#ifndef CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
#define CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H

#include <recommendation_service.h>
#include <recipe_service.h>
#include <gtk/gtk.h>
#include "app.h"

void recommendation_service_controller_register_callbacks(GtkBuilder *builder);

#endif //CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
