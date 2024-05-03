#ifndef CONTROLLER_MASTERMIND_H
#define CONTROLLER_MASTERMIND_H

#include <gtk-2.0/gtk/gtk.h>
#include "model_mastermind.h"
#include "view_mastermind.h"

#define GUESSER_BUTTON_LABEL "Guesser"
#define PROPOSER_BUTTON_LABEL "Proposer"
#define SAVE_BUTTON_LABEL "Save"
#define PLAY_BUTTON_LABEL "Play"
#define QUIT_BUTTON_LABEL "Quit"

typedef struct controller_main_menu_t ControllerMainMenu;

ControllerMainMenu *create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vm);
void destroy_controller_main_menu(ControllerMainMenu *cmm);

void init_main_menu(ControllerMainMenu *cmm);

void on_save_button_clicked(GtkWidget *button, gpointer data);
void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data);
void on_guesser_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);
void on_proposer_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);
void on_play_clicked(GtkWidget *button, gpointer data);
void on_quit_clicked(GtkWidget *button, gpointer data);

#endif /* CONTROLLER_MASTERMIND_H */
