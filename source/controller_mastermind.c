#include <gtk-2.0/gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include "controller_mastermind.h"

struct controller_main_menu_t {
   ModelMastermind *mm;
   ViewMainMenu *vmm;
   GtkWidget *pseudoEntry;
   GtkWidget **buttons;
};


ControllerMainMenu *create_controller_main_menu(ModelMastermind *mm, ViewMainMenu *vmm) {
   assert(mm != NULL && vmm != NULL);

   ControllerMainMenu *cmm = malloc(sizeof(ControllerMainMenu));
   if(cmm == NULL)
      return NULL;

   cmm->mm = mm;
   cmm->vmm = vmm;

   
   cmm->pseudoEntry = gtk_entry_new();
   if(cmm->pseudoEntry == NULL){
      free(cmm);
      return NULL;
   }

   cmm->buttons = malloc(MAIN_MENU_NB_BUTTONS * sizeof(GtkWidget *));
   if(cmm->buttons == NULL){
      free(cmm);
      return NULL;
   }

   const char *MAIN_MENU_BUTTONS_LABELS[MAIN_MENU_NB_BUTTONS] = {
      "Save",
      "Play as guesser",
      "Play as proposer",
      "Settings",
      "Quit"
   };

   
   for(unsigned int i = 0; i < MAIN_MENU_NB_BUTTONS; i++){
      cmm->buttons[i] = gtk_button_new_with_label(MAIN_MENU_BUTTONS_LABELS[i]);
      if(cmm->buttons[i] == NULL){
         free(cmm->buttons);
         free(cmm);
         return NULL;
      }
   }

   // CONNECT SIGNALS

   return cmm;
}

void destroy_controller_main_menu(ControllerMainMenu *cmm) {
   if(cmm != NULL){
      if(cmm->buttons != NULL)
         free(cmm->buttons);
      free(cmm);
   }
}

GtkWidget *get_pseudo_entry(ControllerMainMenu *cmm) {
   assert(cmm != NULL);

   return cmm->pseudoEntry;
}


GtkWidget *get_button(ControllerMainMenu *cmm, MainMenuButton button) {
   assert(cmm != NULL);

   return cmm->buttons[button];
}