#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "model_mastermind.h"

struct model_main_menu_t{
   char pseudo[MAX_PSEUDO_LENGTH];
   bool validPseudo;
   ROLE role;
   unsigned int nbPawns;
};


ModelMainMenu *create_model_main_menu() {
   ModelMainMenu *mmm = malloc(sizeof(ModelMainMenu));

   mmm->validPseudo = false;
   mmm->role = GUESSER;
   mmm->nbPawns = DEFAULT_NB_PAWNS;

   return mmm;
}


void destroy_model_main_menu(ModelMainMenu *mmm) {
   if(mmm != NULL)
      free(mmm);
}


void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns) {
   assert(mmm != NULL);
   mmm->nbPawns = nbPawns;
}


void set_role(ModelMainMenu *mmm, ROLE role) {
   assert(mmm != NULL);
   mmm->role = role;
}


void set_pseudo(ModelMainMenu *mmm, char *pseudo) {
   assert(mmm != NULL && strlen(pseudo) <= MAX_PSEUDO_LENGTH);
   strcpy(mmm->pseudo, pseudo);
}