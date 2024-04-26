#ifndef CONTROLLER_MASTERMIND_H
#define CONTROLLER_MASTERMIND_H

#include <gtk-2.0/gtk/gtk.h>
#include "model_mastermind.h"
#include "view_mastermind.h"

typedef enum{
   MAIN_MENU_SAVE_BUTTON,
   MAIN_MENU_PLAY_GUESSER_BUTTON,
   MAIN_MENU_PLAY_PROPOSER_BUTTON,
   MAIN_MENU_SETTINGS_BUTTON,
   MAIN_MENU_QUIT_BUTTON,
   MAIN_MENU_NB_BUTTONS
}MainMenuButton;

typedef struct controller_main_menu_t ControllerMainMenu;

typedef struct controller_mastermind_t ControllerMastermind;

ControllerMainMenu *create_controller_main_menu(ModelMastermind *mm, ViewMainMenu *vm);
void destroy_controller_main_menu(ControllerMainMenu *cmm);

GtkWidget *get_pseudo_entry(ControllerMainMenu *cmm);
GtkWidget *get_button(ControllerMainMenu *cmm, MainMenuButton button);

#endif /* CONTROLLER_MASTERMIND_H */
