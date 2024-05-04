#include <stdbool.h>

#ifndef __MODEL_MASTERMIND__
#define __MODEL_MASTERMIND__

#define MAX_PSEUDO_LENGTH 50
#define MIN_PSEUDO_LENGTH 5

#define MIN_NB_PAWNS 4
#define MAX_NB_PAWNS 8
#define DEFAULT_NB_PAWNS 4

#define NB_COMBINATIONS 10

/**
 * \brief Defines the different pawn types.
*/
typedef enum{
   /** Start of the editable part.
    *  Keep the colors in the same order as the main paths.
    */
   PAWN_BLUE,     /*!< Blue color pawn */
   PAWN_CYAN,     /*!< Cyan color pawn */
   PAWN_GREEN,    /*!< Green color pawn */
   PAWN_ORANGE,   /*!< Orange color pawn */
   PAWN_PURPLE,   /*!< Purple color pawn */
   PAWN_RED,      /*!< Red color pawn */
   PAWN_YELLOW,   /*!< Yellow color pawn */

   // End of the editable part. Don't edit from here.
   PAWN_DEFAULT,  /*!< Default pawn */
   NB_PAWN_COLORS /*!< Number of colors */
}PAWN_COLOR;


typedef enum{
   FB_BLACK,      /*!< Black feedback pawn color */
   FB_WHITE,      /*!< White feedback pawn color  */
   FB_DEFAULT,    /*!< No feedback pawn */
   NB_FB_COLORS   /*!< Number of feedback colors */ 
}FEEDBACK_COLOR;


typedef enum{
   GUESSER,
   PROPOSER
}ROLE;


/**
 * Declare the Combination opaque type.
 * */
typedef struct combination_t Combination;

/**
 * Declare the History opaque type.
 * */
typedef struct history_t History;

/**
 * Declare the Game opaque type.
 * */
typedef struct game_t Game;

/**
 * Declare the Settings opaque type.
 * */
typedef struct settings_t Settings;

/**
 * Declare the ModelMastermind opaque type. 
 * */
typedef struct model_mastermind_t ModelMastermind;

/**
 * Declare the ModelMainMenu opaque type.
 * */
typedef struct model_main_menu_t ModelMainMenu;

ModelMainMenu *create_model_main_menu();
void destroy_model_main_menu(ModelMainMenu *mmm);

void set_role(ModelMainMenu *mmm, ROLE role);

ModelMastermind *create_model_mastermind(ModelMainMenu *mmm);
void destroy_model_mastermind(ModelMastermind *mm);

History *create_history(unsigned int nbPawns, unsigned int nbCombinations);
void destroy_history(History *history);

Combination *create_combination(unsigned int nbPawns);
void destroy_combination(Combination *combination);

void generate_random_solution(ModelMastermind *mm);
void reset_proposition(ModelMastermind *mm);
void set_proposition_in_history(ModelMastermind *mm);
bool verify_proposition(ModelMastermind *mm);
void determine_feedback_last_combination(ModelMastermind *mm);
void update_current_combination_index(ModelMastermind *mm);

char *get_pseudo(ModelMastermind *mm);
void set_pseudo(ModelMainMenu *mmm, char *pseudo);

void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns);
unsigned int get_nb_pawns(ModelMastermind *mm);
unsigned int get_nb_combinations(ModelMastermind *mm);
unsigned int get_nb_correct_last_combination(ModelMastermind *mm);
unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm);
void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor);
PAWN_COLOR get_selected_color(ModelMastermind *mm);
void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i);
bool get_in_game(ModelMastermind *mm);
PAWN_COLOR get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex);
int get_current_index(ModelMastermind *mm);
void verify_end_game(ModelMastermind *mm);

#endif //__MODEL_MASTERMIND__
