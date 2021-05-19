//
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include <recipe_service.h>
#include "ingredient_service_controller.h"

static void add_to_tree_store(GtkTreeStore *store, int id, char name[100], int amount, IngredientType type);

static void set_ingredient_in_form(App *app, int id);

// callbacks
static void on_btn_ingredient_form_modify_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_ingredient_form_add_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_ingredient_form_cancel_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_ingredients_list_delete_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_ingredients_list_modify_clicked(__attribute__((unused)) GtkButton *button, App *app);

static void on_btn_ingredients_list_add_clicked(__attribute__((unused)) GtkButton *button, App *app);

void ingredient_service_register_callbacks(GtkBuilder *builder) {
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredient_form_modify_clicked",
                                    G_CALLBACK(on_btn_ingredient_form_modify_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredient_form_add_clicked",
                                    G_CALLBACK(on_btn_ingredient_form_add_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredient_form_cancel_clicked",
                                    G_CALLBACK(on_btn_ingredient_form_cancel_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredients_list_delete_clicked",
                                    G_CALLBACK(on_btn_ingredients_list_delete_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredients_list_modify_clicked",
                                    G_CALLBACK(on_btn_ingredients_list_modify_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_ingredients_list_add_clicked",
                                    G_CALLBACK(on_btn_ingredients_list_add_clicked));
}

void ingredient_service_init_tree(App *app) {
    GtkTreeStore *store = app->tree_store_ingredients;
    int num_of_ingredients = ingredient_service_get_num_of_ingredients(app->ingredient_service);
    IngredientReadModel to_list[num_of_ingredients];
    ingredient_service_get_all_ingredients(app->ingredient_service, to_list);
    for (int i = 0; i < num_of_ingredients; i++) {
        IngredientReadModel current = to_list[i];
        add_to_tree_store(store, current.id, current.name, current.amount, current.type);
    }
}

static void add_to_tree_store(GtkTreeStore *store, int id, char name[100], int amount, IngredientType type) {
    GtkTreeIter iter;
    gtk_tree_store_append(store, &iter, NULL);
    gchar *amount_text;
    if (type == SOLID) {
        amount_text = g_strdup_printf("%d", amount);
    } else {
        amount_text = g_strdup_printf("%d ml", amount);
    }
    gtk_tree_store_set(store, &iter,
                       0, id,
                       1, name,
                       2, amount_text,
                       -1);
    g_free(amount_text);
}

static void set_ingredient_in_form(App *app, int id) {
    IngredientReadModel ingredient;
    ingredient_service_get_ingredient_by_id(app->ingredient_service, id, &ingredient);
    gtk_entry_set_text(app->entry_ingredient_form_name, ingredient.name);
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, ingredient.amount);
    if (ingredient.type == SOLID) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_liquid), true);
    }
}

static void on_btn_ingredient_form_modify_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_ingredients);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected(selection, &model, &iter);
    gint id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    gchar *name = (gchar *) gtk_entry_get_text(app->entry_ingredient_form_name);
    gint amount = gtk_spin_button_get_value_as_int(app->entry_ingredient_form_amount);
    IngredientType type;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid))) {
        type = SOLID;
    } else {
        type = LIQUID;
    }
    ingredient_service_modify_ingredient(app->ingredient_service, id, name, amount, type);
    gchar *amount_text;
    if (type == SOLID) {
        amount_text = g_strdup_printf("%d", amount);
    } else {
        amount_text = g_strdup_printf("%d ml", amount);
    }
    gtk_tree_store_set(app->tree_store_ingredients, &iter, 1, name, 2, amount_text, -1);
    g_free(amount_text);
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
    gtk_entry_set_text(app->entry_ingredient_form_name, "");
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
}

static void on_btn_ingredient_form_add_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gchar *name = (gchar *) gtk_entry_get_text(app->entry_ingredient_form_name);
    gint amount = gtk_spin_button_get_value_as_int(app->entry_ingredient_form_amount);
    IngredientType type;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid))) {
        type = SOLID;
    } else {
        type = LIQUID;
    }
    int id = ingredient_service_add_ingredient(app->ingredient_service, name, amount, type);
    add_to_tree_store(app->tree_store_ingredients, id, name, amount, type);
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
    gtk_entry_set_text(app->entry_ingredient_form_name, "");
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
}

static void on_btn_ingredient_form_cancel_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
}

static void on_btn_ingredients_list_delete_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_ingredients);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        return;
    }

    gtk_tree_model_get(model, &iter, 0, &id, -1);
    int response = gtk_dialog_run(GTK_DIALOG(app->dialog_delete_ingredient));
    gtk_widget_hide(GTK_WIDGET(app->dialog_delete_ingredient));

    if (response != GTK_RESPONSE_OK) {
        return;
    }

    ingredient_service_remove_ingredient(app->ingredient_service, id);

    gtk_tree_store_remove(app->tree_store_ingredients, &iter);
}

static void on_btn_ingredients_list_modify_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gtk_entry_set_text(app->entry_ingredient_form_name, "");
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_ingredients);
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        gint id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        set_ingredient_in_form(app, id);
    } else {
        return;
    }
    gtk_stack_set_visible_child_name(app->stack_ingredient_form_button, "modify");
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_form");
}

static void on_btn_ingredients_list_add_clicked(__attribute__((unused)) GtkButton *button, App *app) {
    gtk_entry_set_text(app->entry_ingredient_form_name, "");
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
    gtk_stack_set_visible_child_name(app->stack_ingredient_form_button, "add");
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_form");
}