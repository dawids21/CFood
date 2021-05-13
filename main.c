#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include <ingredient_service.h>
#include <unistd.h>
#include <recipe_service.h>
#include <recommendation_service.h>
#include "ingredient_service_controller.h"
#include "input.h"
#include "recipe_service_controller.h"
#include "recommendation_service_controller.h"
#include "app.h"

static void main_console();

static void manage_ingredients_handler(IngredientService ingredient_service, RecipeService recipe_service);

static void manage_recipe_handler(RecipeService recipe_service, IngredientService ingredient_service);

static void recommendation_handler(RecommendationService recommendation_service, RecipeService recipe_service);

static void main_gtk(int argc, char *argv[]);

#define INGREDIENT_SERVICE_FILENAME "./ingredient_service.bin"
#define RECIPE_SERVICE_FILENAME "./recipe_service.bin"

int main(int argc, char *argv[]) {
//    main_console();
    main_gtk(argc, argv);

    return 0;
}

static void main_console() {

    IngredientService ingredient_service;
    if (access(INGREDIENT_SERVICE_FILENAME, F_OK) == 0) {
        ingredient_service = restore_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    } else {
        ingredient_service = new_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    }

    RecipeService recipe_service;
    if (access(RECIPE_SERVICE_FILENAME, F_OK) == 0) {
        recipe_service = restore_recipe_service(RECIPE_SERVICE_FILENAME, ingredient_service);
    } else {
        recipe_service = new_recipe_service(RECIPE_SERVICE_FILENAME, ingredient_service);
    }

    RecommendationService recommendation_service = new_recommendation_service(recipe_service, ingredient_service);

    while (true) {
        printf("***** CFood *****\n");
        printf("-----------------\n");
        printf("1. Recommendations\n");
        printf("2. Manage ingredients\n");
        printf("3. Manage recipes\n");
        printf("4. Exit program\n");
        printf("Choose option: ");
        char option;
        input_char(&option);
        if (option == '1') {
            recommendation_handler(recommendation_service, recipe_service);
        } else if (option == '2') {
            manage_ingredients_handler(ingredient_service, recipe_service);
        } else if (option == '3') {
            manage_recipe_handler(recipe_service, ingredient_service);
        } else if (option == '4') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }

    delete_recommendation_service(recommendation_service);

    save_recipe_service(recipe_service);
    delete_recipe_service(recipe_service);

    save_ingredient_service(ingredient_service);
    delete_ingredient_service(ingredient_service);
}

static void manage_ingredients_handler(IngredientService ingredient_service, RecipeService recipe_service) {
    while (true) {
        ingredient_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '4') {
            ingredient_service_handle_option(option, ingredient_service, recipe_service);
        } else if (option == '5') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void manage_recipe_handler(RecipeService recipe_service, IngredientService ingredient_service) {
    while (true) {
        recipe_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '4') {
            recipe_service_handle_option(option, recipe_service, ingredient_service);
        } else if (option == '5') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void recommendation_handler(RecommendationService recommendation_service, RecipeService recipe_service) {
    while (true) {
        recommendation_service_display_main_menu();
        char option;
        input_char(&option);
        if (option >= '1' && option <= '2') {
            recommendation_service_handle_option(option, recommendation_service, recipe_service);
        } else if (option == '3') {
            break;
        } else {
            printf("Unknown option\n");
        }
    }
}

static void main_gtk(int argc, char *argv[]) {

    App *app = g_slice_new(App);
    if (access(INGREDIENT_SERVICE_FILENAME, F_OK) == 0) {
        app->ingredient_service = restore_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    } else {
        app->ingredient_service = new_ingredient_service(INGREDIENT_SERVICE_FILENAME);
    }

    if (access(RECIPE_SERVICE_FILENAME, F_OK) == 0) {
        app->recipe_service = restore_recipe_service(RECIPE_SERVICE_FILENAME, app->ingredient_service);
    } else {
        app->recipe_service = new_recipe_service(RECIPE_SERVICE_FILENAME, app->ingredient_service);
    }

    app->recommendation_service = new_recommendation_service(app->recipe_service, app->ingredient_service);

    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, app);

    app->stack_main = GTK_STACK(gtk_builder_get_object(builder, "stack_main"));
    app->stack_recommendations = GTK_STACK(gtk_builder_get_object(builder, "stack_recommendations"));
    app->lbl_get_recommendations_recipe_name = GTK_LABEL(
            gtk_builder_get_object(builder, "lbl_get_recommendations_recipe_name"));
    app->lbl_get_recommendations_num_of_uses = GTK_LABEL(
            gtk_builder_get_object(builder, "lbl_get_recommendations_num_of_uses"));
    app->list_get_recommendations_ingredients = GTK_LIST_BOX(
            gtk_builder_get_object(builder, "list_get_recommendations_ingredients"));
    app->list_get_recommendations_steps = GTK_LIST_BOX(
            gtk_builder_get_object(builder, "list_get_recommendations_steps"));
    app->lbl_try_something_new_recipe_name = GTK_LABEL(
            gtk_builder_get_object(builder, "lbl_try_something_new_recipe_name"));
    app->list_try_something_new_ingredients = GTK_LIST_BOX(
            gtk_builder_get_object(builder, "list_try_something_new_ingredients"));
    app->list_try_something_new_steps = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_try_something_new_steps"));

    app->current_recommendation_index = 0;

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    g_slice_free(App, app);
}

void on_window_main_destroy(GtkWidget *widget, App *app) {
    delete_recommendation_service(app->recommendation_service);

    save_recipe_service(app->recipe_service);
    delete_recipe_service(app->recipe_service);

    save_ingredient_service(app->ingredient_service);
    delete_ingredient_service(app->ingredient_service);
    gtk_main_quit();
}

void on_btn_try_something_new_next_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
}

void on_btn_try_something_new_prepare_clicked(GtkButton *button, App *app) {

}

void on_btn_get_recommendations_next_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);

}

void on_btn_get_recommendations_prepare_clicked(GtkButton *button, App *app) {

}

void on_btn_main_stack_recipes_clicked(GtkButton *button, App *app) {

}

void on_btn_main_stack_ingredients_clicked(GtkButton *button, App *app) {

}

void on_btn_main_stack_recommendations_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_main, "recommendation_stack");
}

void on_btn_stack_recommendations_get_recommendations_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "get_recommendations");
}

void on_btn_stack_recommendations_try_something_new_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "try_something_new");
}