/**
 * \file view_mastermind.h
 * \brief View header of mastermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 06/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern view header for the mastermind game.
 * 
 * */

#ifndef __VIEW_MASTERMIND__
#define __VIEW_MASTERMIND__

#include "model_mastermind.h"

/**
 * \brief Main menu window label
 */
#define MAIN_MENU_WINDOW_LABEL "Main menu"

/**
 * \brief Main menu window width
 */
#define MAIN_MENU_WINDOW_WIDTH 400

/**
 * \brief Main menu window height
 */
#define MAIN_MENU_WINDOW_HEIGHT 800

/**
 * \brief Game window label
 */
#define MASTERMIND_WINDOW_LABEL "Mastermind"

/**
 * \brief Game window size scale (Width & Height are fixed for good game render)
 */
#define MASTERMIND_WINDOW_SIZE 0.8

/**
 * \brief Abouts window label
 */
#define ABOUTS_WINDOW_LABEL "Abouts"

/**
 * \brief Scores window label
 */
#define SCORES_WINDOW_LABEL "Scores"

/**
 * \brief End game window label
 */
#define END_GAME_WINDOW_LABEL "End game"

/**
 * \brief End game window width
 */
#define END_GAME_WINDOW_WIDTH 200

/**
 * \brief End game window height
 */
#define END_GAME_WINDOW_HEIGHT 150

/**
 * \brief Main menu logo path
 */
#define LOGO_PATH "./images/title.png"

/**
 * Declare the ViewMainMenu opaque type.
 * */
typedef struct view_main_menu_t ViewMainMenu; 

/**
 * Declare the ViewMastermind opaque type.
 * */
typedef struct view_mastermind_t ViewMastermind;


ViewMainMenu *create_view_main_menu(ModelMainMenu *mmm);

void destroy_view_main_menu(ViewMainMenu *vmm);

ViewMastermind *create_view_mastermind(ModelMastermind *mm);

void destroy_view_mastermind(ViewMastermind *vm);

GtkWidget *create_window(const char *title, unsigned int width, unsigned int height);

void apply_pixbufs_to_button(GtkWidget *button, GdkPixbuf *pb, unsigned int size);

GtkWidget *create_button_with_pixbuf(GdkPixbuf *pb, unsigned int size);

GtkWidget *create_image(const char *imagePath, unsigned int width, unsigned int height);

void update_last_combination_images(ViewMastermind *vm, ModelMastermind *mm);

void udpate_last_feedback_images(ViewMastermind *vm, ModelMastermind *mm);

GdkPixbuf *get_color_image_pixbuf(ViewMastermind *vm, PAWN_COLOR color);

GdkPixbuf *get_feedback_image_pixbuf(ViewMastermind *vm, FEEDBACK_COLOR color);

GtkWidget *get_main_menu_window(ViewMainMenu *vmm);

GtkWidget *get_main_menu_main_vbox(ViewMainMenu *vmm);

GtkWidget *get_main_menu_pseudo_hbox(ViewMainMenu *vmm);

GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm);

GtkWidget *get_main_menu_logo(ViewMainMenu *vmm);

GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm);

GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm);

GtkWidget *get_main_menu_error_label(ViewMainMenu *vmm);

unsigned int get_mastermind_small_button_size(ViewMastermind *vm);

unsigned int get_mastermind_proposition_button_size(ViewMastermind *vm);

unsigned int get_mastermind_color_button_size(ViewMastermind *vm);

unsigned int get_mastermind_big_button_size(ViewMastermind *vm);

GtkWidget *get_mastermind_end_game_window(ViewMastermind *vm);

GdkPixbuf *get_mastermind_win_image(ViewMastermind *vm);

GdkPixbuf *get_mastermind_loose_image(ViewMastermind *vm);

GtkWidget *get_mastermind_abouts_window(ViewMastermind *vm);

GtkWidget *get_abouts_main_vbox(ViewMastermind *vm);

GtkWidget *get_mastermind_abouts_label(ViewMastermind *vm);

GtkWidget *get_mastermind_score_window(ViewMastermind *vm);

GtkWidget *get_mastermind_scores_title_label(ViewMastermind *vm);

GtkWidget **get_mastermind_players_scores_label(ViewMastermind *vm);

GtkWidget *get_score_main_vbox(ViewMastermind *vm);

GtkWidget *get_mastermind_window(ViewMastermind *vm);

GtkWidget *get_mastermind_main_vbox(ViewMastermind *vm);

GtkWidget *get_mastermind_history_table(ViewMastermind *vm);

GtkWidget *get_mastermind_feedback_zone_hbox(ViewMastermind *vm);

GtkWidget *get_mastermind_proposition_hbox(ViewMastermind *vm);

GtkWidget *get_mastermind_proposition_control_hbox(ViewMastermind *vm);

GtkWidget *get_mastermind_color_selection_hbox(ViewMastermind *vm);

GtkWidget *get_mastermind_score_hbox(ViewMastermind *vm);

GtkWidget *get_mastermind_history_combination_button(ViewMastermind *vm, unsigned int i, unsigned int j);

GtkWidget *get_mastermind_history_feedback_button(ViewMastermind *vm, unsigned int i, unsigned int j);

GtkWidget *get_mastermind_score_label(ViewMastermind *vm);

void set_score_label_text(GtkWidget *label, char *string);

#endif //__VIEW_MASTERMIND__
