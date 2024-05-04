#ifndef CONTROLLER_MASTERMIND_H
#define CONTROLLER_MASTERMIND_H

#include <gtk-2.0/gtk/gtk.h>
#include "model_mastermind.h"
#include "view_mastermind.h"

#define SAVE_BUTTON_LABEL "Save"
#define PLAY_BUTTON_LABEL "Play"
#define SETTINGS_BUTTON_LABEL "Settings"
#define QUIT_BUTTON_LABEL "Quit"
#define GUESSER_BUTTON_LABEL "Guesser"
#define PROPOSER_BUTTON_LABEL "Proposer"

#define BAR_GAME_ITEM_LABEL "Game"
#define BAR_HELP_ITEM_LABEL "Help"
#define MENU_GAME_MAIN_MENU_ITEM_LABEL "Main menu"
#define MENU_GAME_NEW_GAME_ITEM_LABEL "New game"
#define MENU_GAME_SCORE_ITEM_LABEL "Score"
#define MENU_GAME_QUIT_ITEM_LABEL "Quit"
#define MENU_HELP_ABOUTS_ITEM_LABEL "Abouts"

typedef struct controller_main_menu_t ControllerMainMenu;

typedef struct menu_bar_t MenuBar;

typedef struct controller_mastermind_t ControllerMastermind;

ControllerMainMenu *create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vm);
void destroy_controller_main_menu(ControllerMainMenu *cmm);

ControllerMastermind *create_controller_mastermind(ModelMastermind *mm, ViewMastermind *vm, ControllerMainMenu *cmm);
void destroy_controller_mastermind(ControllerMastermind *cm);

MenuBar *create_menu_bar(void);

void init_main_menu(ControllerMainMenu *cmm);
void init_mastermind(ControllerMastermind *cm);
void show_window(GtkWidget *button, gpointer data);
void hide_window(GtkWidget *button, gpointer data);

void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data);
void on_guesser_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);
void on_proposer_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);
void on_play_clicked(GtkWidget *button, gpointer data);
void on_main_menu_clicked(GtkWidget *button, gpointer data);
void on_color_picked(GtkWidget *button, gpointer data);
void on_save_button_clicked(GtkWidget *button, gpointer data);
void on_proposition_button_clicked(GtkWidget *button, gpointer data);
void on_apply_clicked(GtkWidget *button, gpointer data);
void on_reset_clicked(GtkWidget *button, gpointer data);

void reset_proposition_buttons(ControllerMastermind *cm);


#endif /* CONTROLLER_MASTERMIND_H */
