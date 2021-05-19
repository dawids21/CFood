//
// Created by dawids21 on 5/11/21.
//

#include "recommendation_service_controller.h"

static void recommendation_service_display_recipe_get_recommendations(int index, App *app);

static void recommendation_service_display_recipe_try_something_new(int index, App *app);

static void remove_widget_from_list(GtkWidget *widget, gpointer list);

// callbacks
static void on_btn_try_something_new_next_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_try_something_new_prepare_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_get_recommendations_next_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_get_recommendations_prepare_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void
on_btn_stack_recommendations_get_recommendations_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_stack_recommendations_try_something_new_clicked(__attribute__((unused)) GtkButton *button, App *app);

void recommendation_service_controller_register_callbacks(GtkBuilder *builder) {

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

static void recommendation_service_display_recipe_get_recommendations(int index, App *app) {

    int num_of_recipes = recommendation_service_get_number_of_available_recipes(app->recommendation_service);
    if (num_of_recipes <= 0) {
        gtk_label_set_text(app->lbl_get_recommendations_recipe_name, "No recipes");
        gtk_label_set_text(app->lbl_get_recommendations_num_of_uses, "Number of uses: 0");
        gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_ingredients), remove_widget_from_list,
                              app->list_try_something_new_ingredients);
        gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_steps), remove_widget_from_list,
                              app->list_try_something_new_steps);
        return;
    }
    if (index >= num_of_recipes) {
        index = 0;
        app->current_recommendation_index = 0;
    }
    int id_recipes[num_of_recipes];
    recommendation_service_get_available_recipes(app->recommendation_service, id_recipes, num_of_recipes);
    RecipeReadModel recipe;
    recipe_service_get_recipe_by_id(app->recipe_service, id_recipes[index], &recipe);

    gtk_label_set_text(app->lbl_get_recommendations_recipe_name, recipe.name);

    gchar *num_of_uses = g_strdup_printf("Number of uses: %d", recipe.num_of_uses);
    gtk_label_set_text(app->lbl_get_recommendations_num_of_uses, num_of_uses);
    g_free(num_of_uses);

    gtk_container_foreach(GTK_CONTAINER(app->list_get_recommendations_ingredients), remove_widget_from_list,
                          app->list_get_recommendations_ingredients);

    for (int i = 0; i < recipe.num_of_ingredients; ++i) {
        IngredientReadModel ingredient;
        ingredient_service_get_ingredient_by_id(app->ingredient_service, recipe.ingredients[i]->id, &ingredient);
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *ingredient_text;
        if (ingredient.type == SOLID) {
            ingredient_text = g_strdup_printf("%d %s", recipe.ingredients[i]->amount, ingredient.name);
        } else {
            ingredient_text = g_strdup_printf("%d ml %s", recipe.ingredients[i]->amount, ingredient.name);
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

static void recommendation_service_display_recipe_try_something_new(int index, App *app) {
    int num_of_recipes = recommendation_service_get_number_of_unused_available_recipes(app->recommendation_service);
    if (num_of_recipes <= 0) {
        gtk_label_set_text(app->lbl_get_recommendations_recipe_name, "No recipes");
        gtk_label_set_text(app->lbl_get_recommendations_num_of_uses, "Number of uses: 0");
        gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_ingredients), remove_widget_from_list,
                              app->list_try_something_new_ingredients);
        gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_steps), remove_widget_from_list,
                              app->list_try_something_new_steps);
        return;
    }
    if (index >= num_of_recipes) {
        index = 0;
        app->current_recommendation_index = 0;
    }
    int id_recipes[num_of_recipes];
    recommendation_service_get_unused_available_recipes(app->recommendation_service, id_recipes, num_of_recipes);
    RecipeReadModel recipe;
    recipe_service_get_recipe_by_id(app->recipe_service, id_recipes[index], &recipe);

    gtk_label_set_text(app->lbl_try_something_new_recipe_name, recipe.name);

    gtk_container_foreach(GTK_CONTAINER(app->list_try_something_new_ingredients), remove_widget_from_list,
                          app->list_try_something_new_ingredients);

    for (int i = 0; i < recipe.num_of_ingredients; ++i) {
        IngredientReadModel ingredient;
        ingredient_service_get_ingredient_by_id(app->ingredient_service, recipe.ingredients[i]->id, &ingredient);
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *ingredient_text;
        if (ingredient.type == SOLID) {
            ingredient_text = g_strdup_printf("%d %s", recipe.ingredients[i]->amount, ingredient.name);
        } else {
            ingredient_text = g_strdup_printf("%d ml %s", recipe.ingredients[i]->amount, ingredient.name);
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

static void remove_widget_from_list(GtkWidget *widget, gpointer list) {
    gtk_container_remove(GTK_CONTAINER(list), widget);
}

static void on_btn_try_something_new_next_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
}

static void on_btn_try_something_new_prepare_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_main, "prepare");
}

static void on_btn_get_recommendations_next_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    app->current_recommendation_index++;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);

}

static void on_btn_get_recommendations_prepare_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_main, "prepare");
}

static void
on_btn_stack_recommendations_get_recommendations_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_get_recommendations(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "get_recommendations");
}

static void
on_btn_stack_recommendations_try_something_new_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    app->current_recommendation_index = 0;
    recommendation_service_display_recipe_try_something_new(app->current_recommendation_index, app);
    gtk_stack_set_visible_child_name(app->stack_recommendations, "try_something_new");
}