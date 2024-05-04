/**
 * \file model_mastermind.h
 * \brief Mdoel header of matsermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 04/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern model header for the mastermind game.
 * 
 * */

#include <stdbool.h>

#ifndef __MODEL_MASTERMIND__
#define __MODEL_MASTERMIND__

/**
 * \brief Max pseudo length.
 * */
#define MAX_PSEUDO_LENGTH 50

/**
 * \brief Min pseudo length.
 * */
#define MIN_PSEUDO_LENGTH 5

/**
 * \brief Minimum number of pawns.
 * */
#define MIN_NB_PAWNS 4

/**
 * \brief Maximum number of pawns.
 * */
#define MAX_NB_PAWNS 8

/**
 * \brief Default number of pawns.
 * */
#define DEFAULT_NB_PAWNS 4

/**
 * \brief Number of combination.
 * */
#define NB_COMBINATIONS 10

/**
 * \brief Defines the different pawn colors.
*/
typedef enum{
   PAWN_BLUE,     /*!< Blue color pawn */
   PAWN_CYAN,     /*!< Cyan color pawn */
   PAWN_GREEN,    /*!< Green color pawn */
   PAWN_ORANGE,   /*!< Orange color pawn */
   PAWN_PURPLE,   /*!< Purple color pawn */
   PAWN_RED,      /*!< Red color pawn */
   PAWN_YELLOW,   /*!< Yellow color pawn */
   PAWN_DEFAULT,  /*!< Default pawn */
   NB_PAWN_COLORS /*!< Number of colors */
}PAWN_COLOR;

/**
 * \brief Defines the different feedback colors.
*/
typedef enum{
   FB_BLACK,      /*!< Black feedback pawn color */
   FB_WHITE,      /*!< White feedback pawn color  */
   FB_DEFAULT,    /*!< No feedback pawn */
   NB_FB_COLORS   /*!< Number of feedback colors */ 
}FEEDBACK_COLOR;

/**
 * \brief Defines the different player roles.
*/
typedef enum{
   GUESSER, /*!< Guesser role */ 
   PROPOSER /*!< Proposer role */ 
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

ModelMainMenu *create_model_main_menu(void);
void destroy_model_main_menu(ModelMainMenu *mmm);

ModelMastermind *create_model_mastermind(ModelMainMenu *mmm);
void destroy_model_mastermind(ModelMastermind *mm);

void generate_random_solution(ModelMastermind *mm);
bool verify_proposition(ModelMastermind *mm);
void reset_proposition(ModelMastermind *mm);

void determine_feedback_last_combination(ModelMastermind *mm);
void update_current_combination_index(ModelMastermind *mm);
void verify_end_game(ModelMastermind *mm);

PAWN_COLOR get_selected_color(ModelMastermind *mm);
char *get_pseudo(ModelMastermind *mm);
unsigned int get_nb_pawns(ModelMastermind *mm);
unsigned int get_nb_combinations(ModelMastermind *mm);
bool get_in_game(ModelMastermind *mm);
int get_current_index(ModelMastermind *mm);
unsigned int get_nb_correct_last_combination(ModelMastermind *mm);
unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm);
PAWN_COLOR get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex);
PAWN_COLOR **get_configs(ModelMastermind *mm);

void set_proposition_in_history(ModelMastermind *mm);
void set_role(ModelMainMenu *mmm, ROLE role);
void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns);
void set_pseudo(ModelMainMenu *mmm, char *pseudo);
void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor);
void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i);

/**
 * \fn void set_propositions(ModelMastermind *mm, const PAWN_COLOR *proposition)
 * \brief set the current proposition to a given one
 *
 * \param mm pointer to the Model Structure
 * \param proposition new proposition to set
 *
 * \pre mm != NULL, proposition != NULL
 * \post the new proposition is correctly set
 */
void set_propositions(ModelMastermind *mm, const PAWN_COLOR *proposition);
#endif //__MODEL_MASTERMIND__
