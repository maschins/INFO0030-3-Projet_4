#ifndef __VIEW_MASTERMIND__
#define __VIEW_MASTERMIND__

#include "model_mastermind.h"

#define MAIN_MENU_WINDOW_LABEL "Main menu"
#define MAIN_MENU_WINDOW_WIDTH 300
#define MAIN_MENU_WINDOW_HEIGHT 600

#define LOGO_PATH "../images/title.png"
#define LOGO_WIDTH MAIN_MENU_WINDOW_WIDTH
#define LOGO_HEIGHT (0.2 * MAIN_MENU_WINDOW_HEIGHT)

typedef struct view_main_menu_t ViewMainMenu;

ViewMainMenu *create_view_main_menu(ModelMainMenu *mmm);
void destroy_view_main_menu(ViewMainMenu *vmm);

GtkWidget *create_window(const char *title, unsigned int width, unsigned int height);
GtkWidget *create_image(const char *imagePath, unsigned int width, unsigned int height);

GtkWidget *get_main_menu_window(ViewMainMenu *vmm);
GtkWidget *get_main_menu_main_vbox(ViewMainMenu *vmm);
GtkWidget *get_main_menu_pseudo_hbox(ViewMainMenu *vmm);
GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm);
GtkWidget *get_main_menu_logo(ViewMainMenu *vmm);
GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm);
GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm);
GtkWidget *get_main_menu_error_label(ViewMainMenu *vmm);

#endif //__VIEW_MASTERMIND__