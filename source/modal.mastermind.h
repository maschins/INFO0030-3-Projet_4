#ifndef __MODAL_MASTERMIND__
#define __MODAL_MASTERMIND__

/**
 * \brief Defines the different colors of a pawn.
*/
typedef enum{
    RED,    /*!< Red color */
    BLUE,   /*!< Blue color */
    GREEN,  /*!< Green color */
    YELLOW  /*!< Yellow color */
}COLOR;

/**
 * Declare the Combination opaque type.
*/
typedef struct combination_t Combination;

/**
 * Declare the Game opaque type. 
*/
typedef struct game_t Game;

#endif //__MODAL_MASTERMIND__
