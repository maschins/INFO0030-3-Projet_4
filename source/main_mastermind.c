/**
 * \file main_mastermind.c
 * \brief Main file of matsermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 04/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * 
 * */

#include <stdlib.h>
#include <gtk-2.0/gtk/gtk.h>
#include <stdbool.h>
#include <assert.h>

#include "model_mastermind.h"
#include "view_mastermind.h"
#include "controller_mastermind.h"

int main(int argc, char **argv) {

   gtk_init(&argc, &argv);

   // Create main menu model.
   ModelMainMenu *mmm = create_model_main_menu();
   if(mmm == NULL)
      return EXIT_FAILURE;

   // Create main menu view.
   ViewMainMenu *vmm = create_view_main_menu(mmm);
   if(vmm == NULL){
      destroy_model_main_menu(mmm);
      return EXIT_FAILURE;
   }

   // Create main menu controller.
   ControllerMainMenu *cmm = create_controller_main_menu(mmm, vmm);
   if(cmm == NULL){
      destroy_view_main_menu(vmm);
      destroy_model_main_menu(mmm);
      return EXIT_FAILURE;
   }

   init_main_menu(cmm);

   gtk_main();

   // Free memory
   destroy_controller_main_menu(cmm);
   destroy_view_main_menu(vmm);
   destroy_model_main_menu(mmm);

   return EXIT_SUCCESS;
}
