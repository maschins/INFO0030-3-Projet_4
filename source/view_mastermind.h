/**
 * \file view_mastermind.h
 * \brief View header of mastermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 06/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern view header for the mastermind game.
 * 
 * */

#ifndef __VIEW_MASTERMIND__
#define __VIEW_MASTERMIND__

#include "model_mastermind.h"

/**
 * \brief Main menu window label
 */
#define MAIN_MENU_WINDOW_LABEL "Main menu"

/**
 * \brief Main menu window width
 */
#define MAIN_MENU_WINDOW_WIDTH 400

/**
 * \brief Main menu window height
 */
#define MAIN_MENU_WINDOW_HEIGHT 800

/**
 * \brief Game window label
 */
#define MASTERMIND_WINDOW_LABEL "Mastermind"

/**
 * \brief Game window size scale (Width & Height are fixed for good game render)
 */
#define MASTERMIND_WINDOW_SIZE 0.8

/**
 * \brief Abouts window label
 */
#define ABOUTS_WINDOW_LABEL "Abouts"

/**
 * \brief Scores window label
 */
#define SCORES_WINDOW_LABEL "Scores"

/**
 * \brief End game window label
 */
#define END_GAME_WINDOW_LABEL "End game"

/**
 * \brief End game window width
 */
#define END_GAME_WINDOW_WIDTH 200

/**
 * \brief End game window height
 */
#define END_GAME_WINDOW_HEIGHT 150

/**
 * \brief Main menu logo path
 */
#define LOGO_PATH "./images/title.png"

/**
 * Declare the ViewMainMenu opaque type.
 * */
typedef struct view_main_menu_t ViewMainMenu;

/**
 * Declare the ViewMastermind opaque type.
 * */
typedef struct view_mastermind_t ViewMastermind;


/**
 * \fn ViewMainMenu *create_view_main_menu(ModelMainMenu *mmm)
 * \brief Creates ViewMainMenu structure
 *
 * \param mmm Pointer on the ModelMainMenu structure containing necessary data
 *
 * \pre mmm != NULL
 * \post Memory is allocated and structure is initialized
 *
 * \return A pointer on the ViewMainMenu structure,
 *         NULL if fail
 */
ViewMainMenu *create_view_main_menu(ModelMainMenu *mmm);


/**
 * \fn void destroy_view_main_menu(ViewMainMenu *vmm)
 * \brief free the given ViewMainMenu structure
 *
 * \param vmm ViewMainMenu structure that needs to be freed
 *
 * \pre vmm != NULL
 * \post vmm is freed
 */
void destroy_view_main_menu(ViewMainMenu *vmm);


/**
 * \fn ModelMastermind *create_view_mastermind(ModelMainMenu *mmm);
 * \brief Creates ViewMastermind structure with menu values and default values.
 *
 * \param mm Pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post Memory is allocated and structure is initialized.
 *
 * \return A pointer to ViewMastermind structure,
 *         NULL if memory allocation fails.
 */
ViewMastermind *create_view_mastermind(ModelMastermind *mm);


/**
 * \fn void destroy_view_mastermind(ViewMastermind *vm)
 * \brief free the given ViewMastermind structure
 *
 * \param vm ViewMastermind structure that needs to be freed
 *
 * \pre vm != NULL
 * \post vm is freed
 */
void destroy_view_mastermind(ViewMastermind *vm);


/**
 * \fn GtkWidget *
 * create_window(const char *title, unsigned int width, unsigned int height)
 * \brief creates a window with the given parameters
 *
 * \param title The name of the window
 * \param width Width of the window
 * \param height Height of the windwo
 *
 * \pre title != NULL
 * \post the function returns a window with the given title, height and width
 *
 * \return A pointer to the created window,
 *         NULL if fail
 */
GtkWidget *
create_window(const char *title, unsigned int width, unsigned int height);


/**
 * \fn void apply_pixbufs_to_button(GtkWidget *button, GdkPixbuf *pb,
 * unsigned int size)
 * \brief Puts a pixbuf (image) in a button
 *
 * \param button A pointer on the button that should contain the image
 * \param pb A pointer on the pixbuf that should be transformed into an image
 * \param size the size of the side of the button (square)
 *
 * \pre button != NULL, pb != NULL
 * \post the button contains the given image and has the given size
 */
void
apply_pixbufs_to_button(GtkWidget *button, GdkPixbuf *pb, unsigned int size);


/**
 * \fn GtkWidget *create_button_with_pixbuf(GdkPixbuf *pb, unsigned int size)
 * \brief creates a square button with an image in it
 *
 * \param pb A pointer on the pixbuf that should be transformed into an image
 * \param size The size of the side of the button (square)
 *
 * \pre pb != NULL
 * \post The function returns a square button with the given size containing
 * the given image
 *
 * \return A pointer on the created button,
 *         NULL if fail
 */
GtkWidget *create_button_with_pixbuf(GdkPixbuf *pb, unsigned int size);


/**
 * \fn GtkWidget *create_image(const char *imagePath, unsigned int width,
 * unsigned int height)
 * \brief creates an image of a given width and height
 *
 * \param imagePath A string containing the path of the image in the files
 * \param width The width of the image
 * \param height The height of the image
 *
 * \pre imagePath != NULL
 * \post The function return an gtk image from given width and height
 *
 * \return A pointer on the created image
 *         NULL if fails
 */
GtkWidget *
create_image(const char *imagePath, unsigned int width, unsigned int height);


/**
 * \fn void update_last_combination_images(ViewMastermind *vm,
 * ModelMastermind *mm)
 * \brief Updates the buttons of the last combination to put the combination
 * images in it
 *
 * \param vm A pointer on the ViewMastermind structure
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre vm != NULL, mm != NULL
 * \post The buttons' image are updated
 */
void update_last_combination_images(ViewMastermind *vm, ModelMastermind *mm);


/**
 * \fn void udpate_last_feedback_images(ViewMastermind *vm, ModelMastermind *mm)
 * \brief Updates the buttons of the last feedback to display the last given
 * feedback
 *
 * \param vm A pointer on the ViewMastermind structure
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre vm != NULL, mm != NULL
 * \post The feedback buttons' image are updated
 */
void udpate_last_feedback_images(ViewMastermind *vm, ModelMastermind *mm);


/**
 * \fn GdkPixbuf *get_color_image_pixbuf(ViewMastermind *vm, PAWN_COLOR color)
 * \brief gets the pixbuf for a given color
 *
 * \param vm A pointer on the ViewMastermind structure
 * \param color The color's pixbuf looked for
 *
 * \pre vm != NULL
 * \post The function returns the pixbuf from vm corresponding to the given
 * color
 *
 * \return A pointer on the right pixbuf
 */
GdkPixbuf *get_color_image_pixbuf(ViewMastermind *vm, PAWN_COLOR color);


/**
 * \fn GdkPixbuf *get_feedback_image_pixbuf(ViewMastermind *vm,
 * FEEDBACK_COLOR color)
 * \brief gets the pixbuf for the feedback buttons images
 *
 * \param vm A pointer on the ViewMastermind structure
 * \param color The color's pixbuf looked for
 *
 * \pre vm != NULL
 * \post The function returns the pixbuf from vm corresponding to the given
 * color
 *
 * \return A pointer on the right pixbuf
 */
GdkPixbuf *get_feedback_image_pixbuf(ViewMastermind *vm, FEEDBACK_COLOR color);


/**
 * \fn GtkWidget *get_main_menu_window(ViewMainMenu *vmm)
 * \brief gets the main menu window widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu window
 */
GtkWidget *get_main_menu_window(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_main_vbox(ViewMainMenu *vmm)
 * \brief gets the main menu main vbox widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu's main vbox
 */
GtkWidget *get_main_menu_main_vbox(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_pseudo_hbox(ViewMainMenu *vmm)
 * \brief gets the main menu pseudo hbox widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu pseudo hbox
 */
GtkWidget *get_main_menu_pseudo_hbox(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm)
 * \brief gets the main menu pawn hbox
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu pawn hbox
 */
GtkWidget *get_main_menu_nb_pawns_hbox(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_logo(ViewMainMenu *vmm)
 * \brief gets the main menu logo
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu's logo
 */
GtkWidget *get_main_menu_logo(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm)
 * \brief gets the main menu pseudo label widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu's pseudo label
 */
GtkWidget *get_main_menu_pseudo_label(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm)
 * \brief gets the main menu's number of pawns label widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu's number of pawns label
 */
GtkWidget *get_main_menu_nb_pawns_label(ViewMainMenu *vmm);


/**
 * \fn GtkWidget *get_main_menu_error_label(ViewMainMenu *vmm)
 * \brief gets the main menu error label widget
 *
 * \param vmm A pointer on the view of the main menu's structure
 *
 * \pre vmm != NULL
 * \post The function returns the pointer in the field of vmm
 *
 * \return A pointer on the widget of the main menu's error label
 */
GtkWidget *get_main_menu_error_label(ViewMainMenu *vmm);


/**
 * \fn unsigned int get_mastermind_proposition_button_size(ViewMastermind *vm)
 * \brief gets the size of the proposition button
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the size stored in the field of vm
 *
 * \return The value of the size of the proposition button
 */
unsigned int get_mastermind_proposition_button_size(ViewMastermind *vm);


/**
 * \fn unsigned int get_mastermind_color_button_size(ViewMastermind *vm)
 * \brief gets the size of the color button
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the size stored in the field of vm
 *
 * \return The value of the size of the color button
 */
unsigned int get_mastermind_color_button_size(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_end_game_window(ViewMastermind *vm)
 * \brief gets the widget of the end of the game window
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the end game window
 */
GtkWidget *get_mastermind_end_game_window(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_win_image(ViewMastermind *vm)
 * \brief gets the widget of the win image
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the win image
 */
GdkPixbuf *get_mastermind_win_image(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_loose_image(ViewMastermind *vm)
 * \brief gets the widget of the loose image
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the loose image
 */
GdkPixbuf *get_mastermind_loose_image(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_abouts_window(ViewMastermind *vm)
 * \brief gets the widget of the about window
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the about window
 */
GtkWidget *get_mastermind_abouts_window(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_abouts_main_vbox(ViewMastermind *vm)
 * \brief gets the widget of the abouts' main vbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the main vbox of abouts
 */
GtkWidget *get_abouts_main_vbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_abouts_label(ViewMastermind *vm)
 * \brief gets the widget of the abouts label
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the abouts label
 */
GtkWidget *get_mastermind_abouts_label(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_score_window(ViewMastermind *vm)
 * \brief gets the widget of the score window
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the score window
 */
GtkWidget *get_mastermind_score_window(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_scores_title_label(ViewMastermind *vm)
 * \brief gets the widget of the scores title label
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the scores title label
 */
GtkWidget *get_mastermind_scores_title_label(ViewMastermind *vm);


/**
 * \fn GtkWidget **get_mastermind_players_scores_label(ViewMastermind *vm)
 * \brief gets an array of widgets of the labels with the top 10 player scores
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return An array of pointer on the widget of player's score
 */
GtkWidget **get_mastermind_players_scores_label(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_score_main_vbox(ViewMastermind *vm)
 * \brief gets the widget of the score main vbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the score main vbox
 */
GtkWidget *get_score_main_vbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_window(ViewMastermind *vm)
 * \brief gets the widget of the mastermind window
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the mastermind window
 */
GtkWidget *get_mastermind_window(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_main_vbox(ViewMastermind *vm)
 * \brief gets the widget of the mastermind main vbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the mastermind main vbox
 */
GtkWidget *get_mastermind_main_vbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_history_table(ViewMastermind *vm)
 * \brief gets the widget of the mastermind history table
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the mastermind history table
 */
GtkWidget *get_mastermind_history_table(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_feedback_zone_hbox(ViewMastermind *vm)
 * \brief gets the widget of the feedback zone hbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the feedback zone hbox
 */
GtkWidget *get_mastermind_feedback_zone_hbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_proposition_hbox(ViewMastermind *vm)
 * \brief gets the widget of the proposition hbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the proposition hbox
 */
GtkWidget *get_mastermind_proposition_hbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_proposition_control_hbox(ViewMastermind *vm)
 * \brief gets the widget of the proposition control hbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the proposition control hbox
 */
GtkWidget *get_mastermind_proposition_control_hbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_color_selection_hbox(ViewMastermind *vm)
 * \brief gets the widget of the color selection hbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the color selection hbox
 */
GtkWidget *get_mastermind_color_selection_hbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_score_hbox(ViewMastermind *vm)
 * \brief gets the widget of the score hbox
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the score hbox
 */
GtkWidget *get_mastermind_score_hbox(ViewMastermind *vm);


/**
 * \fn GtkWidget *get_mastermind_score_label(ViewMastermind *vm)
 * \brief gets the widget of the score label displayed at the bottom of the
 * window during the game
 *
 * \param vm A pointer on the view of the mastermind structure
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the score label
 */
GtkWidget *get_mastermind_score_label(ViewMastermind *vm);

/**
 * \fn void set_score_label_text(GtkWidget *label, char *string)
 * \brief change the score label
 *
 * \param label pointer on label that need to be changed
 * \param string new string in the label
 *
 * \pre label != NULL, string != NULL
 * \post label sting is changed
 */
void set_score_label_text(GtkWidget *label, char *string);


/**
 * \fn GtkWidget *get_mastermind_history_combination_button(ViewMastermind
 * *vm, unsigned int i, unsigned int j)
 * \brief gets the widget of the history combination button of given coordinates
 *
 * \param vm A pointer on the view of the mastermind structure
 * \param i abscissa
 * \param j ordinate
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the history combination button of given
 * coordinates
 */
GtkWidget *
get_mastermind_history_combination_button(ViewMastermind *vm, unsigned int i,
                                          unsigned int j);


/**
 * \fn GtkWidget *get_mastermind_history_feedback_button(ViewMastermind
 * *vm, unsigned int i, unsigned int j)
 * \brief gets the widget of the feedback combination button of given
 * coordinates
 *
 * \param vm A pointer on the view of the mastermind structure
 * \param i abscissa
 * \param j ordinate
 *
 * \pre vm != NULL
 * \post The function returns the pointer stored in the field of vm
 *
 * \return A pointer on the widget of the feedback combination button of given
 * coordinates
 */
GtkWidget *
get_mastermind_history_feedback_button(ViewMastermind *vm, unsigned int i,
                                       unsigned int j);

#endif //__VIEW_MASTERMIND__
