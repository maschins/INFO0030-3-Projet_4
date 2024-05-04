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


struct controller_menu_bar_t{
   GtkWidget *menuBar;
   GtkWidget *menuGame;
   GtkWidget *menuHelp;
   GtkWidget *itemGame;
   GtkWidget *itemNewGame;
   GtkWidget *itemMainMenu;
   GtkWidget *itemScore;
   GtkWidget *itemQuit;
   GtkWidget *itemAbouts;
};


struct controller_mastermind_t{
   ModelMastermind *mm;
   ViewMastermind *vm;
   GtkWidget *applyButton;
   GtkWidget *resetButton;
   GtkWidget **colorSelectionButtons;
   GtkWidget **propositionButtons;
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


ControllerMastermind *create_controller_mastermind(ModelMastermind *mm, ViewMastermind *vm){
   assert(vm != NULL && mm != NULL);

   ControllerMastermind *cm = malloc(sizeof(ControllerMastermind));
   if(cm == NULL)
      return NULL;

   cm->mm = mm;
   cm->vm = vm;

   const char *APPLY_BUTTON_LABEL = "Apply";
   cm->applyButton = gtk_button_new_with_label(APPLY_BUTTON_LABEL);
   if(cm->applyButton == NULL){
      free(cm);
      return NULL;
   }

   const char *RESET_BUTTON_LABEL = "Reset";
   cm->resetButton = gtk_button_new_with_label(RESET_BUTTON_LABEL);
   if(cm->resetButton == NULL){
      free(cm);
      return NULL;
   }

   cm->colorSelectionButtons = malloc((NB_PAWN_COLORS - 1) * sizeof(GtkWidget *)); // -1 because default color is not selectable. 
   if(cm->colorSelectionButtons == NULL){
      free(cm);
      return NULL;
   }

   for(unsigned int i = 0; i < NB_PAWN_COLORS - 1; i++){
      cm->colorSelectionButtons[i] = create_button_with_pixbuf(get_color_image_pixbuf(vm, i), get_mastermind_color_button_size(vm));
      if(cm->colorSelectionButtons[i] == NULL){
         free(cm->colorSelectionButtons);
         free(cm);
         return NULL;
      }
   }

   cm->propositionButtons = malloc(get_nb_pawns(mm) * sizeof(GtkWidget *));
   if(cm->propositionButtons == NULL){
      free(cm->colorSelectionButtons);
      free(cm);
      return NULL;
   }

   for(unsigned int i = 0; i < get_nb_pawns(mm); i++){
      cm->propositionButtons[i] = create_button_with_pixbuf(get_color_image_pixbuf(vm, PAWN_DEFAULT), get_mastermind_proposition_button_size(vm));
      if(cm->propositionButtons[i] == NULL){
         free(cm->colorSelectionButtons);
         free(cm->propositionButtons);
         free(cm);
         return NULL;
      }
   }

   return cm;
}


void destroy_controller_mastermind(ControllerMastermind *cm){
   if(cm != NULL){
      if(cm->colorSelectionButtons != NULL)
         free(cm->colorSelectionButtons);

      if(cm->propositionButtons != NULL)
         free(cm->propositionButtons);

      free(cm);
   }
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


void init_mastermind(ControllerMastermind *cm) {
   assert(cm != NULL);

   GtkWidget *window = get_mastermind_window(cm->vm);
   GtkWidget *mainVBox = get_mastermind_main_vbox(cm->vm);
   GtkWidget *historyTable = get_mastermind_history_table(cm->vm);
   GtkWidget *propositionHBox = get_mastermind_proposition_hbox(cm->vm);
   GtkWidget *propositionControlHBox = get_mastermind_proposition_control_hbox(cm->vm);
   GtkWidget *colorSelectionHBox = get_mastermind_color_selection_hbox(cm->vm);
   GtkWidget *scoreHBox = get_mastermind_score_hbox(cm->vm);

   unsigned int nbCombi = get_nb_combinations(cm->mm);
   unsigned int nbPawns = get_nb_pawns(cm->mm);

   for(int i = 0; i < nbCombi; i++){
      for(int j = 0; j < nbPawns; j++){
         gtk_table_attach_defaults(GTK_TABLE(historyTable), get_mastermind_history_combination_button(cm->vm, i, j), j, j + 1, i, i + 1);
         gtk_table_attach(GTK_TABLE(historyTable), get_mastermind_history_feedback_button(cm->vm, i, j), nbPawns + j, nbPawns + j + 1, i, i + 1, 0, 0, 0, 0);
      }
   }

   for(int i = 0; i < nbPawns; i++){
      gtk_box_pack_start(GTK_BOX(propositionHBox), cm->propositionButtons[i], TRUE, TRUE, 0);
      g_signal_connect(G_OBJECT(cm->propositionButtons[i]), "clicked", G_CALLBACK(on_proposition_button_clicked), cm);
   }

   gtk_box_pack_start(GTK_BOX(propositionControlHBox), cm->applyButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(propositionControlHBox), cm->resetButton, TRUE, TRUE, 0);

   for(int i = 0; i < NB_PAWN_COLORS - 1; i++) {
      g_signal_connect(G_OBJECT(cm->colorSelectionButtons[i]), "clicked", G_CALLBACK(on_color_picked), cm);
      gtk_box_pack_start(GTK_BOX(colorSelectionHBox), cm->colorSelectionButtons[i], TRUE, TRUE, 0);
   }

   //GtkWidget *scoreAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
   //gtk_box_pack_start(GTK_BOX(scoreHBox), scoreAlignment, TRUE, TRUE, 0);
   //gtk_container_add(GTK_CONTAINER(scoreAlignment), get_mastermind_score_label(cm->vm));

   gtk_container_add(GTK_CONTAINER(mainVBox), historyTable);
   gtk_container_add(GTK_CONTAINER(mainVBox), propositionControlHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), propositionHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), colorSelectionHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), scoreHBox);
   gtk_container_add(GTK_CONTAINER(window), mainVBox);

   g_signal_connect(G_OBJECT(cm->applyButton), "clicked", G_CALLBACK(on_apply_clicked), cm);
   g_signal_connect(G_OBJECT(cm->resetButton), "clicked", G_CALLBACK(on_reset_clicked), cm);
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

   ModelMastermind *mm = create_model_mastermind(cmm->mmm);
   if(mm == NULL)
      gtk_main_quit();

   ViewMastermind *vm = create_view_mastermind(mm);
   if(vm == NULL)
      gtk_main_quit();

   ControllerMastermind *cm = create_controller_mastermind(mm, vm);
   if(cm == NULL)
      gtk_main_quit();

   init_mastermind(cm);
}


void on_color_picked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *)data;

   int newColor = -1;
   for(unsigned int i = 0; newColor == -1 && i < NB_PAWN_COLORS - 1; i++)
      if(cm->colorSelectionButtons[i] == button)
         newColor = i;

   if(newColor != -1)
      set_selected_color(cm->mm, newColor);
}


void on_proposition_button_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *)data;
   
   int pawnIndex = -1;
   for(unsigned int i = 0; pawnIndex == -1 && i < get_nb_pawns(cm->mm); i++) {
      if(cm->propositionButtons[i] == button)
         pawnIndex = i;
   }
   
   if(pawnIndex != -1){
      set_proposition_pawn_selected_color(cm->mm, pawnIndex);
      apply_pixbufs_to_button(button, get_color_image_pixbuf(cm->vm, get_selected_color(cm->mm)), get_mastermind_proposition_button_size(cm->vm));
   }
}


void on_reset_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *)data;

   reset_proposition(cm->mm);
   reset_proposition_buttons(cm);
}


void reset_proposition_buttons(ControllerMastermind *cm) {
   if(cm != NULL && cm->mm != NULL && cm->vm != NULL)
      for(unsigned int i = 0; i < get_nb_pawns(cm->mm); ++i)
         apply_pixbufs_to_button(cm->propositionButtons[i], get_color_image_pixbuf(cm->vm, PAWN_DEFAULT), get_mastermind_proposition_button_size(cm->vm));
}


void on_apply_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *)data;

   if(get_in_game(cm->mm)){
      if(verify_proposition(cm->mm)){
         set_proposition_in_history(cm->mm);
         determine_feedback_last_combination(cm->mm);
         verify_end_game(cm->mm);

         update_last_combination_images(cm->vm, cm->mm);
         udpate_last_feedback_images(cm->vm, cm->mm);

         update_current_combination_index(cm->mm);

         reset_proposition(cm->mm);
         reset_proposition_buttons(cm);
      }
   }
}