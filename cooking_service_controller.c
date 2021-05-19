//
// Created by dawids21 on 5/11/21.
//

#include "cooking_service_controller.h"

static void on_btn_recipe_prepare_done_clicked(GtkButton *button, App *app);

static void on_btn_recipe_prepare_cancel_clicked(GtkButton *button, App *app);

void cooking_service_register_callbacks(GtkBuilder *builder) {
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_prepare_done_clicked",
                                    G_CALLBACK(on_btn_recipe_prepare_done_clicked));
    gtk_builder_add_callback_symbol(builder, "on_btn_recipe_prepare_cancel_clicked",
                                    G_CALLBACK(on_btn_recipe_prepare_cancel_clicked));
}

static void on_btn_recipe_prepare_done_clicked(GtkButton *button, App *app) {

}

static void on_btn_recipe_prepare_cancel_clicked(GtkButton *button, App *app) {

}
