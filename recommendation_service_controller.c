//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service_controller.h"
#include "input.h"

static void get_recommendations(RecommendationService service);

static void try_something_new(RecommendationService service);

static void print_recommendation_menu();

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
    int num_of_available_recipes = get_number_of_available_recipes(service);
    if (num_of_available_recipes <= 0) {
        printf("No available recipes");
        return;
    }
    int id_recipes[num_of_available_recipes];
    get_available_recipes(service, id_recipes, num_of_available_recipes);
    int current = 0;
    int run = 1;
    while (run) {
        char option;
        input_char(&option);
        print_recommendation_menu();
        switch (option) {
            case '1':
                //TODO
                run = 0;
                break;
            case '2':
                current = (current + 1) % num_of_available_recipes;
                break;
            case '3':
                run = 0;
                break;
            default:
                printf("Unknown option\n");
                break;
        }
    }
}

static void try_something_new(RecommendationService service) {
    //TODO
}

static void print_recommendation_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. Prepare meal (not implemented yet)\n");
    printf("2. Next (not implemented yet)\n");
    printf("3. Return\n");
    printf("Choose option: ");
}
