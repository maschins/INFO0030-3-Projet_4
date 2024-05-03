#include <stdbool.h>

#ifndef __MODEL_MASTERMIND__
#define __MODEL_MASTERMIND__

#define MAX_PSEUDO_LENGTH 50
#define MIN_PSEUDO_LENGTH 5

#define MIN_NB_PAWNS 4
#define MAX_NB_PAWNS 8
#define DEFAULT_NB_PAWNS 4

#define NB_COMBINATIONS 10

typedef enum{
   GUESSER,
   PROPOSER
}ROLE;

/**
 * Declare the ModelMainMenu opaque type.
 * */
typedef struct model_main_menu_t ModelMainMenu;

ModelMainMenu *create_model_main_menu();
void destroy_model_main_menu(ModelMainMenu *mmm);

void set_role(ModelMainMenu *mmm, ROLE role);
void set_pseudo(ModelMainMenu *mmm, char *pseudo);
void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns);

#endif //__MODEL_MASTERMIND__
