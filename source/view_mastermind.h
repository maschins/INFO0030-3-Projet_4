#ifndef __VIEW_MASTERMIND__
#define __VIEW_MASTERMIND__

#include "model_mastermind.h"

#define MAIN_MENU_WINDOW_LABEL "Main menu"
#define MAIN_MENU_WINDOW_WIDTH 400
#define MAIN_MENU_WINDOW_HEIGHT 800

#define MASTERMIND_WINDOW_LABEL "Mastermind"
#define MASTERMIND_WINDOW_SIZE 0.8

#define ABOUTS_WINDOW_LABEL "Abouts"

#define END_GAME_WINDOW_LABEL "End game"

#define LOGO_PATH "./images/title.png"
#define LOGO_WIDTH MAIN_MENU_WINDOW_WIDTH
#define LOGO_HEIGHT (0.2 * MAIN_MENU_WINDOW_HEIGHT)

typedef struct view_main_menu_t ViewMainMenu;

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

GtkWidget *get_main_menu_welcome_hbox(ViewMainMenu *vmm);

GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm);

GtkWidget *get_main_menu_logo(ViewMainMenu *vmm);

GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm);

GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm);

GtkWidget *get_main_menu_welcome_label(ViewMainMenu *vmm);

GtkWidget *get_main_menu_current_pseudo_label(ViewMainMenu *vmm);

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

#endif //__VIEW_MASTERMIND__
