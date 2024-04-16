/**
 * \file main.mastermind.c
 * \brief The main file containing the main() function
 *
 * \authors Thomas Fraiponts (s2301865) and Martin Schins (s220635)
 * \date 16/04/2024
 */

#include <stdlib.h>
#include <gtk-2.0/gtk/gtk.h>

#define WINDOW_NAME "Mastermind"
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

/**
 * \fn static GtkWidget *create_window(void)
 * \brief Creates a window with a quit function
 *
 * \return A pointer on the window if success
 *         NULL if error
 */
static GtkWidget *create_window(void);


int main(int argc, char **argv){
   GtkWidget *pWindow;

   gtk_init(&argc, &argv);

   pWindow = create_window();
   if(pWindow == NULL)
      return EXIT_FAILURE;

   gtk_widget_show_all(pWindow);

   gtk_main();

   return EXIT_SUCCESS;
}

static GtkWidget *create_window(void) {
   GtkWidget *pW = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   if (pW == NULL)
      return NULL;
   gtk_window_set_title(GTK_WINDOW(pW), WINDOW_NAME);
   gtk_window_set_default_size(GTK_WINDOW(pW), WINDOW_WIDTH, WINDOW_HEIGHT);

   g_signal_connect(G_OBJECT(pW), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   return pW;
}//End create_window()