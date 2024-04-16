#include <stdbool.h>

#include "modal.mastermind.h"

struct combination_t{
    unsigned int correct; /*!< Number of correctly placed pawns with correct color */
    unsigned int misplaced; /*!< Number of wrongly placed pawns with correct color */
    COLOR *pawns; /*!< Combination of pawns */
};

struct game_t{
    unsigned int nbPawns; /*!< Number of pawns in a combination */
    bool inGame; /*!< State of the game */
    COLOR *solution; /*!< Proposer combination */
    Combination **history; /*!< History of combinations proposed by the guesser */
};
