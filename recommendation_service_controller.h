//
// Created by dawids21 on 5/11/21.
//

#ifndef CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
#define CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H

#include <recommendation_service.h>
#include <recipe_service.h>

void recommendation_service_display_main_menu();

void recommendation_service_handle_option(char option, RecommendationService service, RecipeService recipe_service);

#endif //CFOOD_RECOMMENDATION_SERVICE_CONTROLLER_H
