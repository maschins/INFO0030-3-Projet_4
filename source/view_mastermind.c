#include <gtk-2.0/gtk/gtk.h>
#include <assert.h>

#include "view_mastermind.h"


struct view_main_menu_t{
   ModelMainMenu *mmm;
   GtkWidget *window;
   GtkWidget *mainVBox;
   GtkWidget *pseudoHBox;
   GtkWidget *nbPawnsHBox;
   GtkWidget *logo;
   GtkWidget *pseudoLabel;
   GtkWidget *errorLabel;
   GtkWidget *nbPawnsLabel;
};


struct view_mastermind_t{
   ModelMastermind *mm;
   unsigned int smallButtonSize;
   unsigned int bigButtonSize;
   unsigned int colorButtonSize;
   unsigned int propositionButtonSize;
   GtkWidget *window;
   GtkWidget *mainVBox;
   GtkWidget *historyTable;
   GtkWidget *propositionHBox;
   GtkWidget *propositionControlHBox;
   GtkWidget *colorSelectionHBox;
   GtkWidget *scoreHBox;
   GdkPixbuf **colorImagePixbufs;
   GdkPixbuf **feedbackImagePixbufs;
   GtkWidget ***historyCombinations;
   GtkWidget ***historyFeedbacks;
   GtkWidget *scoreLabel;
};


ViewMainMenu *create_view_main_menu(ModelMainMenu *mmm) {
   assert(mmm != NULL);

   // Allocate memory for view.
   ViewMainMenu *vmm = malloc(sizeof(ViewMainMenu));
   if(vmm == NULL)
      return NULL;

   vmm->mmm = mmm;

   // Create window
   vmm->window = create_window(MAIN_MENU_WINDOW_LABEL, MAIN_MENU_WINDOW_WIDTH, MAIN_MENU_WINDOW_HEIGHT);
   if(vmm->window == NULL){
      free(vmm);
      return NULL;
   }

   // Create main box
   vmm->mainVBox = gtk_vbox_new(FALSE, 0);
   if(vmm->mainVBox == NULL){
      free(vmm);
      return NULL;
   }

   // Create horizontal box for pseudo stuff.
   vmm->pseudoHBox = gtk_hbox_new(FALSE, 0);
   if(vmm->pseudoHBox == NULL){
      free(vmm);
      return NULL;
   }

   // Create horizontal box for number of pawns stuff.
   vmm->nbPawnsHBox = gtk_hbox_new(FALSE, 0);
   if(vmm->nbPawnsHBox == NULL){
      free(vmm);
      return NULL;
   }

   // Create logo image.
   vmm->logo = create_image(LOGO_PATH, LOGO_WIDTH, LOGO_HEIGHT);
   if(vmm->logo == NULL){
      free(vmm);
      return NULL;
   }

   // Create pseudo label.
   const char *PSEUDO_LABEL = "Pseudo : ";
   vmm->pseudoLabel = gtk_label_new(PSEUDO_LABEL);
   if(vmm->pseudoLabel == NULL){
      free(vmm);
      return NULL;
   }

   // Create error label.
   vmm->errorLabel = gtk_label_new(NULL);
   if(vmm->errorLabel == NULL){
      free(vmm);
      return NULL;
   }

   // Create number of pawns label.
   const char *NB_PAWNS_LABEL = "Number\nof pawns :";
   vmm->nbPawnsLabel = gtk_label_new(NB_PAWNS_LABEL);
   if(vmm->nbPawnsLabel == NULL){
      free(vmm);
      return NULL;
   }

   return vmm;
}


void destroy_view_main_menu(ViewMainMenu *vmm) {
   if(vmm != NULL)
      free(vmm);
}


ViewMastermind *create_view_mastermind(ModelMastermind *mm) {
   assert(mm != NULL);

   ViewMastermind *vm = malloc(sizeof(ViewMastermind));
   if(vm == NULL)
      return NULL;

   vm->mm = mm;

   unsigned int nbCombi = get_nb_combinations(mm);
   unsigned int nbPawns = get_nb_pawns(mm);

   vm->bigButtonSize = MASTERMIND_WINDOW_SIZE * 60;
   vm->smallButtonSize = MASTERMIND_WINDOW_SIZE * 30;
   vm->colorButtonSize = nbPawns * (vm->bigButtonSize + vm->smallButtonSize) / (NB_PAWN_COLORS-1);
   vm->propositionButtonSize = vm->bigButtonSize + vm->smallButtonSize;

   vm->window = create_window(MASTERMIND_WINDOW_LABEL, -1, -1);
   if(vm->window == NULL){
      free(vm);
      return NULL;
   }

   vm->mainVBox = gtk_vbox_new(FALSE, 0);
   if(vm->mainVBox == NULL){
      free(vm);
      return NULL;
   }

   vm->historyTable = gtk_table_new(nbCombi, 2 * nbPawns, FALSE);
   if(vm->historyTable == NULL){
      free(vm);
      return NULL;
   }

   vm->propositionHBox = gtk_hbox_new(FALSE, 0);
   if(vm->propositionHBox == NULL){
      free(vm);
      return NULL;
   }

   vm->propositionControlHBox = gtk_hbox_new(FALSE, 0);
   if(vm->propositionControlHBox == NULL){
      free(vm);
      return NULL;
   }

   vm->colorSelectionHBox = gtk_hbox_new(FALSE, 0);
   if(vm->colorSelectionHBox == NULL){
      free(vm);
      return NULL;
   }

   vm->scoreHBox = gtk_hbox_new(FALSE, 0);
   if(vm->scoreHBox == NULL){
      free(vm);
      return NULL;
   }

   vm->scoreLabel = gtk_label_new("Score: ");
   if(vm->scoreLabel == NULL){
      free(vm);
      return NULL;
   }

   const char *COLOR_IMAGE_FILENAMES[] = {
      "../images/blue.png",
      "../images/cyan.png",
      "../images/green.png",
      "../images/orange.png",
      "../images/purple.png",
      "../images/red.png",
      "../images/yellow.png",
      "../images/default.png",
   };

   const char *FEEDBACK_IMAGE_FILENAMES[] = {
      "../images/black.png",
      "../images/white.png",
      "../images/no_feedback.png"
   };

   vm->colorImagePixbufs = malloc(NB_PAWN_COLORS * sizeof(GdkPixbuf *));
   if(vm->colorImagePixbufs == NULL){
      free(vm);
      return NULL;
   }

   for(unsigned int i = 0; i < NB_PAWN_COLORS; i++){
      vm->colorImagePixbufs[i] = gdk_pixbuf_new_from_file(COLOR_IMAGE_FILENAMES[i], NULL);
      if(vm->colorImagePixbufs[i] == NULL){
         free(vm->colorImagePixbufs);
         free(vm);
         return NULL;
      }
   }

   vm->feedbackImagePixbufs = malloc(NB_FB_COLORS * sizeof(GdkPixbuf *));
   if(vm->feedbackImagePixbufs == NULL){
      free(vm->colorImagePixbufs);
      free(vm);
      return NULL;
   }

   for(unsigned int i = 0; i < NB_FB_COLORS; i++){
      vm->feedbackImagePixbufs[i] = gdk_pixbuf_new_from_file(FEEDBACK_IMAGE_FILENAMES[i], NULL);
      if(vm->feedbackImagePixbufs[i] == NULL){
         free(vm->feedbackImagePixbufs);
         free(vm->colorImagePixbufs);
         free(vm);
         return NULL;
      }
   }

   vm->historyCombinations = malloc(nbCombi * sizeof(GtkWidget **));
   if(vm->historyCombinations == NULL){
      free(vm->feedbackImagePixbufs);
      free(vm->colorImagePixbufs);
      free(vm);
      return NULL;
   }

   for(unsigned int i = 0; i < nbCombi; i++){
      vm->historyCombinations[i] = malloc(nbPawns * sizeof(GtkWidget *));
      if(vm->historyCombinations[i] == NULL){
         for(unsigned int j = 0; j < i; j++)
            free(vm->historyCombinations[j]);

         free(vm->historyCombinations);
         free(vm->feedbackImagePixbufs);
         free(vm->colorImagePixbufs);
         free(vm);
         return NULL;
      }
      for(unsigned int j = 0; j < nbPawns; j++){
         vm->historyCombinations[i][j] = create_button_with_pixbuf(get_color_image_pixbuf(vm, PAWN_DEFAULT), vm->bigButtonSize);
         if(vm->historyCombinations[i][j] == NULL){
            for(unsigned int k = 0; k < i; k++)
               free(vm->historyCombinations[k]);

            free(vm->historyCombinations);
            free(vm->feedbackImagePixbufs);
            free(vm->colorImagePixbufs);
            free(vm);
            return NULL;
         }
      }
   }

   vm->historyFeedbacks = malloc(nbCombi * sizeof(GtkWidget **));
   if(vm->historyFeedbacks == NULL){
      for(unsigned int i = 0; i < nbCombi; i++)
         free(vm->historyCombinations[i]);
      
      free(vm->historyCombinations);
      free(vm->feedbackImagePixbufs);
      free(vm->colorImagePixbufs);
      free(vm);
      return NULL;
   }

   for(unsigned int i = 0; i < nbCombi; i++){
      vm->historyFeedbacks[i] = malloc(nbPawns * sizeof(GtkWidget *));
      if(vm->historyFeedbacks[i] == NULL){
         for(unsigned int j = 0; j < i; j++)
            free(vm->historyFeedbacks[j]);
         
         for(unsigned int j = 0; j < nbCombi; j++)
            free(vm->historyCombinations[j]);
         
         free(vm->historyFeedbacks);
         free(vm->historyCombinations);
         free(vm->feedbackImagePixbufs);
         free(vm->colorImagePixbufs);
         free(vm);
         return NULL;
      }
      for(unsigned int j = 0; j < nbPawns; j++){
         vm->historyFeedbacks[i][j] = create_button_with_pixbuf(get_feedback_image_pixbuf(vm, FB_DEFAULT), vm->smallButtonSize);
         if(vm->historyFeedbacks[i][j] == NULL){
            for(unsigned int k = 0; k < i; k++)
               free(vm->historyFeedbacks[k]);
         
            for(unsigned int k = 0; k < nbCombi; k++)
               free(vm->historyCombinations[k]);

            free(vm->historyFeedbacks);
            free(vm->historyCombinations);
            free(vm->feedbackImagePixbufs);
            free(vm->colorImagePixbufs);
            free(vm);
            return NULL;
         }
      }
   }

   return vm;
}


void destroy_view_mastermind(ViewMastermind *vm) {
   if(vm != NULL){
      unsigned int nbCombi = get_nb_combinations(vm->mm);
      unsigned int nbPawns = get_nb_pawns(vm->mm);

      if(vm->historyCombinations != NULL){
         for(unsigned int i = 0; i < nbCombi; i++)
            if(vm->historyCombinations[i] != NULL)
               free(vm->historyCombinations[i]);

         free(vm->historyCombinations);
      }

      if(vm->historyFeedbacks != NULL){
         for(unsigned int i = 0; i < nbCombi; i++)
            if(vm->historyFeedbacks[i] != NULL)
               free(vm->historyFeedbacks[i]);

         free(vm->historyFeedbacks);
      }

      if(vm->colorImagePixbufs != NULL)
         free(vm->colorImagePixbufs);

      if(vm->feedbackImagePixbufs != NULL)
         free(vm->feedbackImagePixbufs);

      free(vm);
   }
}


GtkWidget *create_window(const char *title, unsigned int width, unsigned int height) {
   GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   if(window == NULL)
      return NULL;

   gtk_window_set_title(GTK_WINDOW(window), title);
   gtk_window_set_default_size(GTK_WINDOW(window), width, height);
   gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

   return window;
}


void apply_pixbufs_to_button(GtkWidget *button, GdkPixbuf *pb, unsigned int size) {
   assert(button != NULL && pb != NULL);

   GdkPixbuf *resizedPixbuf = gdk_pixbuf_scale_simple(pb, size, size, GDK_INTERP_BILINEAR);
   GtkWidget *image = gtk_image_new_from_pixbuf(resizedPixbuf);
   gtk_button_set_image(GTK_BUTTON(button), image);
}


GtkWidget *create_button_with_pixbuf(GdkPixbuf *pb, unsigned int size) {
   assert(pb != NULL);

   GtkWidget *pButton = gtk_button_new();
   if(pButton == NULL)
      return NULL;

   apply_pixbufs_to_button(pButton, pb, size);

   return pButton;
}


GtkWidget *create_image(const char *imagePath, unsigned int width, unsigned int height) {
   assert(imagePath != NULL);

   GdkPixbuf *pb = gdk_pixbuf_new_from_file(imagePath, NULL);
   if(pb == NULL)
      return NULL;

   GdkPixbuf *resizedPb = gdk_pixbuf_scale_simple(pb, width, height, GDK_INTERP_BILINEAR);
   GtkWidget *image = gtk_image_new_from_pixbuf(resizedPb);

   return image;
}


void update_last_combination_images(ViewMastermind *vm, ModelMastermind *mm) {
   assert(vm != NULL && mm != NULL);

   unsigned int index = get_current_index(mm);

   for(unsigned int i = 0; i < get_nb_pawns(mm); i++){
      apply_pixbufs_to_button(vm->historyCombinations[index][i], vm->colorImagePixbufs[get_pawn_last_combination(mm, i)], vm->bigButtonSize);  
   }
}


void udpate_last_feedback_images(ViewMastermind *vm, ModelMastermind *mm) {
   assert(vm != NULL && mm != NULL);

   unsigned int index = get_current_index(mm);
   unsigned int nbPawns = get_nb_pawns(mm);
   unsigned int nbCorrect = get_nb_correct_last_combination(mm);
   unsigned int nbMisplaced = get_nb_misplaced_last_combination(mm);
   
   fprintf(stderr, "%d, %d, %d, %d", index, nbPawns, nbCorrect, nbMisplaced);

   for(unsigned int i = 0; i < nbCorrect; i++)
      apply_pixbufs_to_button(vm->historyFeedbacks[index][i], vm->feedbackImagePixbufs[FB_BLACK], vm->smallButtonSize); 

   for(unsigned int i = nbCorrect; i < nbPawns - nbMisplaced; i++)
      apply_pixbufs_to_button(vm->historyFeedbacks[index][i], vm->feedbackImagePixbufs[FB_WHITE], vm->smallButtonSize);

   for(unsigned int i = nbCorrect + nbMisplaced; i < nbPawns; i++)
      apply_pixbufs_to_button(vm->historyFeedbacks[index][i], vm->feedbackImagePixbufs[FB_DEFAULT], vm->smallButtonSize);
}


GdkPixbuf *get_color_image_pixbuf(ViewMastermind *vm, PAWN_COLOR color) {
   assert(vm != NULL);
   return vm->colorImagePixbufs[color];
}


GdkPixbuf *get_feedback_image_pixbuf(ViewMastermind *vm, FEEDBACK_COLOR color) {
   assert(vm != NULL);
   return vm->feedbackImagePixbufs[color];
}


GtkWidget *get_main_menu_window(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->window;
}


GtkWidget *get_main_menu_main_vbox(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->mainVBox;
}


GtkWidget *get_main_menu_pseudo_hbox(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->pseudoHBox;
}


GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->nbPawnsHBox;
}


GtkWidget *get_main_menu_logo(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->logo;
}


GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->pseudoLabel;
}


GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->nbPawnsLabel;
}


GtkWidget *get_main_menu_error_label(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   return vmm->errorLabel;
}


unsigned int get_mastermind_big_button_size(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->bigButtonSize;
}


unsigned int get_mastermind_small_button_size(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->smallButtonSize;
}


unsigned int get_mastermind_proposition_button_size(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->propositionButtonSize;
}


unsigned int get_mastermind_color_button_size(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->colorButtonSize;
}


GtkWidget *get_mastermind_window(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->window;
}


GtkWidget *get_mastermind_main_vbox(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->mainVBox;
}


GtkWidget *get_mastermind_history_table(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->historyTable;
}


GtkWidget *get_mastermind_proposition_hbox(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->propositionHBox;
}


GtkWidget *get_mastermind_proposition_control_hbox(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->propositionControlHBox;
}


GtkWidget *get_mastermind_color_selection_hbox(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->colorSelectionHBox;
}


GtkWidget *get_mastermind_score_hbox(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->scoreHBox;
}


GtkWidget *get_mastermind_history_combination_button(ViewMastermind *vm, unsigned int i, unsigned int j) {
   assert(vm != NULL && i < get_nb_combinations(vm->mm) && j < get_nb_pawns(vm->mm));
   return vm->historyCombinations[i][j];
}


GtkWidget *get_mastermind_history_feedback_button(ViewMastermind *vm, unsigned int i, unsigned int j) {
   assert(vm != NULL && i < get_nb_combinations(vm->mm) && j < get_nb_pawns(vm->mm));
   return vm->historyFeedbacks[i][j];
}


GtkWidget *get_mastermind_score_label(ViewMastermind *vm) {
   assert(vm != NULL);
   return vm->scoreLabel;
}