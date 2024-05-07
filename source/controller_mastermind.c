/**
 * \file controller_mastermind.c
 * \brief Controller file of matsermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 06/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern controller for the mastermind game.
 * 
 * */

#include <gtk-2.0/gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "controller_mastermind.h"

struct controller_main_menu_t {
   ModelMainMenu *mmm;        /*!< Main menu model */
   ViewMainMenu *vmm;         /*!< Main menu view */
   GtkWidget *pseudoEntry;    /*!< Pseudo text entry box */
   GtkWidget *saveButton;     /*!< Save pseudo buttin */
   GtkWidget *guesserButton;  /*!< Guesser mode button */
   GtkWidget *proposerButton; /*!< Proposer mode button */
   GtkWidget *nbPawnsSlider;  /*!< Number of pawns slider */
   GtkWidget *playButton;     /*!< Play button */
   GtkWidget *quitButton;     /*!< Quit button */
};


struct menu_bar_t {
   GtkWidget *bar;            /*!< Bar of menu bar */
   GtkWidget *menuGame;       /*!< Game submenu */
   GtkWidget *menuHelp;       /*!< Help submenu */
   GtkWidget *itemGame;       /*!< Game submenu button */
   GtkWidget *itemHelp;       /*!< Help submenu button */
   GtkWidget *itemMainMenu;   /*!< Main menu Game submenu button */
   GtkWidget *itemScore;      /*!< Score Game submenu button */
   GtkWidget *itemQuit;       /*!< Quit Game submenu button */
   GtkWidget *itemAbouts;     /*!< Abouts Help submenu button */
};


struct controller_mastermind_t {
   ControllerMainMenu *cmm;            /*!< Main menu controller */
   ModelMastermind *mm;                /*!< Mastermind model */
   ViewMastermind *vm;                 /*!< Mastermind view */
   GtkWidget *aboutsOkayButton;        /*!< Abouts okay button */
   GtkWidget *scoreOkayButton;         /*!< Score okay button */
   MenuBar *menuBar;                   /*!< Menu bar */
   GtkWidget *applyButton;             /*!< Apply button */
   GtkWidget *resetButton;             /*!< Reset button */
   GtkWidget **colorSelectionButtons;  /*!< Color seleciton buttons */
   GtkWidget **propositionButtons;     /*!< Proposition selection buttons */
   GtkWidget **feedbackButtons;        /*!< Feedback buttons */
};

/**
 * \fn static void handle_quit(GtkWidget *button, gpointer data)
 * \brief Handles quitting the game
 *
 * \param button pointer on the button that was used to quit
 * \param data needed data to quit the game
 *
 * \pre button != NULL, data != NULL
 * \post the score is saved in the file and the game is quit
 */
static void handle_quit(GtkWidget *button, gpointer data);


ControllerMainMenu *
create_controller_main_menu(ModelMainMenu *mmm, ViewMainMenu *vmm) {
   assert(mmm != NULL && vmm != NULL);

   ControllerMainMenu *cmm = malloc(sizeof(ControllerMainMenu));
   if(cmm == NULL)
      return NULL;

   cmm->mmm = mmm;
   cmm->vmm = vmm;

   cmm->pseudoEntry = gtk_entry_new();
   if(cmm->pseudoEntry == NULL){
      free(cmm);
      return NULL;
   }

   cmm->saveButton = gtk_button_new_with_label(SAVE_BUTTON_LABEL);
   if(cmm->saveButton == NULL){
      free(cmm);
      return NULL;
   }

   cmm->guesserButton = gtk_radio_button_new_with_label(NULL,
                                                        GUESSER_BUTTON_LABEL);
   if(cmm->guesserButton == NULL){
      free(cmm);
      return NULL;
   }

   cmm->proposerButton = gtk_radio_button_new_with_label_from_widget(
           GTK_RADIO_BUTTON(cmm->guesserButton), PROPOSER_BUTTON_LABEL);
   if(cmm->proposerButton == NULL){
      free(cmm);
      return NULL;
   }

   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cmm->guesserButton), TRUE);

   cmm->nbPawnsSlider = gtk_hscale_new_with_range(MIN_NB_PAWNS, MAX_NB_PAWNS,
                                                  1);
   gtk_range_set_value(GTK_RANGE(cmm->nbPawnsSlider), DEFAULT_NB_PAWNS);
   gtk_scale_set_digits(GTK_SCALE(cmm->nbPawnsSlider), 0);
   gtk_scale_set_value_pos(GTK_SCALE(cmm->nbPawnsSlider), GTK_POS_TOP);
   gtk_scale_set_draw_value(GTK_SCALE(cmm->nbPawnsSlider), TRUE);

   cmm->playButton = gtk_button_new_with_label(PLAY_BUTTON_LABEL);
   if(cmm->playButton == NULL){
      free(cmm);
      return NULL;
   }

   cmm->quitButton = gtk_button_new_with_label(QUIT_BUTTON_LABEL);
   if(cmm->quitButton == NULL){
      free(cmm);
      return NULL;
   }

   return cmm;
}


void destroy_controller_main_menu(ControllerMainMenu *cmm) {
   if(cmm != NULL)
      free(cmm);
}


ControllerMastermind *
create_controller_mastermind(ModelMastermind *mm, ViewMastermind *vm,
                             ControllerMainMenu *cmm) {
   assert(vm != NULL && mm != NULL);

   ControllerMastermind *cm = malloc(sizeof(ControllerMastermind));
   if(cm == NULL)
      return NULL;

   cm->cmm = cmm;
   cm->mm = mm;
   cm->vm = vm;

   const char *OKAY_BUTTON_LABEL = "Okay";
   cm->aboutsOkayButton = gtk_button_new_with_label(OKAY_BUTTON_LABEL);
   if(cm->aboutsOkayButton == NULL){
      free(cm);
      return NULL;
   }

   cm->scoreOkayButton = gtk_button_new_with_label(OKAY_BUTTON_LABEL);
   if(cm->scoreOkayButton == NULL){
      free(cm);
      return NULL;
   }

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


   cm->menuBar = create_menu_bar();
   if(cm->menuBar == NULL){
      free(cm);
      return NULL;
   }

   cm->colorSelectionButtons = malloc((NB_PAWN_COLORS - 1) *
                                      sizeof(GtkWidget * )); // -1 because default color is not selectable.
   if(cm->colorSelectionButtons == NULL){
      free(cm->menuBar);
      free(cm);
      return NULL;
   }

   for(unsigned int i = 0; i < NB_PAWN_COLORS - 1; i++){
      cm->colorSelectionButtons[i] = create_button_with_pixbuf(
              get_color_image_pixbuf(vm, i),
              get_mastermind_color_button_size(vm));
      if(cm->colorSelectionButtons[i] == NULL){
         free(cm->colorSelectionButtons);
         free(cm->menuBar);
         free(cm);
         return NULL;
      }
   }

   cm->propositionButtons = malloc(get_nb_pawns(mm) * sizeof(GtkWidget * ));
   if(cm->propositionButtons == NULL){
      free(cm->colorSelectionButtons);
      free(cm->menuBar);
      free(cm);
      return NULL;
   }

   for(unsigned int i = 0; i < get_nb_pawns(mm); i++){
      cm->propositionButtons[i] = create_button_with_pixbuf(
              get_color_image_pixbuf(vm, PAWN_DEFAULT),
              get_mastermind_proposition_button_size(vm));
      if(cm->propositionButtons[i] == NULL){
         free(cm->propositionButtons);
         free(cm->colorSelectionButtons);
         free(cm->menuBar);
         free(cm);
         return NULL;
      }
   }

   cm->feedbackButtons = malloc(get_nb_pawns(mm) * sizeof(GtkWidget * ));
   if(cm->feedbackButtons == NULL){
      free(cm->colorSelectionButtons);
      free(cm->propositionButtons);
      free(cm->menuBar);
      free(cm);
   }

   for(unsigned int i = 0; i < get_nb_pawns(mm); i++){
      cm->feedbackButtons[i] = create_button_with_pixbuf(
              get_feedback_image_pixbuf(vm, FB_DEFAULT),
              get_mastermind_proposition_button_size(vm));
      if(cm->feedbackButtons[i] == NULL){
         free(cm->feedbackButtons);
         free(cm->propositionButtons);
         free(cm->colorSelectionButtons);
         free(cm->menuBar);
         free(cm);
         return NULL;
      }
   }

   return cm;
}


void destroy_controller_mastermind(ControllerMastermind *cm) {
   if(cm != NULL){
      if(cm->menuBar != NULL)
         free(cm->menuBar);

      if(cm->colorSelectionButtons != NULL)
         free(cm->colorSelectionButtons);

      if(cm->propositionButtons != NULL)
         free(cm->propositionButtons);

      if(cm->feedbackButtons != NULL)
         free(cm->feedbackButtons);

      free(cm);
   }
}


MenuBar *create_menu_bar(void) {
   MenuBar *menuBar = malloc(sizeof(MenuBar));
   if(menuBar == NULL)
      return NULL;

   menuBar->bar = gtk_menu_bar_new();
   if(menuBar->bar == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->menuGame = gtk_menu_new();
   if(menuBar->menuGame == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->menuHelp = gtk_menu_new();
   if(menuBar->menuHelp == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemGame = gtk_menu_item_new_with_label(BAR_GAME_ITEM_LABEL);
   if(menuBar->itemGame == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemHelp = gtk_menu_item_new_with_label(BAR_HELP_ITEM_LABEL);
   if(menuBar->itemHelp == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemMainMenu = gtk_menu_item_new_with_label(
           MENU_GAME_MAIN_MENU_ITEM_LABEL);
   if(menuBar->itemMainMenu == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemScore = gtk_menu_item_new_with_label(
           MENU_GAME_SCORE_ITEM_LABEL);
   if(menuBar->itemScore == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemQuit = gtk_menu_item_new_with_label(MENU_GAME_QUIT_ITEM_LABEL);
   if(menuBar->itemQuit == NULL){
      free(menuBar);
      return NULL;
   }

   menuBar->itemAbouts = gtk_menu_item_new_with_label(
           MENU_HELP_ABOUTS_ITEM_LABEL);
   if(menuBar->itemAbouts == NULL){
      free(menuBar);
      return NULL;
   }

   gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuBar->itemGame),
                             menuBar->menuGame);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuBar->itemHelp),
                             menuBar->menuHelp);

   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->bar), menuBar->itemGame);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->bar), menuBar->itemHelp);

   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuGame),
                         menuBar->itemMainMenu);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuGame), menuBar->itemScore);
   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuGame), menuBar->itemQuit);

   gtk_menu_shell_append(GTK_MENU_SHELL(menuBar->menuHelp),
                         menuBar->itemAbouts);

   return menuBar;
}


void init_main_menu(ControllerMainMenu *cmm) {
   assert(cmm != NULL);

   GtkWidget *window = get_main_menu_window(cmm->vmm);
   GtkWidget *mainVBox = get_main_menu_main_vbox(cmm->vmm);
   GtkWidget *pseudoHBox = get_main_menu_pseudo_hbox(cmm->vmm);
   GtkWidget *nbPawnsHBox = get_main_menu_nb_pawns_hbox(cmm->vmm);

   gtk_container_add(GTK_CONTAINER(window), mainVBox);
   gtk_box_pack_start(GTK_BOX(mainVBox), get_main_menu_logo(cmm->vmm), TRUE,
                      TRUE, 10);

   gtk_container_add(GTK_CONTAINER(mainVBox), nbPawnsHBox);
   gtk_box_pack_start(GTK_BOX(nbPawnsHBox),
                      get_main_menu_nb_pawns_label(cmm->vmm), FALSE, FALSE, 10);
   gtk_box_pack_start(GTK_BOX(nbPawnsHBox), cmm->nbPawnsSlider, TRUE, TRUE, 0);

   const int smallFontSize = 9;
   PangoFontDescription *font_desc = pango_font_description_new();
   pango_font_description_set_family(font_desc, "sans");

   gtk_container_add(GTK_CONTAINER(mainVBox), pseudoHBox);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), get_main_menu_pseudo_label(cmm->vmm),
                      TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), cmm->pseudoEntry, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(pseudoHBox), cmm->saveButton, TRUE, TRUE, 0);

   gtk_box_pack_start(GTK_BOX(mainVBox), get_main_menu_error_label(cmm->vmm),
                      TRUE, TRUE, 0);
   // Small font for error message.
   pango_font_description_set_size(font_desc, smallFontSize * PANGO_SCALE);
   gtk_widget_modify_font(get_main_menu_error_label(cmm->vmm), font_desc);
   pango_font_description_free(font_desc);
   gtk_misc_set_alignment(GTK_MISC(get_main_menu_error_label(cmm->vmm)), 0.5,
                          0.5);

   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->guesserButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->proposerButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->playButton, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(mainVBox), cmm->quitButton, TRUE, TRUE, 0);

   // Connect signals.
   g_signal_connect(G_OBJECT(cmm->nbPawnsSlider), "value-changed",
                    G_CALLBACK(on_nb_pawns_slider_changed), cmm);
   g_signal_connect(G_OBJECT(cmm->playButton), "clicked",
                    G_CALLBACK(on_play_clicked), cmm);
   g_signal_connect(G_OBJECT(cmm->guesserButton), "clicked",
                    G_CALLBACK(on_guesser_choosed), cmm);
   g_signal_connect(G_OBJECT(cmm->proposerButton), "clicked",
                    G_CALLBACK(on_proposer_choosed), cmm);
   g_signal_connect(G_OBJECT(cmm->saveButton), "clicked",
                    G_CALLBACK(on_save_button_clicked), cmm);
   g_signal_connect(G_OBJECT(cmm->quitButton), "clicked",
                    G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                    NULL);

   gtk_widget_show_all(window);
}


void init_mastermind(ControllerMastermind *cm) {
   assert(cm != NULL);

   GtkWidget *aboutsWindow = get_mastermind_abouts_window(cm->vm);
   GtkWidget *aboutsMainVBox = get_abouts_main_vbox(cm->vm);

   GtkWidget *scoreWindow = get_mastermind_score_window(cm->vm);
   GtkWidget *scoreMainVBox = get_score_main_vbox(cm->vm);

   GtkWidget *window = get_mastermind_window(cm->vm);
   GtkWidget *mainVBox = get_mastermind_main_vbox(cm->vm);
   GtkWidget *historyTable = get_mastermind_history_table(cm->vm);
   GtkWidget *propositionHBox = get_mastermind_proposition_hbox(cm->vm);
   GtkWidget *propositionControlHBox = get_mastermind_proposition_control_hbox(
           cm->vm);
   GtkWidget *colorSelectionHBox = get_mastermind_color_selection_hbox(cm->vm);
   GtkWidget *scoreHBox = get_mastermind_score_hbox(cm->vm);

   gtk_box_pack_start(GTK_BOX(aboutsMainVBox),
                      get_mastermind_abouts_label(cm->vm), TRUE, TRUE, 10);
   gtk_box_pack_start(GTK_BOX(aboutsMainVBox), cm->aboutsOkayButton, FALSE,
                      FALSE, 10);

   gtk_box_pack_start(GTK_BOX(scoreMainVBox),
                      get_mastermind_scores_title_label(cm->vm), TRUE, TRUE,
                      10);

   unsigned size = (get_saved_scores_length(cm->mm) < MAX_SCORE_DISPLAYED)
                   ? get_saved_scores_length(cm->mm) : MAX_SCORE_DISPLAYED;

   for(unsigned i = 0; i < size; i++)
      gtk_box_pack_start(GTK_BOX(scoreMainVBox),
                         get_mastermind_players_scores_label(cm->vm)[i], TRUE,
                         TRUE, 10);

   gtk_box_pack_start(GTK_BOX(scoreMainVBox), cm->scoreOkayButton, FALSE, FALSE,
                      10);

   unsigned int nbCombi = get_nb_combinations(cm->mm);
   unsigned int nbPawns = get_nb_pawns(cm->mm);

   for(unsigned int i = 0; i < nbCombi; i++){
      for(unsigned int j = 0; j < nbPawns; j++){
         gtk_table_attach_defaults(GTK_TABLE(historyTable),
                                   get_mastermind_history_combination_button(
                                           cm->vm, i, j), j, j + 1, i, i + 1);
         gtk_table_attach(GTK_TABLE(historyTable),
                          get_mastermind_history_feedback_button(cm->vm, i, j),
                          nbPawns + j, nbPawns + j + 1, i, i + 1, 0, 0, 0, 0);
      }
   }

   for(unsigned int i = 0; i < nbPawns; i++){
      gtk_box_pack_start(GTK_BOX(propositionHBox), cm->propositionButtons[i],
                         TRUE, TRUE, 0);
      g_signal_connect(G_OBJECT(cm->propositionButtons[i]), "clicked",
                       G_CALLBACK(on_proposition_button_clicked), cm);
   }

   gtk_box_pack_start(GTK_BOX(propositionControlHBox), cm->applyButton, TRUE,
                      TRUE, 0);
   gtk_box_pack_start(GTK_BOX(propositionControlHBox), cm->resetButton, TRUE,
                      TRUE, 0);

   for(unsigned int i = 0; i < NB_PAWN_COLORS - 1; i++){
      g_signal_connect(G_OBJECT(cm->colorSelectionButtons[i]), "clicked",
                       G_CALLBACK(on_color_picked), cm);
      gtk_box_pack_start(GTK_BOX(colorSelectionHBox),
                         cm->colorSelectionButtons[i], TRUE, TRUE, 0);
   }

   GtkWidget *scoreAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
   gtk_box_pack_start(GTK_BOX(scoreHBox), scoreAlignment, TRUE, TRUE, 0);
   gtk_container_add(GTK_CONTAINER(scoreAlignment),
                     get_mastermind_score_label(cm->vm));
   gtk_container_add(GTK_CONTAINER(aboutsWindow), aboutsMainVBox);
   gtk_container_add(GTK_CONTAINER(scoreWindow), scoreMainVBox);

   gtk_container_add(GTK_CONTAINER(mainVBox), cm->menuBar->bar);
   gtk_container_add(GTK_CONTAINER(mainVBox), historyTable);
   gtk_container_add(GTK_CONTAINER(mainVBox), propositionHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), propositionControlHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), colorSelectionHBox);
   gtk_container_add(GTK_CONTAINER(mainVBox), scoreHBox);
   gtk_container_add(GTK_CONTAINER(window), mainVBox);

   // Connect signals
   g_signal_connect(G_OBJECT(cm->aboutsOkayButton), "clicked",
                    G_CALLBACK(hide_window), aboutsWindow);
   g_signal_connect(G_OBJECT(cm->scoreOkayButton), "clicked",
                    G_CALLBACK(hide_window), scoreWindow);

   g_signal_connect(G_OBJECT(cm->menuBar->itemMainMenu), "activate",
                    G_CALLBACK(on_main_menu_clicked), cm);
   g_signal_connect(G_OBJECT(cm->menuBar->itemQuit), "activate",
                    G_CALLBACK(handle_quit), cm);
   g_signal_connect(G_OBJECT(cm->menuBar->itemAbouts), "activate",
                    G_CALLBACK(show_window), aboutsWindow);
   g_signal_connect(G_OBJECT(cm->menuBar->itemScore), "activate",
                    G_CALLBACK(show_window), scoreWindow);
   g_signal_connect(G_OBJECT(cm->applyButton), "clicked",
                    G_CALLBACK(on_apply_clicked), cm);
   g_signal_connect(G_OBJECT(cm->resetButton), "clicked",
                    G_CALLBACK(on_reset_clicked), cm);
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(handle_quit), cm);
   g_signal_connect(G_OBJECT(aboutsWindow), "destroy", G_CALLBACK(hide_window),
                    aboutsWindow);
   g_signal_connect(G_OBJECT(scoreWindow), "destroy", G_CALLBACK(hide_window),
                    scoreWindow);

   gtk_widget_show_all(window);
}


void init_feedback_zone_mastermind(ControllerMastermind *cm) {
   assert(cm != NULL);

   GtkWidget *mainVBox = get_mastermind_main_vbox(cm->vm);
   GtkWidget *hbox = get_mastermind_feedback_zone_hbox(cm->vm);

   gtk_container_remove(GTK_CONTAINER(mainVBox),
                        get_mastermind_color_selection_hbox(cm->vm));
   gtk_container_add(GTK_CONTAINER(mainVBox), hbox);

   for(unsigned int i = 0; i < get_nb_pawns(cm->mm); i++){
      gtk_box_pack_start(GTK_BOX(hbox), cm->feedbackButtons[i], TRUE, TRUE, 0);
      g_signal_connect(G_OBJECT(cm->feedbackButtons[i]), "clicked",
                       G_CALLBACK(on_feedback_button_clicked), cm);
   }

   gtk_widget_show_all(get_mastermind_window(cm->vm));
}


void init_end_game_window(ControllerMastermind *cm, bool win) {
   assert(cm != NULL);

   GtkWidget *window = get_mastermind_end_game_window(cm->vm);
   GdkPixbuf *pb;

   if((!win && get_role(cm->mm) == PROPOSER && get_nb_correct_last_combination(cm->mm) < get_nb_pawns(cm->mm)) || (win && get_role(cm->mm) == GUESSER))
      pb = gdk_pixbuf_scale_simple(get_mastermind_win_image(cm->vm), END_GAME_WINDOW_WIDTH, END_GAME_WINDOW_HEIGHT, GDK_INTERP_BILINEAR);

   else
      pb = gdk_pixbuf_scale_simple(get_mastermind_loose_image(cm->vm), END_GAME_WINDOW_WIDTH, END_GAME_WINDOW_HEIGHT, GDK_INTERP_BILINEAR);

   gtk_container_add(GTK_CONTAINER(window), gtk_image_new_from_pixbuf(pb));
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(hide_window), window);
   gtk_widget_show_all(window);
}


void show_window(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   GtkWidget *window = (GtkWidget *) data;

   gtk_widget_show_all(window);
}


void hide_window(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   GtkWidget *window = (GtkWidget *) data;

   gtk_widget_hide(window);
}


void on_nb_pawns_slider_changed(GtkWidget *slider, gpointer data) {
   assert(slider != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *) data;

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

   ControllerMainMenu *cmm = (ControllerMainMenu *) data;
   const char *pseudo = gtk_entry_get_text(GTK_ENTRY(cmm->pseudoEntry));

   if(strlen(pseudo) > MAX_PSEUDO_LENGTH){
      const char *PSEUDO_TOO_LONG_ERROR = "Pseudo is too long (Max 50 char).";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)),
                         PSEUDO_TOO_LONG_ERROR);
   } else if(strlen(pseudo) < MIN_PSEUDO_LENGTH){
      const char *PSEUDO_TOO_SHORT_ERROR = "Pseudo is too short (Min 5 char).";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)),
                         PSEUDO_TOO_SHORT_ERROR);
   } else{
      const char *PSEUDO_GOOD = "Pseudo saved !";
      gtk_label_set_text(GTK_LABEL(get_main_menu_error_label(cmm->vmm)),
                         PSEUDO_GOOD);
      set_pseudo(cmm->mmm, (char *) pseudo);
   }
}


void on_play_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMainMenu *cmm = (ControllerMainMenu *) data;

   ModelMastermind *mm = create_model_mastermind(cmm->mmm);
   if(mm == NULL)
      gtk_main_quit();


   ViewMastermind *vm = create_view_mastermind(mm);
   if(vm == NULL){
      destroy_model_mastermind(mm);
      gtk_main_quit();
   }

   ControllerMastermind *cm = create_controller_mastermind(mm, vm, cmm);
   if(cm == NULL){
      destroy_view_mastermind(vm);
      destroy_model_mastermind(mm);
      gtk_main_quit();
   }

   gtk_widget_hide(get_main_menu_window(cmm->vmm));

   generate_random_solution(mm);

   init_mastermind(cm);
}


void on_main_menu_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   write_scores(get_saved_scores(cm->mm), SAVED_SCORES_PATH);

   hide_window(button, get_mastermind_end_game_window(cm->vm));
   hide_window(button, get_mastermind_window(cm->vm));
   show_window(button, get_main_menu_window(cm->cmm->vmm));

   ModelMastermind *mm = cm->mm;
   ViewMastermind *vm = cm->vm;

   destroy_controller_mastermind(cm);
   destroy_view_mastermind(vm);
   destroy_model_mastermind(mm);
}


void on_color_picked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   int newColor = -1;
   for(unsigned int i = 0; newColor == -1 && i < NB_PAWN_COLORS - 1; i++)
      if(cm->colorSelectionButtons[i] == button)
         newColor = (int) i;

   if(newColor != -1)
      set_selected_color(cm->mm, newColor);
}


void on_proposition_button_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   if(get_role(cm->mm) == GUESSER ||
      (get_role(cm->mm) == PROPOSER && !get_valid_solution(cm->mm))){
      int pawnIndex = -1;
      for(unsigned int i = 0; pawnIndex == -1 && i < get_nb_pawns(cm->mm); i++){
         if(cm->propositionButtons[i] == button)
            pawnIndex = (int) i;
      }

      if(pawnIndex != -1){
         set_proposition_pawn_selected_color(cm->mm, pawnIndex);
         apply_pixbufs_to_button(button, get_color_image_pixbuf(cm->vm,
                                                                get_selected_color(
                                                                        cm->mm)),
                                 get_mastermind_proposition_button_size(
                                         cm->vm));
      }
   }
}


void on_reset_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   if(!get_valid_solution(cm->mm)){
      reset_proposition(cm->mm);
      reset_proposition_buttons(cm);
   } else if(get_role(cm->mm) == PROPOSER){
      reset_feedback(cm->mm);
      reset_feedback_buttons(cm);
   }
}


void reset_proposition_buttons(ControllerMastermind *cm) {
   if(cm != NULL)
      for(unsigned int i = 0; i < get_nb_pawns(cm->mm); ++i)
         apply_pixbufs_to_button(cm->propositionButtons[i],
                                 get_color_image_pixbuf(cm->vm, PAWN_DEFAULT),
                                 get_mastermind_proposition_button_size(
                                         cm->vm));
}


void reset_feedback_buttons(ControllerMastermind *cm) {
   if(cm != NULL)
      for(unsigned int i = 0; i < get_nb_pawns(cm->mm); ++i)
         apply_pixbufs_to_button(cm->feedbackButtons[i],
                                 get_feedback_image_pixbuf(cm->vm, FB_DEFAULT),
                                 get_mastermind_proposition_button_size(
                                         cm->vm));
}


void on_apply_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   if(get_in_game(cm->mm)){
      if(get_role(cm->mm) == GUESSER){
         if(verify_proposition(cm->mm)){
            determine_feedback_proposition(cm->mm, get_proposition(cm->mm),
                                           get_solution(cm->mm));
            set_proposition_in_history(cm->mm);
            verify_end_game(cm->mm);

            update_last_combination_images(cm->vm, cm->mm);
            udpate_last_feedback_images(cm->vm, cm->mm);

            update_current_combination_index(cm->mm);

            reset_proposition(cm->mm);
            reset_proposition_buttons(cm);
         }
      } else{
         if(get_valid_solution(cm->mm)){
            update_last_combination_feedback(cm->mm);
            udpate_last_feedback_images(cm->vm, cm->mm);
            verify_end_game(cm->mm);

            reset_feedback(cm->mm);
            reset_feedback_buttons(cm);
            update_current_combination_index(cm->mm);

            if(get_in_game(cm->mm)){
               find_next_proposition(cm->mm);
               set_proposition_in_history(cm->mm);
               update_last_combination_images(cm->vm, cm->mm);
            }
         }

         if(!get_valid_solution(cm->mm)){
            if(verify_proposition(cm->mm)){
               set_proposition_as_solution(cm->mm);
               init_feedback_zone_mastermind(cm);
               set_valid_solution_true(cm->mm);

               // Find first combination.
               find_next_proposition(cm->mm);
               set_proposition_in_history(cm->mm);
               update_last_combination_images(cm->vm, cm->mm);
            }
         }
      }

      char new_label[MAX_PSEUDO_LENGTH];
      sprintf(new_label, "Score: %d", 9 - get_current_index(cm->mm));
      set_score_label_text(get_mastermind_score_label(cm->vm), new_label);

      if(!get_in_game(cm->mm))
         init_end_game_window(cm, get_current_index(cm->mm) >= 0);
   }
}


void on_feedback_button_clicked(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   int pawnIndex = -1;
   for(unsigned int i = 0; pawnIndex == -1 && i < get_nb_pawns(cm->mm); i++){
      if(cm->feedbackButtons[i] == button)
         pawnIndex = (int) i;
   }

   if(pawnIndex != -1){
      set_feedback_pawn(cm->mm, pawnIndex);
      apply_pixbufs_to_button(button, get_feedback_image_pixbuf(cm->vm,
                                                                get_feedback_pawn(
                                                                        cm->mm,
                                                                        pawnIndex)),
                              get_mastermind_proposition_button_size(cm->vm));
   }
}

static void handle_quit(GtkWidget *button, gpointer data) {
   assert(button != NULL && data != NULL);

   ControllerMastermind *cm = (ControllerMastermind *) data;

   write_scores(get_saved_scores(cm->mm), SAVED_SCORES_PATH);

   ModelMastermind *mm = cm->mm;
   ViewMastermind *vm = cm->vm;

   destroy_controller_mastermind(cm);
   destroy_view_mastermind(vm);
   destroy_model_mastermind(mm);

   gtk_main_quit();
}
