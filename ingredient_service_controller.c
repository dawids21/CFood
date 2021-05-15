//
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include <recipe_service.h>
#include <ctype.h>
#include "ingredient_service_controller.h"
#include "input.h"

static void list_ingredients(IngredientService service);

static void add_new_ingredient(IngredientService service);

static void modify_existing_ingredient(IngredientService service);

static void delete_existing_ingredient(IngredientService service, RecipeService recipe_service);

static void add_to_tree_store(GtkTreeStore *store, int id, char name[100], int amount, IngredientType type);

static void set_ingredient_in_form(App *app, int id);

// callbacks
static void on_btn_ingredient_form_modify_clicked(GtkButton *button, App *app);

static void on_btn_ingredient_form_add_clicked(GtkButton *button, App *app);

static void on_btn_ingredient_form_cancel_clicked(GtkButton *button, App *app);

static void on_btn_ingredients_list_delete_clicked(GtkButton *button, App *app);

static void on_btn_ingredients_list_modify_clicked(GtkButton *button, App *app);

static void on_btn_ingredients_list_add_clicked(GtkButton *button, App *app);

void ingredient_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all ingredients\n");
    printf("2. Add new ingredient\n");
    printf("3. Modify existing ingredient\n");
    printf("4. Delete existing ingredient\n");
    printf("5. Return\n");
    printf("Choose option: ");
}

void ingredient_service_handle_option(char option, IngredientService service, RecipeService recipe_service) {

    switch (option) {
        case '1':
            list_ingredients(service);
            break;
        case '2':
            add_new_ingredient(service);
            break;
        case '3':
            modify_existing_ingredient(service);
            break;
        case '4':
            delete_existing_ingredient(service, recipe_service);
            break;
        default:
            break;
    }
    printf("\n");
}

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
    GtkTreeIter iter;
    int num_of_ingredients = get_num_of_ingredients(app->ingredient_service);
    IngredientReadModel to_list[num_of_ingredients];
    get_all_ingredients(app->ingredient_service, to_list);
    for (int i = 0; i < num_of_ingredients; i++) {
        IngredientReadModel current = to_list[i];
        add_to_tree_store(store, current.id, current.name, current.amount, current.type);
    }
}

static void list_ingredients(IngredientService service) {
    int num_of_ingredients = get_num_of_ingredients(service);
    if (num_of_ingredients == 0) {
        printf("No ingredients\n");
        return;
    }
    IngredientReadModel to_list[num_of_ingredients];
    get_all_ingredients(service, to_list);
    printf("ID | Name | Amount\n");
    printf("------------------\n");
    for (int i = 0; i < num_of_ingredients; i++) {
        IngredientReadModel current = to_list[i];
        if (current.type == SOLID) {
            printf("%d | %s | %d\n", current.id, current.name, current.amount);
        } else {
            printf("%d | %s | %d ml\n", current.id, current.name, current.amount);
        }
    }
}

static void add_new_ingredient(IngredientService service) {

    char name[100];
    printf("Name: ");
    input_string(name, 100);

    int amount;
    printf("Amount: ");
    input_integer(&amount);

    char type_letter;
    printf("Type ([S]OLID/[L]IQUID): ");
    input_char(&type_letter);
    IngredientType type = type_letter == 'L' || type_letter == 'l' ? LIQUID : SOLID;

    int id = add_ingredient(service, name, amount, type);
    if (id != -1) {
        printf("Ingredient added\n");
    } else {
        printf("Problem with adding ingredient\n");
    }
}

static void modify_existing_ingredient(IngredientService service) {
    list_ingredients(service);
    printf("Choose ID to modify: ");
    int id;
    input_integer(&id);

    char new_name[100];
    printf("New name: ");
    input_string(new_name, 100);

    int new_amount;
    printf("New amount: ");
    input_integer(&new_amount);

    char new_type_letter;
    printf("New type ([S]OLID/[L]IQUID): ");
    input_char(&new_type_letter);
    IngredientType type = new_type_letter == 'L' || new_type_letter == 'l' ? LIQUID : SOLID;

    bool success = modify_ingredient(service, id, new_name, new_amount, type);
    if (success) {
        printf("Ingredient modified\n");
    } else {
        printf("Problem with modifying ingredient\n");
    }
}

static void delete_existing_ingredient(IngredientService service, RecipeService recipe_service) {
    list_ingredients(service);
    printf("Choose ID to delete: ");
    int id;
    input_integer(&id);
    printf("Recipes associated with this ingredient will also be removed!\n");
    printf("Proceed? (y/n): ");
    char option;
    input_char(&option);
    if (tolower(option) != 'y') {
        return;
    }

    bool success = remove_recipe_with_ingredient_id(recipe_service, id);
    if (success) {
        printf("Recipe with this ingredient deleted\n");
    } else {
        printf("Problem with deleting recipes with this ingredient\n");
    }

    success = remove_ingredient(service, id);
    if (success) {
        printf("Ingredient deleted\n");
    } else {
        printf("Problem with deleting ingredient\n");
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
    get_ingredient_by_id(app->ingredient_service, id, &ingredient);
    gtk_entry_set_text(app->entry_ingredient_form_name, ingredient.name);
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, ingredient.amount);
    if (ingredient.type == SOLID) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_liquid), true);
    }
}

static void on_btn_ingredient_form_modify_clicked(GtkButton *button, App *app) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_ingredients);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gtk_tree_selection_get_selected(selection, &model, &iter);
    gint id;
    gtk_tree_model_get(model, &iter, 0, &id, -1);
    const gchar *name = gtk_entry_get_text(app->entry_ingredient_form_name);
    gint amount = gtk_spin_button_get_value_as_int(app->entry_ingredient_form_amount);
    IngredientType type;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid))) {
        type = SOLID;
    } else {
        type = LIQUID;
    }
    modify_ingredient(app->ingredient_service, id, name, amount, type);
    gchar *amount_text;
    if (type == SOLID) {
        amount_text = g_strdup_printf("%d", amount);
    } else {
        amount_text = g_strdup_printf("%d ml", amount);
    }
    gtk_tree_store_set(app->tree_store_ingredients, &iter, 1, name, 2, amount_text, -1);
    g_free(amount_text);
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
}

static void on_btn_ingredient_form_add_clicked(GtkButton *button, App *app) {
    const gchar *name = gtk_entry_get_text(app->entry_ingredient_form_name);
    gint amount = gtk_spin_button_get_value_as_int(app->entry_ingredient_form_amount);
    IngredientType type;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid))) {
        type = SOLID;
    } else {
        type = LIQUID;
    }
    int id = add_ingredient(app->ingredient_service, name, amount, type);
    add_to_tree_store(app->tree_store_ingredients, id, name, amount, type);
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
    gtk_entry_set_text(app->entry_ingredient_form_name, "");
    gtk_spin_button_set_value(app->entry_ingredient_form_amount, 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(app->entry_ingredient_form_type_solid), true);
}

static void on_btn_ingredient_form_cancel_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_list");
}

static void on_btn_ingredients_list_delete_clicked(GtkButton *button, App *app) {

}

static void on_btn_ingredients_list_modify_clicked(GtkButton *button, App *app) {
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

static void on_btn_ingredients_list_add_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_ingredient_form_button, "add");
    gtk_stack_set_visible_child_name(app->stack_ingredients, "ingredient_form");
}