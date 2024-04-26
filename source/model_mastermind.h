#ifndef __MODEL_MASTERMIND__
#define __MODEL_MASTERMIND__

#define PSEUDO_LENGTH 50

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
   PAWN_DEFAULT,                  /*!< Default pawn */
   NB_PAWN_COLORS /*!< Number of colors */
}PAWN_COLOR;


typedef enum{
   FB_BLACK,    /*!< Black feedback pawn color */
   FB_WHITE,    /*!< White feedback pawn color  */
   FB_DEFAULT,  /*!< No feedback pawn */
   NB_FB_COLORS /*!< Number of feedback colors */ 
}FEEDBACK_COLOR;


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
typedef struct model_t ModelMastermind;


ModelMastermind *create_model_mastermind(unsigned int nbPawns, unsigned int nbAttempts);
void destroy_model_mastermind(ModelMastermind *mm);

Settings *create_settings(unsigned int nbPawns, unsigned int nbAttempts);
void destroy_settings(Settings *settings);

Game *create_game(unsigned int nbPawns, unsigned int nbCombinations);
void destroy_game(Game *game);

History *create_history(unsigned int nbPawns, unsigned int nbCombinations);
void destroy_history(History *history);

Combination *create_combination(unsigned int nbPawns);
void destroy_combination(Combination *combination);

char *get_pseudo(ModelMastermind *mm);
void set_pseudo(ModelMastermind *mm, char *pseudo);

#endif //__MODEL_MASTERMIND__
