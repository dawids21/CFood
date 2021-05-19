//
// Created by dawids21 on 5/11/21.
//

#include "cooking_service_controller.h"

static void remove_widget_from_list(GtkWidget *widget, gpointer list);

// callbacks

static void on_btn_recipe_prepare_done_clicked(GtkButton *button, App *app);

static void on_btn_recipe_prepare_cancel_clicked(GtkButton *button, App *app);

void cooking_service_controller_register_callbacks(GtkBuilder *builder) {
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_prepare_done_clicked",
                                    G_CALLBACK(on_btn_recipe_prepare_done_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_prepare_cancel_clicked",
                                    G_CALLBACK(on_btn_recipe_prepare_cancel_clicked));
}

void cooking_service_controller_display_recipe(App *app) {
    RecipeReadModel recipe;
    recipe_service_get_recipe_by_id(app->recipe_service, app->recipe_id_to_prepare, &recipe);

    gtk_label_set_text(app->lbl_recipe_prepare_name, recipe.name);

    gtk_container_foreach(GTK_CONTAINER(app->list_recipe_prepare_ingredients), remove_widget_from_list,
                          app->list_recipe_prepare_ingredients);

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
        gtk_list_box_insert(GTK_LIST_BOX(app->list_recipe_prepare_ingredients), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_recipe_prepare_ingredients));

    gtk_container_foreach(GTK_CONTAINER(app->list_recipe_prepare_steps), remove_widget_from_list,
                          app->list_recipe_prepare_steps);

    for (int i = 0; i < recipe.num_of_steps; ++i) {
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *step;
        step = g_strdup_printf("%d. %s", i + 1, recipe.steps[i]);
        GtkWidget *lbl_step = gtk_label_new(step);
        gtk_label_set_xalign(GTK_LABEL(lbl_step), 0);
        g_free(step);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_step);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_recipe_prepare_steps), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_recipe_prepare_steps));
}

static void remove_widget_from_list(GtkWidget *widget, gpointer list) {
    gtk_container_remove(GTK_CONTAINER(list), widget);
}

static void on_btn_recipe_prepare_done_clicked(GtkButton *button, App *app) {

}

static void on_btn_recipe_prepare_cancel_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_recipes, "recipes_list");
    gtk_stack_set_visible_child_name(app->stack_main, "recipes");
}