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
    gtk_stack_set_visible_child_name(app->stack_recipes, "recipe_details");
}

static void on_btn_recipes_list_delete_clicked(GtkButton *button, App *app) {

}

static void on_btn_recipes_list_add_clicked(GtkButton *button, App *app) {
    gtk_stack_set_visible_child_name(app->stack_recipes, "add_recipe");
}
