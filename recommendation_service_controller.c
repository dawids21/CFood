//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service_controller.h"
#include "input.h"

static void get_recommendations(RecommendationService service, RecipeService recipe_service);

static void try_something_new(RecommendationService service, RecipeService recipe_service);

static void print_recommendation_menu();

static void remove_widget_from_list(GtkWidget *widget, gpointer list);

// callbacks
static void on_btn_try_something_new_next_clicked(GtkButton *button, App *app);

static void on_btn_try_something_new_prepare_clicked(GtkButton *button, App *app);

static void on_btn_get_recommendations_next_clicked(GtkButton *button, App *app);

static void on_btn_get_recommendations_prepare_clicked(GtkButton *button, App *app);

static void on_btn_stack_recommendations_get_recommendations_clicked(GtkButton *button, App *app);

static void on_btn_stack_recommendations_try_something_new_clicked(GtkButton *button, App *app);


void recommendation_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. Get recommendations\n");
    printf("2. Try something new\n");
    printf("3. Return\n");
    printf("Choose option: ");
}

void recommendation_service_handle_option(char option, RecommendationService service, RecipeService recipe_service) {

    switch (option) {
        case '1':
            get_recommendations(service, recipe_service);
            break;
        case '2':
            try_something_new(service, recipe_service);
            break;
        default:
            break;
    }
    printf("\n");
}

void recommendation_service_display_recipe_get_recommendations(int index, App *app) {

    int num_of_recipes = get_number_of_available_recipes(app->recommendation_service);
    if (num_of_recipes <= 0) {
        //TODO
        return;
    }
    if (index >= num_of_recipes) {
        index = 0;
        app->current_recommendation_index = 0;
    }
    int id_recipes[num_of_recipes];
    get_available_recipes(app->recommendation_service, id_recipes, num_of_recipes);
    RecipeReadModel recipe;
    get_recipe_by_id(app->recipe_service, id_recipes[index], &recipe);

    gtk_label_set_text(app->lbl_get_recommendations_recipe_name, recipe.name);

    gchar *num_of_uses = g_strdup_printf("Number of uses: %d", recipe.num_of_uses);
    gtk_label_set_text(app->lbl_get_recommendations_num_of_uses, num_of_uses);
    g_free(num_of_uses);

    gtk_container_foreach(GTK_CONTAINER(app->list_get_recommendations_ingredients), remove_widget_from_list,
                          app->list_get_recommendations_ingredients);

    if (recipe.num_of_ingredients > 0) {
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_get_recommendations_ingredients), NULL);
    } else {
        GtkWidget *lbl_placeholder = gtk_label_new("No ingredients");
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_get_recommendations_ingredients),
                                     lbl_placeholder);
    }

    for (int i = 0; i < recipe.num_of_ingredients; ++i) {
        IngredientReadModel ingredient;
        get_ingredient_by_id(app->ingredient_service, recipe.ingredients[i]->id, &ingredient);
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *ingredient_text;
        if (ingredient.type == SOLID) {
            ingredient_text = g_strdup_printf("%d %s", ingredient.amount, ingredient.name);
        } else {
            ingredient_text = g_strdup_printf("%d ml %s", ingredient.amount, ingredient.name);
        }
        GtkWidget *lbl_ingredient = gtk_label_new(ingredient_text);
        gtk_label_set_xalign(GTK_LABEL(lbl_ingredient), 0);
        g_free(ingredient_text);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_ingredient);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_get_recommendations_ingredients), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_get_recommendations_ingredients));

    gtk_container_foreach(GTK_CONTAINER(app->list_get_recommendations_steps), remove_widget_from_list,
                          app->list_get_recommendations_steps);

    if (recipe.num_of_steps > 0) {
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_get_recommendations_steps), NULL);
    } else {
        GtkWidget *lbl_placeholder = gtk_label_new("No steps");
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_get_recommendations_steps),
                                     lbl_placeholder);
    }

    for (int i = 0; i < recipe.num_of_steps; ++i) {
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *step;
        step = g_strdup_printf("%d. %s", i + 1, recipe.steps[i]);
        GtkWidget *lbl_step = gtk_label_new(step);
        gtk_label_set_xalign(GTK_LABEL(lbl_step), 0);
        g_free(step);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_step);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_get_recommendations_steps), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_get_recommendations_steps));
}

void recommendation_service_display_recipe_try_something_new(int index, App *app) {
    int num_of_recipes = get_number_of_unused_available_recipes(app->recommendation_service);
    if (num_of_recipes <= 0) {
        //TODO
        return;
    }
    if (index >= num_of_recipes) {
        index = 0;
        app->current_recommendation_index = 0;
    }
    int id_recipes[num_of_recipes];
    get_unused_available_recipes(app->recommendation_service, id_recipes, num_of_recipes);
    RecipeReadModel recipe;
    get_recipe_by_id(app->recipe_service, id_recipes[index], &recipe);

    gtk_label_set_text(app->lbl_try_something_new_recipe_name, recipe.name);

    gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_ingredients), remove_widget_from_list,
                          app->list_try_something_new_ingredients);

    if (recipe.num_of_ingredients > 0) {
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_try_something_new_ingredients), NULL);
    } else {
        GtkWidget *lbl_placeholder = gtk_label_new("No ingredients");
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_try_something_new_ingredients),
                                     lbl_placeholder);
    }

    for (int i = 0; i < recipe.num_of_ingredients; ++i) {
        IngredientReadModel ingredient;
        get_ingredient_by_id(app->ingredient_service, recipe.ingredients[i]->id, &ingredient);
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *ingredient_text;
        if (ingredient.type == SOLID) {
            ingredient_text = g_strdup_printf("%d %s", ingredient.amount, ingredient.name);
        } else {
            ingredient_text = g_strdup_printf("%d ml %s", ingredient.amount, ingredient.name);
        }
        GtkWidget *lbl_ingredient = gtk_label_new(ingredient_text);
        gtk_label_set_xalign(GTK_LABEL(lbl_ingredient), 0);
        g_free(ingredient_text);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_ingredient);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_try_something_new_ingredients), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_try_something_new_ingredients));

    gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_steps), remove_widget_from_list,
                          app->list_try_something_new_steps);

    if (recipe.num_of_steps > 0) {
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_try_something_new_steps), NULL);
    } else {
        GtkWidget *lbl_placeholder = gtk_label_new("No steps");
        gtk_list_box_set_placeholder(GTK_LIST_BOX(app->list_try_something_new_steps),
                                     lbl_placeholder);
    }

    for (int i = 0; i < recipe.num_of_steps; ++i) {
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *step;
        step = g_strdup_printf("%d. %s", i + 1, recipe.steps[i]);
        GtkWidget *lbl_step = gtk_label_new(step);
        gtk_label_set_xalign(GTK_LABEL(lbl_step), 0);
        g_free(step);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_step);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_try_something_new_steps), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_try_something_new_steps));
}

void recommendation_service_register_callbacks(GtkBuilder *builder) {

    gtk_builder_add_callback_symbol(builder, "on_btn_try_something_new_next_clicked",
                                    G_CALLBACK(on_btn_try_something_new_next_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_try_something_new_prepare_clicked",
                                    G_CALLBACK(on_btn_try_something_new_prepare_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_get_recommendations_next_clicked",
                                    G_CALLBACK(on_btn_get_recommendations_next_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_get_recommendations_prepare_clicked",
                                    G_CALLBACK(on_btn_get_recommendations_prepare_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_stack_recommendations_get_recommendations_clicked",
                                    G_CALLBACK(on_btn_stack_recommendations_get_recommendations_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_stack_recommendations_try_something_new_clicked",
                                    G_CALLBACK(on_btn_stack_recommendations_try_something_new_clicked));
}

static void get_recommendations(RecommendationService service, RecipeService recipe_service) {
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
        print_detailed_info_about_recipe(recipe_service, id_recipes[current]);
        print_recommendation_menu();
        char option;
        input_char(&option);
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

static void try_something_new(RecommendationService service, RecipeService recipe_service) {
    int num_of_unused_available_recipes = get_number_of_unused_available_recipes(service);
    if (num_of_unused_available_recipes <= 0) {
        printf("No available recipes");
        return;
    }
    int id_recipes[num_of_unused_available_recipes];
    get_available_recipes(service, id_recipes, num_of_unused_available_recipes);
    int current = 0;
    int run = 1;
    while (run) {
        print_detailed_info_about_recipe(recipe_service, id_recipes[current]);
        print_recommendation_menu();
        char option;
        input_char(&option);
        switch (option) {
            case '1':
                //TODO
                run = 0;
                break;
            case '2':
                current = (current + 1) % num_of_unused_available_recipes;
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

static void print_recommendation_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. Prepare meal (not implemented yet)\n");
    printf("2. Next \n");
    printf("3. Return\n");
    printf("Choose option: ");
}

static void remove_widget_from_list(GtkWidget *widget, gpointer list) {
    gtk_container_remove(GTK_CONTAINER(list), widget);
}

static void on_btn_try_something_new_next_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
}

static void on_btn_try_something_new_prepare_clicked(GtkButton *button, App *app) {

}

static void on_btn_get_recommendations_next_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);

}

static void on_btn_get_recommendations_prepare_clicked(GtkButton *button, App *app) {

}

static void on_btn_stack_recommendations_get_recommendations_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "get_recommendations");
}

static void on_btn_stack_recommendations_try_something_new_clicked(GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "try_something_new");
}