#include <stdlib.h>
#include <gtk-2.0/gtk/gtk.h>
#include <stdbool.h>
#include <assert.h>

#include "model_mastermind.h"
#include "view_mastermind.h"
#include "controller_mastermind.h"

#define NB_PAWNS 4
#define NB_ATTEMPS 10

int main(int argc, char **argv) {

   gtk_init(&argc, &argv);
   
   ModelMainMenu *mmm = create_model_main_menu();
   if(mmm == NULL)
      return EXIT_FAILURE;

   ViewMainMenu *vmm = create_view_main_menu(mmm);
   if(vmm == NULL){
      destroy_model_main_menu(mmm);
      return EXIT_FAILURE;
   }

   ControllerMainMenu *cmm = create_controller_main_menu(mmm, vmm);
   if(cmm == NULL){
      destroy_view_main_menu(vmm);
      destroy_model_main_menu(mmm);
      return EXIT_FAILURE;
   }

   init_main_menu(cmm);
   
   gtk_main();

   return EXIT_SUCCESS;
}