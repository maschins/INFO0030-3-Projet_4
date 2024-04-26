#include <gtk-2.0/gtk/gtk.h>
#include <assert.h>

#include "view_mastermind.h"

struct view_main_menu_t{
   ModelMastermind *mm;
   GtkWidget *window;
   GtkWidget *mainVBox;
   GtkWidget *hBoxPseudo;
   GtkWidget **labels;
};


ViewMainMenu *create_view_main_menu(ModelMastermind *mm) {
   assert(mm != NULL);

   ViewMainMenu *vmm = malloc(sizeof(ViewMainMenu));
   if(vmm == NULL)
      return NULL;

   vmm->mm = mm;

   vmm->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   if(vmm->window == NULL){
      free(vmm);
      return NULL;
   }

   g_signal_connect(G_OBJECT(vmm->window), "destroy", G_CALLBACK(destroy_game), NULL);

   vmm->mainVBox = gtk_vbox_new(FALSE, 0);
   if(vmm->mainVBox == NULL){
      free(vmm);
      return NULL;
   }

   vmm->hBoxPseudo = gtk_hbox_new(FALSE, 0);
   if(vmm->hBoxPseudo == NULL){
      free(vmm);
      return NULL;
   }

   vmm->labels = malloc(MAIN_MENU_NB_LABELS * sizeof(GtkWidget *));
   if(vmm->labels == NULL){
      free(vmm);
      return NULL;
   }

   const char *MAIN_MENU_LABELS[MAIN_MENU_NB_LABELS] = {
      "Mastermind",
      "  Pseudo :  "
   };

   for(unsigned int i = 0; i < MAIN_MENU_NB_LABELS; i++){
      vmm->labels[i] = gtk_label_new(MAIN_MENU_LABELS[i]);
      if(vmm->labels[i] == NULL){
         free(vmm->labels);
         free(vmm);
         return NULL;
      }
   }

   return vmm;
}


void destroy_view_main_menu(ViewMainMenu *vmm) {
   if(vmm != NULL){
      if(vmm->labels != NULL)
         free(vmm->labels);
      free(vmm);
   }
}


GtkWidget *get_window(ViewMainMenu *vmm) {
   assert(vmm != NULL);
   
   return vmm->window;
}


GtkWidget *get_main_v_box(ViewMainMenu *vmm) {
   assert(vmm != NULL);

   return vmm->mainVBox;
}


GtkWidget *get_h_box_pseudo(ViewMainMenu *vmm) {
   assert(vmm != NULL);

   return vmm->hBoxPseudo;
}


GtkWidget *get_label(ViewMainMenu *vmm, MainMenuLabel label) {
   assert(vmm != NULL);

   return vmm->labels[label];
}