/**
 * \file model_mastermind.h
 * \brief Model header of mastermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 06/05/2024
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
 * \brief Default player pseudo.
 * */
#define DEFAULT_PSEUDO "Guest"

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
 * \brief Maximum scores displayed in the scores window
 */
#define MAX_SCORE_DISPLAYED 10

/**
 * \brief Defines the different pawn colors.
*/
typedef enum {
    PAWN_BLUE,     /*!< Blue color pawn */
    PAWN_CYAN,     /*!< Cyan color pawn */
    PAWN_GREEN,    /*!< Green color pawn */
    PAWN_ORANGE,   /*!< Orange color pawn */
    PAWN_PURPLE,   /*!< Purple color pawn */
    PAWN_RED,      /*!< Red color pawn */
    PAWN_YELLOW,   /*!< Yellow color pawn */
    PAWN_DEFAULT,  /*!< Default pawn */
    NB_PAWN_COLORS /*!< Number of colors */
} PAWN_COLOR;

/**
 * \brief Defines the different feedback colors.
*/
typedef enum {
    FB_BLACK,      /*!< Black feedback pawn color */
    FB_WHITE,      /*!< White feedback pawn color  */
    FB_DEFAULT,    /*!< No feedback pawn */
    NB_FB_COLORS   /*!< Number of feedback colors */
} FEEDBACK_COLOR;

/**
 * \brief Defines the different player roles.
*/
typedef enum {
    GUESSER, /*!< Guesser role */
    PROPOSER /*!< Proposer role */
} ROLE;

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


/**
 * \fn ModelMainMenu *create_model_main_menu(void)
 * \brief Creates ModelMainMenu structure with default values.
 *
 * \post memory is allocated and the structure is initialized.
 *
 * \return A pointer to ModelMainMenu structure,
 *         NULL if memory allocation failed.
 */
ModelMainMenu *create_model_main_menu(void);


/**
 * \fn void destroy_model_main_menu(ModelMainMenu *mmm)
 * \brief Free memory allocated for ModelMainMenu structure.
 *
 * \param mmm A valid pointer to ModelMainMenu structure.
 *
 * \pre mmm != NULL
 * \post Memory allocated for ModelMainMenu structure is freed.
 */
void destroy_model_main_menu(ModelMainMenu *mmm);


/**
 * \fn ModelMastermind *create_model_mastermind(ModelMainMenu *mmm);
 * \brief Creates ModelMastermind structure with menu values and default values.
 *
 * \param mmm Pointer to the ModelMainMenu structure containing the main menu settings.
 *
 * \pre mmm != NULL
 * \post Memory is allocated and sctructure is initialized.
 *
 * \return A pointer to ModelMastermind structure, 
 *         NULL if memory allocation fails.
 */
ModelMastermind *create_model_mastermind(ModelMainMenu *mmm);


/**
 * \fn void destroy_model_mastermind(ModelMastermind *mm)
 * \brief Free memory allocated for ModelMastermind structure.
 *
 * \param mm A valid pointer to ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post Memory allocated for ModelMastermind structure is freed.
 * 
 */
void destroy_model_mastermind(ModelMastermind *mm);


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
 * \fn void generate_random_solution(ModelMastermind *mm)
 * \brief Generates a random solution for the model.
 *
 * \param mm a valid pointer to ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post Model solution is randomly generated.
 */
void generate_random_solution(ModelMastermind *mm);


/**
 * \fn bool verify_proposition(ModelMastermind *mm);
 * \brief Verify if the current proposition is valid.
 *
 * \param mm a valid pointer to ModelMastermind.
 *
 * \pre mm != NULL
 * \post model proposition is verified.
 * 
 * \return true if proposition is valid
 *         false if its not.
 */
bool verify_proposition(ModelMastermind *mm);


/**
 * \fn void reset_proposition(ModelMastermind *mm)
 * \brief Reset the current proposition.
 *
 * \param mm a valid pointer to ModelMastermind.
 *
 * \pre mm != NULL
 * \post model proposition is reset.
 */
void reset_proposition(ModelMastermind *mm);


/**
 * \fn reset_feedback(ModelMastermind *mm)
 * \brief Reset the current feedback.
 *
 * \param mm a valid pointer to ModelMastermind.
 *
 * \pre mm != NULL
 * \post model feedback is reset.
 */
void reset_feedback(ModelMastermind *mm);


/**
 * \fn void  determine_feedback_proposition(ModelMastermind *mm, Combination *proposition, PAWN_COLOR *solution)
 * \brief determines the feedback of a proposition in relation to a solution.
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 * \param proposition a valid proposition
 * \param solution a valid solution.
 *
 * \pre mm != NULL, proposition != NULL, solution != NULL.
 * \post The proposition feedback is set.
 */
void
determine_feedback_proposition(ModelMastermind *mm, Combination *proposition,
                               const PAWN_COLOR *solution);


/**
 * \fn void update_current_combination_index(ModelMastermind *mm);
 * \brief updates the current history index.
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The current history index is decreased.
 */
void update_current_combination_index(ModelMastermind *mm);


/**
 * \fn void update_last_combination_feedback(ModelMastermind *mm)
 * \brief Updates the feedback of the last combination in the hisotry.
 *
 * \param mm A pointer to ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The feedback of the last combination is updated.
 */
void update_last_combination_feedback(ModelMastermind *mm);


/**
 * \fn void find_next_proposition(ModelMastermind *mm)
 * \brief Finds the next proposition the computer will propose.
 *
 * \param mm A pointer to the ModelMastermind.
 *
 * \pre mm != NULL
 * \post The next proposition is found and set in the model.
 */
void find_next_proposition(ModelMastermind *mm);


/**
 * \fn void verify_end_game(ModelMastermind *mm)
 * \brief Verify the game state and updates it.
 *
 * \param mm A valid pointer to the ModelMastermind.
 *
 * \pre mm != NULL
 * \post The game state is updated.
 */
void verify_end_game(ModelMastermind *mm);


/**
 * \fn PAWN_COLOR get_selected_color(ModelMastermind *mm)
 * \brief gets the currently selected pawn color
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The currently selected pawn color is returned.
 *
 * \return The currently selected pawn color.
 */
PAWN_COLOR get_selected_color(ModelMastermind *mm);


/**
 * \fn ROLE get_role(ModelMastermind *mm)
 * \brief Gets the current player's role (guesser or proposer).
 *
 * \param mm A valid pointer to the ModelMastermind.
 *
 * \pre mm != NULL
 * \post the player's role is returned.
 *
 * \return The player's role.
 */
ROLE get_role(ModelMastermind *mm);


/**
 * \fn bool get_in_game(ModelMastermind *mm)
 * \brief Gets the game state.
 *
 * \param mm A pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The game state is returned.
 *
 * \return true if the game continue
 *         false if not.
 */
bool get_in_game(ModelMastermind *mm);


/**
 * \fn bool get_valid_solution(ModelMastermind *mm)
 * \brief get the validity of the solution.
 *
 * \param mm A pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The solution validity is returned.
 *
 * \return true if solution is valid,
 *         false if the solution is not valid
 */
bool get_valid_solution(ModelMastermind *mm);


/**
 * \fn Combination *get_proposition(ModelMastermind *mm)
 * \brief gets the current proposition in the game.
 *
 * \param mm A valid pointer to the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post The current proposition is returned.
 *
 * \return A pointer to the current propsition.
 */
Combination *get_proposition(ModelMastermind *mm);


/**
 * \fn PAWN_COLOR *get_solution(ModelMastermind *mm)
 * \brief Gets the actual game solution
 *
 * \param mm A pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The game solution is returned.
 *
 * \return The solution from the ModelMastermind.
 */
PAWN_COLOR *get_solution(ModelMastermind *mm);


/**
 * \fn unsigned int get_nb_pawns(ModelMastermind *mm)
 * \brief Gets the number of pawns of a combination
 *
 * \param mm A pointer to the ModelMastermid.
 *
 * \pre mmm != NULL
 * \post The number of pawns of a combination is returned.
 *
 * \return the number of pawns of combination.
 */
unsigned int get_nb_pawns(ModelMastermind *mm);


/**
 * \fn unsigned int get_nb_combinations(ModelMastermind *mm)
 * \brief gets the number of combinations of the game
 *
 * \param mm A pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The number of combinations of the game is returned
 *
 * \return The number of combinations.
 */
unsigned int get_nb_combinations(ModelMastermind *mm);


/**
 * \fn int get_current_index(ModelMastermind *mm)
 * \brief Gets the current index of the history.
 *
 * \param mm A valid pointer to the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post The current index of the history is returned.
 *
 * \return The current index of the history.
 */
int get_current_index(ModelMastermind *mm);


/**
 * \fn PAWN_COLOR get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex)
 * \brief Gets the pawn color at the specified index in the last combination.
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 * \param pawnIndex The index of the pawn in the last combination.
 *
 * \pre mm != NULL
 * \post The pawn color at the specified index in the last combination is returned.
 *
 * \return The pawn color at the specified index in the last combination.
 */
PAWN_COLOR
get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex);


/**
 * \fn unsigned int get_nb_correct_last_combination(ModelMastermind *mm)
 * \brief Gets the number of correct pawns in the last combinatin.
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The number of corect pawns in the last combination is returned.
 *
 * \return The number of correct pawns in the last combination.
 */
unsigned int get_nb_correct_last_combination(ModelMastermind *mm);


/**
 * \fn unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm)
 * \brief Gets the number of misplaced pawns in the last combination
 *
 * \param mm A valid pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post The number of misplaced pawns in the last combination is returned.
 *
 * \return The number of misplaced pawns in the last combination.
 */
unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm);


/**
 * \fn FEEDBACK_COLOR get_feedback_pawn(ModelMastermind *mm, unsigned int index)
 * \brief Gets the feedback pawn color at the specified index.
 *
 * \param mm a valid pointer to the Modelmastermind structure.
 * \param index The index of the feedback pawn color.
 *
 * \pre mm != NULL
 * \post The feedback pawn color at the specified index is returned.
 *
 * \return The feedback pawn color at the specified index.
 */
FEEDBACK_COLOR get_feedback_pawn(ModelMastermind *mm, unsigned int index);


/**
 * \fn SavedScores *get_saved_scores(ModelMastermind *mm)
 * \brief Gets the saved scores in the ModelMastermind.
 *
 * \param mm A pointer to the ModelMastermind structure.
 *
 * \pre mm != NULL
 * \post Scores are returned
 *
 * \return The saved scores in the ModelMastermind.
 */
SavedScores *get_saved_scores(ModelMastermind *mm);

/**
 * \fn unsigned get_saved_scores_length(ModelMastermind *mm)
 * \brief Gets the saved score length in the ModelMastermind
 *
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post The length of the saved score in The mastermind is returned
 *
 * \return The length field in the save field of ModelMastermind
 */
unsigned get_saved_scores_length(ModelMastermind *mm);

/**
 * \fn char **get_scores_strings(SavedScores *scores)
 * \brief Returns the strings that needs to be in the labels of the scores
 *
 * \param scores A pointer on the SavedScores structure
 *
 * \pre scores != NULL
 * \post the array of string is returned
 *
 * \return An array of strings with the ranking pseudo and score
 */
char **get_scores_strings(SavedScores *scores);

/**
 * \fn void free_scores_strings(char **strings, unsigned length)
 * \brief destroy the 2D array of strings
 *
 * \param strings the array that needs to be freed
 * \param length the length of the array
 *
 * \pre strings != NULL
 * \post strings is freed
 */
void free_scores_strings(char **strings, unsigned length);


/**
 * \fn void set_proposition_in_history(ModelMastermind *mm)
 * \brief sets the current proposition in the combinations history.
 *
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post the proposition is set in the combinations history.
 */
void set_proposition_in_history(ModelMastermind *mm);


/**
 * \fn void set_role(ModelMainMenu *mmm, ROLE role)
 * \brief sets the player role in the main menu model structure.
 *
 * \param mmm A pointer on the ModelMainMenu structure
 * \param role The player role
 *
 * \pre mm != NULL
 * \post the player role is set.
 */
void set_role(ModelMainMenu *mmm, ROLE role);


/**
 * \fn void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns)
 * \brief sets the number of pawns for the game based on the number of pawn slider.
 *
 * \param mmm A pointer on the ModelMainMenu structure
 * \param nbPawns The number of pawns selected with the slider.
 *
 * \pre mm != NULL
 * \post the number of pawns is set.
 */
void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns);


/**
 * \fn void set_pseudo(ModelMainMenu *mmm, char *pseudo)
 * \brief sets the player pseudo in the main menu model.
 *
 * \param mmm A pointer on the ModelMainMenu structure
 * \param pseudo The player pseudo.
 *
 * \pre mm != NULL, pseudo != NULL
 * \post the pseudo is set.
 */
void set_pseudo(ModelMainMenu *mmm, char *pseudo);


/**
 * \fn void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor)
 * \brief Sets the selected color.
 *
 * \param mm A pointer on the ModelMastermind structure
 * \param newColor the new selected color.
 *
 * \pre mm != NULL
 * \post the selected color is set.
 */
void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor);


/**
 * \fn void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i)
 * \brief Sets the selected color to a proposition pawn.
 *
 * \param mm A pointer on the ModelMastermind structure
 * \param i the proposition pawn index.
 *
 * \pre mm != NULL, i < mm->history->nbPawns
 * \post the color is set to the pawn.
 */
void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i);


/**
 * \fn void set_feedback_pawn(ModelMastermind *mm, unsigned int index)
 * \brief Changes a pawn in the feedback.
 *
 * \param mm A pointer on the ModelMastermind structure
 * \param index the feedback pawn index.
 *
 * \pre mm != NULL, index < mm->history->nbPawns
 * \post the feedback pawn is changed.
 */
void set_feedback_pawn(ModelMastermind *mm, unsigned int index);


/**
 * \fn void set_feedback_pawn(ModelMastermind *mm, unsigned int index)
 * \brief Sets the proposition as the solution.
 *
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post the solution is the proposition.
 */
void set_proposition_as_solution(ModelMastermind *mm);


/**
 * \fn void set_valid_solution_true(ModelMastermind *mm)
 * \brief Sets the solution to valid state.
 *
 * \param mm A pointer on the ModelMastermind structure
 *
 * \pre mm != NULL
 * \post the solution validity is true
 */
void set_valid_solution_true(ModelMastermind *mm);

#endif //__MODEL_MASTERMIND__
