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


GtkWidget *create_image(const char *imagePath, unsigned int width, unsigned int height) {
   assert(imagePath != NULL);

   GdkPixbuf *pb = gdk_pixbuf_new_from_file(imagePath, NULL);
   if(pb == NULL)
      return NULL;

   GdkPixbuf *resizedPb = gdk_pixbuf_scale_simple(pb, width, height, GDK_INTERP_BILINEAR);
   GtkWidget *image = gtk_image_new_from_pixbuf(resizedPb);

   return image;
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