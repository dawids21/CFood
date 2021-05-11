//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service_controller.h"

static void get_recommendations(RecommendationService service);

static void try_something_new(RecommendationService service);

void recommendation_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. Get recommendations\n");
    printf("2. Try something new (not implemented yet)\n");
    printf("3. Return\n");
    printf("Choose option: ");
}

void recommendation_service_handle_option(char option, RecommendationService service) {

    switch (option) {
        case '1':
            get_recommendations(service);
            break;
        case '2':
            try_something_new(service);
            break;
        default:
            break;
    }
    printf("\n");
}

static void get_recommendations(RecommendationService service) {

}

static void try_something_new(RecommendationService service) {
    //TODO
}