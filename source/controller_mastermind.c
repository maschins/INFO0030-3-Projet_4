#include <gtk-2.0/gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include "controller_mastermind.h"

struct controller_main_menu_t{
   ModelMainMenu *mmm;
   ViewMainMenu *vmm;
   GtkWidget *pseudoEntry;
   GtkWidget *saveButton;
   GtkWidget *guesserButton;
   GtkWidget *proposerButton;
   GtkWidget *nbPawnsSlider;
   GtkWidget *playButton;
   GtkWidget *quitButton;
};


ControllerMainMenu *create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vmm) {
   assert(mmm != NULL && vmm != NULL);

   // Allocate memory for controller.
   ControllerMainMenu *cmm = malloc(sizeof(ControllerMainMenu));
   if(cmm == NULL)
      return NULL;

   cmm->mmm = mmm;
   cmm->vmm = vmm;

   // Create pseudo entry.
   cmm->pseudoEntry = gtk_entry_new();
   if(cmm->pseudoEntry == NULL){
      free(cmm);
      return NULL;
   }

   // Create save button.
   cmm->saveButton = gtk_button_new_with_label(SAVE_BUTTON_LABEL);
   if(cmm->saveButton == NULL){
      free(cmm);
      return NULL;
   }

   // Créer le premier bouton radio
   cmm->guesserButton = gtk_radio_button_new_with_label(NULL, GUESSER_BUTTON_LABEL);
   if(cmm->guesserButton == NULL){
      free(cmm);
      return NULL;
   }

   // Créer le deuxième bouton radio, lié au premier
   cmm->proposerButton = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(cmm->guesserButton), PROPOSER_BUTTON_LABEL);
   if(cmm->proposerButton == NULL){
      free(cmm);
      return NULL;
   }

   // Select guesser option by default.
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cmm->guesserButton), TRUE);

   // Create the slide to select the nb of pawns.
   cmm->nbPawnsSlider = gtk_hscale_new_with_range(MIN_NB_PAWNS, MAX_NB_PAWNS, 1);
   gtk_range_set_value(GTK_RANGE(cmm->nbPawnsSlider), DEFAULT_NB_PAWNS);
   gtk_scale_set_digits(GTK_SCALE(cmm->nbPawnsSlider), 0);
   gtk_scale_set_value_pos(GTK_SCALE(cmm->nbPawnsSlider), GTK_POS_TOP);
   gtk_scale_set_draw_value(GTK_SCALE(cmm->nbPawnsSlider), TRUE);

   // Create play button.
   cmm->playButton = gtk_button_new_with_label(PLAY_BUTTON_LABEL);
   if(cmm->playButton == NULL){
      free(cmm);
      return NULL;
   }

   // Create quit button.
   cmm->quitButton = gtk_button_new_with_label(QUIT_BUTTON_LABEL);
   if(cmm->quitButton == NULL){
      free(cmm);
      return NULL;
   }

   // Connect signals to buttons.
   g_signal_connect(G_OBJECT(cmm->nbPawnsSlider), "value-changed", G_CALLBACK(on_nb_pawns_slider_changed), cmm);
   g_signal_connect(G_OBJECT(cmm->playButton), "clicked", G_CALLBACK(on_play_clicked), cmm);
   g_signal_connect(G_OBJECT(cmm->guesserButton), "clicked", G_CALLBACK(on_guesser_choosed), cmm);
   g_signal_connect(G_OBJECT(cmm->proposerButton), "clicked", G_CALLBACK(on_proposer_choosed), cmm);
   g_signal_connect(G_OBJECT(cmm->saveButton), "clicked", G_CALLBACK(on_save_button_clicked), cmm);

   return cmm;
}


void destroy_controller_main_menu(ControllerMainMenu *cmm) {
   if(cmm != NULL)
      free(cmm);
}


void init_main_menu(ControllerMainMenu *cmm) {
   assert(cmm != NULL);

   GtkWidget *window = get_main_menu_window(cmm->vmm);
   GtkWidget *mainVBox = get_main_menu_main_vbox(cmm->vmm);
   GtkWidget *pseudoHBox = get_main_menu_pseudo_hbox(cmm->vmm);
   GtkWidget *nbPawnsHBox = get_main_menu_nb_pawns_hbox(cmm->vmm);

   gtk_container_add(GTK_CONTAINER(window), mainVBox);
   gtk_box_pack_start(GTK_BOX(mainVBox), get_main_menu_logo(cmm->vmm), TRUE, TRUE, 10);

   gtk_container_add(GTK_CONTAINER(mainVBox), nbPawnsHBox);
   gtk_box_pack_start(GTK_BOX(nbPawnsHBox), get_main_menu_nb_pawns_label(cmm->vmm), FALSE, FALSE, 10);
   gtk_box_pack_start(GTK_BOX(nbPawnsHBox), cmm->nbPawnsSlider, TRUE, TRUE, 0);

   gtk_container_add(GTK_CONTAINER(mainVBox), pseudoHBox);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), get_main_menu_pseudo_label(cmm->vmm), TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), cmm->pseudoEntry, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), cmm->saveButton, TRUE, TRUE, 0);
   
   gtk_box_pack_start(GTK_BOX(mainVBox), get_main_menu_error_label(cmm->vmm), TRUE, TRUE, 0);
   gtk_misc_set_alignment(GTK_MISC(get_main_menu_error_label(cmm->vmm)), 0, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->guesserButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->proposerButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->playButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->quitButton, TRUE, TRUE, 0);

   // Connect signals.
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   gtk_widget_show_all(window);
}


void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data) {
   assert(slider != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *)data;

   unsigned int nbPawns = gtk_range_get_value(GTK_RANGE(slider));
   set_nb_pawns_slider(cmm->mmm, nbPawns);
}


void on_guesser_choosed(GtkWidget *button, ControllerMainMenu *cmm) {
   assert(button != NULL && cmm != NULL);
   set_role(cmm->mmm, GUESSER);
}


void on_proposer_choosed(GtkWidget *button, ControllerMainMenu *cmm) {
   assert(button != NULL && cmm != NULL);
   set_role(cmm->mmm, PROPOSER);
}


void on_save_button_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *)data;
   const char *pseudo = gtk_entry_get_text(GTK_ENTRY(cmm->pseudoEntry));

   if(strlen(pseudo) > MAX_PSEUDO_LENGTH){
      const char *PSEUDO_TOO_LONG_ERROR = "Pseudo is too long (Max 50 char).";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)), PSEUDO_TOO_LONG_ERROR);
   } 
   else if(strlen(pseudo) < MIN_PSEUDO_LENGTH){
      const char *PSEUDO_TOO_SHORT_ERROR = "Pseudo is too long (Min 5 char).";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)), PSEUDO_TOO_SHORT_ERROR);
   }
   else{
      const char *PSEUDO_GOOD = "Pseudo saved !";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)), PSEUDO_GOOD);
      set_pseudo(cmm->mmm, (char *)pseudo);
   }
}


void on_play_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *)data;

   // TODO
}


void on_quit_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *)data;

   // TODO
}