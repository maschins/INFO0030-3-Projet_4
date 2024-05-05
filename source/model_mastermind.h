/**
 * \file model_mastermind.h
 * \brief Model header of mastermind game
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
 * \brief Path of the file where the scores are saved
 */
#define SAVED_SCORES_PATH "./source/scores.txt"

/**
 * \brief Max pseudo length.
 * */
#define MAX_PSEUDO_LENGTH 51

/**
 * \brief Min pseudo length.
 * */
#define MIN_PSEUDO_LENGTH 6

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

/**
 * \struct Score
 * \brief Type representing the player score
 *
 * Declaration the Score opaque type.
 * */
typedef struct score_t Score;

/**
 * \struct SavedScores
 * \brief Type representing the scores of the precedent players
 *
 * Declaration the SavedScore opaque type.
 * */
typedef struct saved_scores_t SavedScores;

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

/**
 * \fn SavedScores *get_saved_scores(ModelMastermind *mm)
 * \brief gets the saved scores in the ModelMastermind
 *
 * \param mm a pointer on the ModelMMastermind structure
 *
 * \pre mm != NULL
 * \post Scores are returned
 *
 * \return score field for mm
 */
SavedScores *get_saved_scores(ModelMastermind *mm);

void set_proposition_in_history(ModelMastermind *mm);

char *get_main_menu_pseudo(ModelMainMenu *mmm);
void set_role(ModelMainMenu *mmm, ROLE role);
void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns);
void set_pseudo(ModelMainMenu *mmm, char *pseudo);
void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor);
void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i);

/**
 * \fn SavedScores *load_scores(const char *filePath)
 * \brief Allocates the space for it and saves the scores from the given file
 * if the given file doesn't exist allocates the memory and returns the
 * empty structure
 *
 * \param filePath the file from which de score needs to be read
 *
 * \pre filePath != NULL
 * \post the memory is allocated and the values are read
 *
 * \return A pointer on the created SavedScores structure
 *         NULL if an error was encountered
 */
SavedScores *load_scores(const char *filePath);

/**
 * \fn int write_scores(SavedScores *scores, const char *filePath)
 * \brief writes in the given file the scores and destroy the score
 *
 * \param scores A pointer on the score structure that needs to be saved in
 * the file
 * \param filePath A string containing the path of the file in which the
 * score should be wrote
 *
 * \pre scores != NULL, filePath != NULL
 * \post The score are written in the file and the structure is freed
 *
 * \return 0 if success
 *         -1 Error manipulating the file
 */
int write_scores(SavedScores *scores, const char *filePath);

/**
 * \fn void destroy_saved_scores(SavedScores *scores)
 * \brief destroy given SavedScores structure
 *
 * \param scores pointer on structure ot destroy
 *
 * \pre scores != NULL
 * \post scores is destroyed and memory has been freed
 */
void destroy_saved_scores(SavedScores *scores);

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
