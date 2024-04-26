#ifndef __VIEW_MASTERMIND__
#define __VIEW_MASTERMIND__

#include "model_mastermind.h"

#define MAIN_MENU_WINDOW_LABEL "Mastermind - Main menu"
#define MAIN_MENU_WINDOW_WIDTH 100
#define MAIN_MENU_WINDOW_HEIGHT 200

typedef enum{
	MAIN_MENU_TITLE_LABEL,
	MAIN_MENU_PSEUDO_LABEL,
	MAIN_MENU_NB_LABELS
}MainMenuLabel;

typedef struct view_main_menu_t ViewMainMenu;

ViewMainMenu *create_view_main_menu(ModelMastermind *mm);
void destroy_view_main_menu(ViewMainMenu *vmm);

GtkWidget *get_window(ViewMainMenu *vmm);
GtkWidget *get_main_v_box(ViewMainMenu *vmm);
GtkWidget *get_h_box_pseudo(ViewMainMenu *vmm);
GtkWidget *get_label(ViewMainMenu *vmm, MainMenuLabel label);

#endif //__VIEW_MASTERMIND__