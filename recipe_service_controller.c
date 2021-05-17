//
// Created by dawids21 on 5/10/21.
//

#include "recipe_service_controller.h"
#include "input.h"
#include "ingredient_service_controller.h"
#include "recipe.h"
#include <stdlib.h>
#include <ingredient_service.h>

static void list_recipes(RecipeService service);

static void print_info_about_recipe(RecipeService service);

static void add_new_recipe(RecipeService service, IngredientService ingredient_service);

static void delete_existing_recipe(RecipeService service);

static void add_to_list_store(GtkListStore *store, int id, char *name, bool possible, int num_of_uses);

static void remove_widget_from_list(GtkWidget *widget, gpointer list);

// callbacks

static void on_btn_recipe_details_prepare_clicked(GtkButton *button, App *app);

static void on_btn_recipe_details_return_clicked(GtkButton *button, App *app);

static void on_btn_add_recipe_add_clicked(GtkButton *button, App *app);

static void on_btn_add_recipe_cancel_clicked(GtkButton *button, App *app);

static void on_btn_add_recipe_remove_step_clicked(GtkButton *button, App *app);

static void on_btn_add_recipe_add_step_clicked(GtkButton *button, App *app);

static void on_crnd_add_recipe_step_description_edited(GtkCellRendererText *renderer,
                                                       char *path,
                                                       char *new_text,
                                                       App *app);

static void on_btn_add_recipe_remove_ingredient_clicked(GtkButton *button, App *app);

static void on_btn_add_recipe_add_ingredient_clicked(GtkButton *button, App *app);

static void on_crnd_add_recipe_ingredient_amount_edited(GtkCellRendererText *renderer,
                                                        char *path,
                                                        char *new_text,
                                                        App *app);

static void on_btn_recipes_list_prepare_clicked(GtkButton *button, App *app);

static void on_btn_recipes_list_details_clicked(GtkButton *button, App *app);

static void on_btn_recipes_list_delete_clicked(GtkButton *button, App *app);

static void on_btn_recipes_list_add_clicked(GtkButton *button, App *app);

void recipe_service_display_main_menu() {
    printf("***** CFood *****\n");
    printf("-----------------\n");
    printf("1. List all recipes\n");
    printf("2. Detailed information about recipe\n");
    printf("3. Add new recipe\n");
    printf("4. Delete existing recipe\n");
    printf("5. Return\n");
    printf("Choose option: ");
}

void recipe_service_handle_option(char option, RecipeService service, IngredientService ingredient_service) {
    switch (option) {
        case '1':
            list_recipes(service);
            break;
        case '2':
            print_info_about_recipe(service);
            break;
        case '3':
            add_new_recipe(service, ingredient_service);
            break;
        case '4':
            delete_existing_recipe(service);
            break;
        default:
            break;
    }
    printf("\n");
}

void recipe_service_register_callbacks(GtkBuilder *builder) {
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_details_prepare_clicked", G_CALLBACK(
            on_btn_recipe_details_prepare_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_details_return_clicked", G_CALLBACK(
            on_btn_recipe_details_return_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_add_clicked", G_CALLBACK(
            on_btn_add_recipe_add_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_cancel_clicked", G_CALLBACK(
            on_btn_add_recipe_cancel_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_remove_step_clicked", G_CALLBACK(
            on_btn_add_recipe_remove_step_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_add_step_clicked", G_CALLBACK(
            on_btn_add_recipe_add_step_clicked));
    gtk_builder_add_callback_symbol(builder, "on_crnd_add_recipe_step_description_edited", G_CALLBACK(
            on_crnd_add_recipe_step_description_edited));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_remove_ingredient_clicked", G_CALLBACK(
            on_btn_add_recipe_remove_ingredient_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_add_recipe_add_ingredient_clicked", G_CALLBACK(
            on_btn_add_recipe_add_ingredient_clicked));
    gtk_builder_add_callback_symbol(builder, "on_crnd_add_recipe_ingredient_amount_edited", G_CALLBACK(
            on_crnd_add_recipe_ingredient_amount_edited));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipes_list_prepare_clicked", G_CALLBACK(
            on_btn_recipes_list_prepare_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipes_list_details_clicked", G_CALLBACK(
            on_btn_recipes_list_details_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipes_list_delete_clicked", G_CALLBACK(
            on_btn_recipes_list_delete_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipes_list_add_clicked", G_CALLBACK(
            on_btn_recipes_list_add_clicked));
}

void recipe_service_init_list_store(App *app) {
    GtkListStore *store = app->list_store_recipes;
    int num_of_recipes = get_num_of_recipes(app->recipe_service);
    RecipeReadModel to_list[num_of_recipes];
    get_all_recipes(app->recipe_service, to_list);
    for (int i = 0; i < num_of_recipes; i++) {
        RecipeReadModel current = to_list[i];
        add_to_list_store(store, current.id, current.name, check_if_recipe_is_possible(app->recipe_service, current.id),
                          current.num_of_uses);
    }
}

static void list_recipes(RecipeService service) {
    int num_of_recipes = get_num_of_recipes(service);
    if (num_of_recipes == 0) {
        printf("No recipes\n");
        return;
    }
    RecipeReadModel recipes[num_of_recipes];
    get_all_recipes(service, recipes);
    printf("ID | Name | Is possible? | Number of uses\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < num_of_recipes; i++) {
        RecipeReadModel current = recipes[i];
        printf("%d | %s | %s | %d\n", current.id, current.name,
               check_if_recipe_is_possible(service, current.id) ? "YES" : "NO",
               current.num_of_uses);
    }
}

static void print_info_about_recipe(RecipeService service) {
    list_recipes(service);
    printf("Choose ID: ");
    int id;
    input_integer(&id);
    print_detailed_info_about_recipe(service, id);
}

static void add_new_recipe(RecipeService service, IngredientService ingredient_service) {
    char name[100];
    printf("Name: ");
    input_string(name, 100);

    int num_of_steps;
    printf("Num of steps: ");
    input_integer(&num_of_steps);

    char *steps[num_of_steps];
    for (int i = 0; i < num_of_steps; ++i) {
        steps[i] = malloc(sizeof(char) * 200);
        printf("Step %d: ", i);
        input_string(steps[i], 200);
    }

    ingredient_service_handle_option('1', ingredient_service, service);
    int num_of_ingredients;
    printf("Num of ingredients: ");
    input_integer(&num_of_ingredients);

    RecipeIngredient ingredients[num_of_ingredients];
    for (int i = 0; i < num_of_ingredients; ++i) {
        ingredients[i] = malloc(sizeof(struct RecipeIngredient));
        printf("Ingredient %d id: ", i);
        input_integer(&ingredients[i]->id);
        printf("Ingredient %d amount: ", i);
        input_integer(&ingredients[i]->amount);
    }

    bool success = add_recipe(service, name, steps, num_of_steps, ingredients, num_of_ingredients);
    if (success) {
        printf("Recipe added\n");
    } else {
        printf("Problem with adding recipe\n");
    }
}

static void delete_existing_recipe(RecipeService service) {
    list_recipes(service);
    printf("Choose ID to delete: ");
    int id;
    input_integer(&id);

    bool success = remove_recipe(service, id);
    if (success) {
        printf("Recipe deleted\n");
    } else {
        printf("Problem with deleting recipe\n");
    }
}

void add_to_list_store(GtkListStore *store, int id, char *name, bool possible, int num_of_uses) {
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, id,
                       1, name,
                       2, possible,
                       3, num_of_uses,
                       -1);
}

static void remove_widget_from_list(GtkWidget *widget, gpointer list) {
    gtk_container_remove(GTK_CONTAINER(list), widget);
}

static void on_btn_recipe_details_prepare_clicked(GtkButton *button, App *app) {

}

static void on_btn_recipe_details_return_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_recipes, "recipes_list");
}

static void on_btn_add_recipe_add_clicked(GtkButton *button, App *app) {

}

static void on_btn_add_recipe_cancel_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_recipes, "recipes_list");
}

static void on_btn_add_recipe_remove_step_clicked(GtkButton *button, App *app) {

}

static void on_btn_add_recipe_add_step_clicked(GtkButton *button, App *app) {

}

static void on_crnd_add_recipe_step_description_edited(GtkCellRendererText *renderer,
                                                       char *path,
                                                       char *new_text,
                                                       App *app) {

}

static void on_btn_add_recipe_remove_ingredient_clicked(GtkButton *button, App *app) {

}

static void on_btn_add_recipe_add_ingredient_clicked(GtkButton *button, App *app) {

}

static void on_crnd_add_recipe_ingredient_amount_edited(GtkCellRendererText *renderer,
                                                        char *path,
                                                        char *new_text,
                                                        App *app) {

}

static void on_btn_recipes_list_prepare_clicked(GtkButton *button, App *app) {

}

static void on_btn_recipes_list_details_clicked(GtkButton *button, App *app) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_recipes);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        return;
    }
    gtk_tree_model_get(model, &iter, 0, &id, -1);

    RecipeReadModel recipe;
    get_recipe_by_id(app->recipe_service, id, &recipe);

    gtk_label_set_text(app->lbl_recipe_details_name, recipe.name);

    gchar *num_of_uses = g_strdup_printf("Number of uses: %d", recipe.num_of_uses);
    gtk_label_set_text(app->lbl_recipe_details_num_of_uses, num_of_uses);
    g_free(num_of_uses);

    gtk_container_foreach(GTK_CONTAINER(app->list_recipe_details_ingredients), remove_widget_from_list,
                          app->list_recipe_details_ingredients);

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
        gtk_list_box_insert(GTK_LIST_BOX(app->list_recipe_details_ingredients), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_recipe_details_ingredients));

    gtk_container_foreach(GTK_CONTAINER(app->list_recipe_details_steps), remove_widget_from_list,
                          app->list_recipe_details_steps);

    for (int i = 0; i < recipe.num_of_steps; ++i) {
        GtkWidget *list_box_row = gtk_list_box_row_new();
        gchar *step;
        step = g_strdup_printf("%d. %s", i + 1, recipe.steps[i]);
        GtkWidget *lbl_step = gtk_label_new(step);
        gtk_label_set_xalign(GTK_LABEL(lbl_step), 0);
        g_free(step);
        gtk_container_add(GTK_CONTAINER(list_box_row), lbl_step);
        gtk_list_box_insert(GTK_LIST_BOX(app->list_recipe_details_steps), list_box_row, -1);
    }

    gtk_widget_show_all(GTK_WIDGET(app->list_recipe_details_steps));
    gtk_stack_set_visible_child_name(app->stack_recipes, "recipe_details");
}

static void on_btn_recipes_list_delete_clicked(GtkButton *button, App *app) {
    GtkTreeSelection *selection = gtk_tree_view_get_selection(app->tree_view_recipes);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;
    if (!gtk_tree_selection_get_selected(selection, &model, &iter)) {
        return;
    }

    gtk_tree_model_get(model, &iter, 0, &id, -1);
    int response = gtk_dialog_run(GTK_DIALOG(app->dialog_delete_recipe));
    gtk_widget_hide(GTK_WIDGET(app->dialog_delete_recipe));

    if (response != GTK_RESPONSE_OK) {
        return;
    }

    remove_recipe(app->recipe_service, id);

    gtk_list_store_remove(app->list_store_recipes, &iter);
}

static void on_btn_recipes_list_add_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_recipes, "add_recipe");
}
