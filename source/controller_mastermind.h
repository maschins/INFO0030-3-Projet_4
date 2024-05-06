/**
 * \file model_mastermind.h
 * \brief Controller header of mastermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 06/05/2024
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
 * \brief Data structure containing every element in the main menu
 *
 * Declaration of the ControllerMainMenu opaque type
 */
typedef struct controller_main_menu_t ControllerMainMenu;

/**
 * \struct MenuBar
 * \brief Data structure containing every element in the menu bar on the top of
 * the window
 *
 * Declaration of the MenuBar opaque type
 */
typedef struct menu_bar_t MenuBar;

/**
 * \struct ControllerMastermind
 * \brief Data structure containing every element managed by the controller
 *
 * Declaration of the ControllerMastermind opaque type
 */
typedef struct controller_mastermind_t ControllerMastermind;


/**
 * \fn ControllerMainMenu *create_controller_main_menu(ModelMainMenu *mmm,
 * ViewMainMenu *vm)
 * \brief Allocates memory and initializes the ControllerMainMenu structure
 *
 * \param mmm Pointer on the ModelMainMenu structure
 * \param vm Pointer of the ViewMainMenu structure
 *
 * \pre mmm != NULL, vm != NULL
 * \post the structure of the controller main menu is created
 *
 * \return A pointer on the ControllerMainMenu
 *         NULL if an error happened
 */
ControllerMainMenu *
create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vm);


/**
 * \fn void destroy_controller_main_menu(ControllerMainMenu *cmm);
 * 
 * \brief Frees memory allocated for ControllerMainMenu structure
 *
 * \param cmm Pointer valid to ControllerMainMenu structure

 * \pre cmm != NULL
 * \post the memory allocated for ControllerMainMenu structure is freed
 */
void destroy_controller_main_menu(ControllerMainMenu *cmm);


/**
 * \fn ControllerMastermind *create_controller_mastermind(ModelMastermind *mm, 
 *                          ViewMastermind *vm, ControllerMainMenu *cmm)
 * \brief Allocates memory and initializes the ControllerMastermind structure
 *
 * \param mm Pointer on the ModelMastermind structure
 * \param vm Pointer of the ViewMastermind structure
 * \param cmm Pointer on the ControllerMainMenu structure
 *
 * \pre mm != NULL, vm != NULL, cmm != NULL
 * \post the controller mastermind structure is created
 *
 * \return A pointer to ControllerMastermind
 *         NULL if an error happened
 */
ControllerMastermind *
create_controller_mastermind(ModelMastermind *mm, ViewMastermind *vm,
                             ControllerMainMenu *cmm);


/**
 * \fn void destroy_controller_mastermind(ControllerMastermind *cm)
 * \brief Frees memory allocated for ControllerMastermind structure
 *
 * \param cm Pointer valid to ControllerMastermind structure
 *
 * \pre cm != NULL
 * \post the memory allocated for ControllerMastermind structure is freed
 */
void destroy_controller_mastermind(ControllerMastermind *cm);


/**
 * \fn MenuBar *create_menu_bar(void)
 * \brief Allocates space and initializes the MenuBar structure
 *
 * \post the menubar structure is created
 *
 * \return A pointer to MenuBar
 *         NULL if an error happened
 */
MenuBar *create_menu_bar(void);


/**
 * \fn void init_main_menu(ControllerMainMenu *cmm)
 * \brief Initializes the main menu
 *
 * \param cmm Pointer to ControllerMainMenu structure
 *
 * \pre cmm != NULL
 * \post the main menu is initialized
 */
void init_main_menu(ControllerMainMenu *cmm);


/**
 * \fn void init_mastermind(ControllerMastermind *cm)
 * \brief Initializes the mastermind game
 *
 * \param cm Pointer to ControllerMastermind structure
 *
 * \pre cm != NULL
 * \post the mastermind game is initialized
 */
void init_mastermind(ControllerMastermind *cm);


/**
 * \fn void init_end_game_window(ControllerMastermind *cm, bool win)
 * \brief initializes the end game window.
 *
 * \param cm Pointer to ControllerMastermind structure
 * \param win Boolean indicating if the player won or lost
 *
 * \pre cm != NULL
 * \post the end game window is initialized
 */
void init_end_game_window(ControllerMastermind *cm, bool win);


/**
 * \fn void show_window(GtkWidget *button, gpointer data)
 * \brief Callback function to show a window
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer the window widget.
 */
void show_window(GtkWidget *button, gpointer data);


/**
 * \fn void hide_window(GtkWidget *button, gpointer data)
 * \brief Callback function to hide the window
 *
 * \param button The GtkWidget button that was clicked.
 * \param data A pointer the window widget.
 */
void hide_window(GtkWidget *button, gpointer data);


/**
 * \fn void init_feedback_zone_mastermind(ControllerMastermind *cm)
 * \brief Initializes the feedback zone in mastermind
 *
 * \param cm A pointer to ControllerMastermind structure.
 *
 * \pre cm != NULL
 * \post the feedback zone is initialized
 */
void init_feedback_zone_mastermind(ControllerMastermind *cm);


/**
 * \fn void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data)
 * \brief Callback function to handle the changing of the number of pawns of the slider
 *
 * \param slider The GtkWidget slider
 * \param data A pointer to ControllerMastermind structure
 */
void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data);


/**
 * \fn void on_guesser_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm)
 * \brief Callback function to handle the selection of guesser
 *
 * \param radioButton The GtkWidget radio button that was selected
 * \param cmm Pinter to ControllerMainMenu structure
 *
 * \pre cmm != NULL
 * \post the guesser selection is handled
 */
void on_guesser_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);


/**
 * \fn void on_proposer_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm)
 * \brief Callback function to handle the selection of proposer
 *
 * \param radioButton The GtkWidget radio button that was selected
 * \param cmm Pointer to ControllerMainMenu structure
 *
 * \pre cm != NULL
 * \post the proposer selection is handled
 */
void on_proposer_choosed(GtkWidget *radioButton, ControllerMainMenu *cmm);


/**
 * \fn void on_play_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Play" button click
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to ControllerMastermind structure
 */
void on_play_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_main_menu_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Main Menu" button click
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to a controllerMastermind structure
 */
void on_main_menu_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_color_picked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the selection of color
 *
 * \param button The GtkWidget button that was clicked
 * \param data a pointer to ControllerMastermind structure.
 */
void on_color_picked(GtkWidget *button, gpointer data);


/**
 * \fn void on_save_button_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Save" button click.
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to mastermind controller structure
 */
void on_save_button_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_proposition_button_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Proposition" button click.
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to mastermind controller structure
 */
void on_proposition_button_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_apply_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Apply" button click
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to mastermind controller structure
 */
void on_apply_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_reset_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Reset" button click
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to mastermind controller strcture
 */
void on_reset_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void on_feedback_button_clicked(GtkWidget *button, gpointer data)
 * \brief Callback function to handle the "Feedback" button click
 *
 * \param button The GtkWidget button that was clicked
 * \param data A pointer to ControllerMastermind structure
 */
void on_feedback_button_clicked(GtkWidget *button, gpointer data);


/**
 * \fn void reset_proposition_buttons(ControllerMastermind *cm)
 * \brief Resets the proposition buttons in mastermind
 *
 * \param cm Pointer to ControllerMastermind structure
 *
 * \pre cm != NULL
 * \post the proposition buttons are reset
 */
void reset_proposition_buttons(ControllerMastermind *cm);


/**
 * \fn void reset_feedback_buttons(ControllerMastermind *cm)
 * \brief Resets the feedback buttons in mastermind
 *
 * \param cm Pointer to ControllerMastermind structure
 *
 * \pre cm != NULL
 * \post the feedback buttons are reset
 */
void reset_feedback_buttons(ControllerMastermind *cm);

#endif /* CONTROLLER_MASTERMIND_H */
