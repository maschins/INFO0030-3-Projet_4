/**
 * \file main.mastermind.c
 */

#include <gtk-2.0/gtk/gtk.h>

#define WINDOW_NAME "Mastermind"
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

static GtkWidget create_window();


int main(){
   GtkWidget pWindow;

   gtk_init(&argc, &argv);

   pWindow = create_window();
   if(pWindow == NULL)
      return EXIT_FAILURE;

   gtk_widget_show_all(pWindow);

   gtk_main();

   return EXIT_SUCCESS;
}

static GtkWidget create_window(){
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   if(pWindow == NULL)
      return NULL;

   gtk_window_set_title(GTK_WINDOW(pWindow), WINDOW_NAME);
   gtk_window_set_default_size(GTK_WINDOW(pWindow), WINDOW_WIDTH, WINDOW_HEIGHT);

   return pWindow;
}