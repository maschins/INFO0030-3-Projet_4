/**
 * \file model_mastermind.h
 * \brief Controller header of mastermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 05/05/2024
 *
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern controller header for the mastermind game.
 *
 * */

#ifndef CONTROLLER_MASTERMIND_H
#define CONTROLLER_MASTERMIND_H

#include <gtk-2.0/gtk/gtk.h>
#include "model_mastermind.h"
#include "view_mastermind.h"

/**
 * \brief Label on the save button
 */
#define SAVE_BUTTON_LABEL "Save"

/**
 * \brief Label on the play button
 */
#define PLAY_BUTTON_LABEL "Play"

/**
 * \brief Label on the settings button
 */
#define SETTINGS_BUTTON_LABEL "Settings"

/**
 * \brief Label on the quit button
 */
#define QUIT_BUTTON_LABEL "Quit"

/**
 * \brief Label on the guesser selector
 */
#define GUESSER_BUTTON_LABEL "Guesser"

/**
 * \brief Label on the proposer selector
 */
#define PROPOSER_BUTTON_LABEL "Proposer"


/**
 * \brief Label on the bar for the game subwindow
 */
#define BAR_GAME_ITEM_LABEL "Game"

/**
 * \brief Label on the bar for the help subwindow containing abouts
 */
#define BAR_HELP_ITEM_LABEL "Help"

/**
 * \brief Label on the bar for the main menu button
 */
#define MENU_GAME_MAIN_MENU_ITEM_LABEL "Main menu"

/**
 * \brief Label on the bar to start a new game
 */
#define MENU_GAME_NEW_GAME_ITEM_LABEL "New game"

/**
 * \brief Label on the button in the Game item allowing to display the stored
 * scores
 */
#define MENU_GAME_SCORE_ITEM_LABEL "Score"

/**
 * \brief Label on the button in the Game item allowing to quit the game
 */
#define MENU_GAME_QUIT_ITEM_LABEL "Quit"

/**
 * \brief Label on the button in the Help item allowing to display the about
 * window
 */
#define MENU_HELP_ABOUTS_ITEM_LABEL "Abouts"

/**
 * \struct ControllerMainMenu
 * \brief Data structure containing evey element in the main menu
 *
 * Declaration of the ControllerMainMenu opaque type
 */
typedef struct controller_main_menu_t ControllerMainMenu;

/**
 * \struct MenuBar
 * \brief Data structure containing evey element in the menu bar on the top of
 * the window
 *
 * Declaration of the MenuBar opaque type
 */
typedef struct menu_bar_t MenuBar;

/**
 * \struct ControllerMastermind
 * \brief Data structure containing evey element managed by the controller
 *
 * Declaration of the ControllerMastermind opaque type
 */
typedef struct controller_mastermind_t ControllerMastermind;

/**
 * \fn ControllerMainMenu *create_controller_main_menu(ModelMainMenu *mmm,
 * ViewMainMenu *vm)
 * \brief Allocates space and initialize the ControllerMainMenu structure
 *
 * \param mmm Pointer on the ModelMainMenu structure
 * \param vm Pointer of the ViewMainMenu structure
 *
 * \pre mmm != NULL, vm != NULL
 * \post the structure of the controller main menu is generated
 *
 * \return A pointer on the created structure
 *         NULL if an error happened
 */
ControllerMainMenu *
create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vm);

void destroy_controller_main_menu(ControllerMainMenu *cmm);

ControllerMastermind *
create_controller_mastermind(ModelMastermind *mm, ViewMastermind *vm,
                             ControllerMainMenu *cmm);

void destroy_controller_mastermind(ControllerMastermind *cm);

MenuBar *create_menu_bar(void);

void init_main_menu(ControllerMainMenu *cmm);

void init_mastermind(ControllerMastermind *cm);

void init_end_game_window(ControllerMastermind *cm, bool win);

void show_window(GtkWidget *button, gpointer data);

void hide_window(GtkWidget *button, gpointer data);

void init_feedback_zone_mastermind(ControllerMastermind *cm);

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

void on_feedback_button_clicked(GtkWidget *button, gpointer data);

void reset_proposition_buttons(ControllerMastermind *cm);

void reset_feedback_buttons(ControllerMastermind *cm);

#endif /* CONTROLLER_MASTERMIND_H */
