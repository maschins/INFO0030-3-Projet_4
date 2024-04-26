#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "model_mastermind.h"

struct combination_t {
   unsigned int nbCorrect;   /*!< Number of correctly placed pawns with correct color in the combination */
   unsigned int nbMisplaced; /*!< Number of wrongly placed pawns with correct color in the combination */
   PAWN_COLOR *pawns;        /*!< Combination of pawns */
};


struct history_t {
   unsigned int nbPawns;        /*!< Number of pawns of a combination */
   unsigned int nbCombinations; /*!< Number of combinations in the histroy */
   unsigned int currentIndex;   /*!< Index of the last combination in the history */
   Combination **combinations;  /*!< History of combinations proposed by the guesser */
};


struct game_t {
   bool inGame;              /*!< State of the game */
   PAWN_COLOR selectedColor; /*!< Selected color */
   PAWN_COLOR *proposition;  /*!< Guesser proposition */
   FEEDBACK_COLOR *solution; /*!< Proposer combination */
   History *history;
};


struct settings_t {
   char pseudo[PSEUDO_LENGTH]; /*!< Player pseudo */ 
   unsigned int nbPawns;       /*!< Number of pawns in a combination */
   unsigned int nbAttempts;    /*!< Number of combinations that can be proposed before the game ends */ 
};


struct model_t {
   Settings *settings; /*!< Settings of the game */
   Game *game;         /*!< State of the game */
};


Combination *create_combination(unsigned int nbPawns) {
   Combination *combination = malloc(sizeof(Combination));
   if(combination == NULL)
      return NULL;

   combination->nbCorrect = 0;
   combination->nbMisplaced = 0;

   combination->pawns = malloc(nbPawns * sizeof(PAWN_COLOR));
   if(combination->pawns == NULL){
      free(combination);
      return NULL;
   }

   for(unsigned int i = 0; i < nbPawns; i++)
      combination->pawns[i] = PAWN_DEFAULT;

   return combination;
}


void destroy_combination(Combination *combination) {
   if(combination != NULL){
      if(combination->pawns != NULL)
         free(combination->pawns);
      free(combination);
   }
}


History *create_history(unsigned int nbPawns, unsigned int nbCombinations) {
   History *history = malloc(sizeof(History));
   if(history == NULL)
      return NULL;

   history->nbPawns = nbPawns;
   history->nbCombinations = nbCombinations;
   history->currentIndex = 0;

   history->combinations = malloc(nbCombinations * sizeof(Combination *));
   if(history->combinations == NULL) {
      free(history);
      return NULL;
   }

   for(unsigned int i = 0; i < nbCombinations; i++) {
      history->combinations[i] = create_combination(nbPawns);
      if(history->combinations[i] == NULL) {
         destroy_history(history);
         return NULL;
      }
   }

   return history;
}


void destroy_history(History *history) {
   if(history != NULL){
      if(history->combinations != NULL){
         for(unsigned int i = 0; i < history->nbCombinations; i++){
            if(history->combinations[i] != NULL)
               destroy_combination(history->combinations[i]);
         }
         free(history->combinations);
      }
      free(history);
   }
}


Game *create_game(unsigned int nbPawns, unsigned int nbCombinations) {
   Game *game = malloc(sizeof(Game));
   if(game == NULL)
      return NULL;

   game->inGame = true;
   game->selectedColor = PAWN_BLUE;

   game->proposition = malloc(nbPawns * sizeof(PAWN_COLOR));
   if(game->proposition == NULL){
      free(game);
      return NULL;
   }

   game->solution = malloc(nbPawns * sizeof(FEEDBACK_COLOR));
   if(game->solution == NULL){
      free(game->proposition);
      free(game);
      return NULL;
   }

   for(unsigned int i = 0; i < nbPawns; i++){
      game->proposition[i] = PAWN_DEFAULT;
      game->solution[i] = PAWN_DEFAULT;
   }

   game->history = create_history(nbPawns, nbCombinations);
   if(game->history == NULL){
      destroy_game(game);
      return NULL;
   }

   return game;
}


void destroy_game(Game *game) {
   if(game != NULL) {
      if(game->proposition != NULL)
         free(game->proposition);
      if(game->solution != NULL)
         free(game->solution);
      destroy_history(game->history);
      free(game);
   }
}


Settings *create_settings(unsigned int nbPawns, unsigned int nbAttempts) {
   Settings *settings = malloc(sizeof(Settings));
   if(settings == NULL)
      return NULL;

   settings->nbPawns = nbPawns;
   settings->nbAttempts = nbAttempts;
   settings->pseudo[0] = '\0';

   return settings;
}


void destroy_settings(Settings *settings) {
   free(settings);
}


ModelMastermind *create_model_mastermind(unsigned int nbPawns, unsigned int nbAttempts) {
   ModelMastermind *mm = malloc(sizeof(ModelMastermind));
   if(mm == NULL)
      return NULL;

   mm->settings = create_settings(nbPawns, nbAttempts);
   if(mm->settings == NULL){
      free(mm);
      return NULL;
   }

   mm->game = create_game(nbPawns, nbAttempts);
   if(mm->game == NULL){
      destroy_settings(mm->settings);
      free(mm);
      return NULL;
   }

   return mm;
}


void destroy_model_mastermind(ModelMastermind *mm) {
   if(mm != NULL){
      destroy_settings(mm->settings);
      destroy_game(mm->game);
      free(mm);
   }
}


char *get_pseudo(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->settings->pseudo;
}


void set_pseudo(ModelMastermind *mm, char *pseudo) {
   assert(mm != NULL && strlen(pseudo) <= PSEUDO_LENGTH);

   strcpy(mm->settings->pseudo, pseudo);
}