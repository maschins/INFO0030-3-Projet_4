#include <stdlib.h>
#include <gtk-2.0/gtk/gtk.h>
#include <stdbool.h>
#include <assert.h>

#include "model_mastermind.h"
#include "view_mastermind.h"
#include "controller_mastermind.h"

#define NB_PAWNS 4
#define NB_ATTEMPS 10

void init_main_menu(ControllerMainMenu *cmm, ViewMainMenu *vmm);

int main(int argc, char **argv) {

   gtk_init(&argc, &argv);
   
   ModelMastermind *mm = create_model_mastermind(NB_PAWNS, NB_ATTEMPS);
   if(mm == NULL)
      return EXIT_FAILURE;

   ViewMainMenu *vmm = create_view_main_menu(mm);
   if(vmm == NULL){
      destroy_model_mastermind(mm);
      return EXIT_FAILURE;
   }

   ControllerMainMenu *cmm = create_controller_main_menu(mm, vmm);
   if(cmm == NULL){
      destroy_view_main_menu(vmm);
      destroy_model_mastermind(mm);
      return EXIT_FAILURE;
   }

   init_main_menu(cmm, vmm);

   gtk_main();

   destroy_controller_main_menu(cmm);
   destroy_view_main_menu(vmm);
   destroy_model_mastermind(mm);

   return EXIT_SUCCESS;
}


void init_main_menu(ControllerMainMenu *cmm, ViewMainMenu *vmm) {
   assert(cmm != NULL && vmm != NULL);

   GtkWidget *window = get_window(vmm);
   gtk_window_set_title(GTK_WINDOW(window), MAIN_MENU_WINDOW_LABEL);
   gtk_window_set_default_size(GTK_WINDOW(window), MAIN_MENU_WINDOW_WIDTH, MAIN_MENU_WINDOW_HEIGHT);
   gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   
   GtkWidget *mainVBox = get_main_v_box(vmm);
   GtkWidget *hBoxPseudo = get_h_box_pseudo(vmm);

   gtk_container_add(GTK_CONTAINER(window), mainVBox);

   gtk_box_pack_start(GTK_BOX(mainVBox), get_label(vmm, MAIN_MENU_TITLE_LABEL), FALSE, FALSE, 0);
   
   gtk_container_add(GTK_CONTAINER(mainVBox), hBoxPseudo);

   gtk_box_pack_start(GTK_BOX(hBoxPseudo), get_label(vmm, MAIN_MENU_PSEUDO_LABEL), FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(hBoxPseudo), get_pseudo_entry(cmm), FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(hBoxPseudo), get_button(cmm, MAIN_MENU_SAVE_BUTTON), FALSE, FALSE, 0);

   gtk_box_pack_start(GTK_BOX(mainVBox), get_button(cmm, MAIN_MENU_PLAY_GUESSER_BUTTON), FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), get_button(cmm, MAIN_MENU_PLAY_PROPOSER_BUTTON), FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), get_button(cmm, MAIN_MENU_SETTINGS_BUTTON), FALSE, FALSE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), get_button(cmm, MAIN_MENU_QUIT_BUTTON), FALSE, FALSE, 0); 

   gtk_widget_show_all(window);
}