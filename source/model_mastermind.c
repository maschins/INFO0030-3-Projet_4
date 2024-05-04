/**
 * \file model_mastermind.c
 * \brief Mdoel file of matsermind game
 * \authors Fraiponts Thomas, Schins Martin
 * \version 0.1
 * \date 04/05/2024
 * 
 * INFO0030 : Projet de programmation 4, Mastermind.
 * MVC pattern model for the mastermind game.
 * 
 * */

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "model_mastermind.h"

struct combination_t{
   unsigned int nbCorrect;   /*!< Number of correctly placed pawns with correct color in the combination */
   unsigned int nbMisplaced; /*!< Number of wrongly placed pawns with correct color in the combination */
   PAWN_COLOR *pawns;        /*!< Combination of pawns */
};


struct history_t{
   unsigned int nbPawns;         /*!< Number of pawns of a combination */
   unsigned int nbCombinations;  /*!< Number of combinations in the histroy */
   int currentIndex;             /*!< Index of the last combination in the history */
   Combination **combinations;   /*!< History of combinations proposed by the guesser */
};


struct model_mastermind_t{
   ROLE role;
   char savedPseudo[MAX_PSEUDO_LENGTH]; /*!< Player pseudo */ 
   bool inGame;                         /*!< State of the game */
   PAWN_COLOR selectedColor;            /*!< Selected color */
   PAWN_COLOR *proposition;             /*!< Guesser proposition */
   PAWN_COLOR *solution;                /*!< Proposer combination */
   History *history;                    /*!< Combinations settings and history */
};


struct model_main_menu_t{
   char pseudo[MAX_PSEUDO_LENGTH];  /*!< Saved player pseudo */
   bool validPseudo;                /*!< State of pseudo validity */
   ROLE role;                       /*!< Player role */
   unsigned int nbPawns;            /*!< Number of pawns selected */
};


/**
 * \fn static Combination *create_combination(unsigned int nbPawns)
 * \brief Allocates memory for Combination structure and returns a pointer to Combination.
 * 
 * \param nbPawns Number of pawns of a combination. 
 * 
 * @post The memory for a Combination structure is allocated.
 * 
 * \return combination a pointer to Combination,
 *         NULL in case of error.
 * 
 * */
static Combination *create_combination(unsigned int nbPawns);


/**
 * \fn static void destroy_combination(Combination *combination)
 * \brief Free the memory allocated to a Combination structure.
 * 
 * \param combination a valid pointer to Combination.
 * 
 * @pre combination != NULL.
 * @post The memory for the Combination structure is freed.
 * 
 * */
static void destroy_combination(Combination *combination);


/**
 * \fn static History *create_history(unsigned int nbPawns, unsigned int nbCombinations)
 * \brief Allocates memory for History structure and returns a pointer to History.
 * 
 * \param nbPawns Number of pawns of a combination.
 * \param nbCombinations Number of combinations that the player can propose during the game. 
 * 
 * @post The memory for a History structure is allocated.
 * 
 * \return history a pointer to History,
 *         NULL in case of error.
 * 
 * */
static History *create_history(unsigned int nbPawns, unsigned int nbCombinations);


/**
 * \fn static void destroy_history(History *history)
 * \brief Free the memory allocated to a History structure.
 * 
 * \param history a valid pointer to History.
 * 
 * @pre history != NULL.
 * @post The memory for the History structure is freed.
 * 
 * */
static void destroy_history(History *history);


static Combination *create_combination(unsigned int nbPawns) {
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


static void destroy_combination(Combination *combination) {
   if(combination != NULL){
      if(combination->pawns != NULL)
         free(combination->pawns);
      free(combination);
   }
}


static History *create_history(unsigned int nbPawns, unsigned int nbCombinations) {
   History *history = malloc(sizeof(History));
   if(history == NULL)
      return NULL;

   history->nbPawns = nbPawns;
   history->nbCombinations = nbCombinations;
   history->currentIndex = nbCombinations - 1;

   history->combinations = malloc(nbCombinations * sizeof(Combination *));
   if(history->combinations == NULL){
      free(history);
      return NULL;
   }

   for(unsigned int i = 0; i < nbCombinations; i++){
      history->combinations[i] = create_combination(nbPawns);
      if(history->combinations[i] == NULL){
         destroy_history(history);
         return NULL;
      }
   }

   return history;
}


static void destroy_history(History *history) {
   if(history != NULL){
      if(history->combinations != NULL){
         for(unsigned int i = 0; i < history->nbCombinations; i++)
            if(history->combinations[i] != NULL)
               destroy_combination(history->combinations[i]);
         
         free(history->combinations);
      }
      free(history);
   }
}


ModelMainMenu *create_model_main_menu(void) {
   ModelMainMenu *mmm = malloc(sizeof(ModelMainMenu));
   if(mmm == NULL)
      return NULL;

   mmm->validPseudo = false;
   mmm->role = GUESSER;
   mmm->nbPawns = DEFAULT_NB_PAWNS;

   return mmm;
}


void destroy_model_main_menu(ModelMainMenu *mmm) {
   if(mmm != NULL)
      free(mmm);
}


ModelMastermind *create_model_mastermind(ModelMainMenu *mmm) {
   ModelMastermind *mm = malloc(sizeof(ModelMastermind));
   if(mm == NULL)
      return NULL;

   // Copy main menu settings in game model.
   mm->role = mmm->role;
   strcpy(mm->savedPseudo, mmm->pseudo);
   mm->inGame = true;
   mm->selectedColor = PAWN_BLUE;

   mm->proposition = malloc(mmm->nbPawns * sizeof(PAWN_COLOR));
   if(mm->proposition == NULL){
      free(mm);
      return NULL;
   }

   mm->solution = malloc(mmm->nbPawns * sizeof(FEEDBACK_COLOR));
   if(mm->solution == NULL){
      free(mm->proposition);
      free(mm);
      return NULL;
   }

   for(unsigned int i = 0; i < mmm->nbPawns; i++){
      mm->proposition[i] = PAWN_DEFAULT;
      mm->solution[i] = PAWN_DEFAULT;
   }

   mm->history = create_history(mmm->nbPawns, NB_COMBINATIONS);
   if(mm->history == NULL){
      free(mm->solution);
      free(mm->proposition);
      free(mm);
      return NULL;
   }

   return mm;
}


void destroy_model_mastermind(ModelMastermind *mm) {
   if(mm != NULL){
      if(mm->solution != NULL)
         free(mm->solution);
      if(mm->proposition != NULL)
         free(mm->proposition);
      destroy_history(mm->history);
      free(mm);
   }
}


void generate_random_solution(ModelMastermind *mm) {
   assert(mm != NULL);

   srand(time(NULL));

   for(unsigned int i = 0; i < mm->history->nbPawns; i++){
      mm->solution[i] = rand() % (NB_PAWN_COLORS - 1);
   }
}


bool verify_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      if(mm->proposition[i] == PAWN_DEFAULT)
         return false;

   return true;
}


void reset_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->proposition[i] = PAWN_DEFAULT;
}


void determine_feedback_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   unsigned int nbCorrect = 0;
   unsigned int nbMisplaced = 0;

   unsigned int nbColorsInProposition[NB_PAWN_COLORS];
   unsigned int nbColorsInSolution[NB_PAWN_COLORS];

   for(unsigned int i = 0; i < NB_PAWN_COLORS; i++){
      nbColorsInProposition[i] = 0;
      nbColorsInSolution[i] = 0;
   }

   Combination *lastCombination = mm->history->combinations[mm->history->currentIndex];
   PAWN_COLOR *solution = mm->solution;

   for(unsigned int i = 0; i < mm->history->nbPawns; i++){
      if(lastCombination->pawns[i] == solution[i])
         nbCorrect++;
      else{
         nbColorsInProposition[lastCombination->pawns[i]]++;
         nbColorsInSolution[solution[i]]++;
      }
   }

   for(unsigned int i = 0; i < NB_PAWN_COLORS; i++){
      if(nbColorsInProposition[i] < nbColorsInSolution[i])
         nbMisplaced += nbColorsInProposition[i];
      else
         nbMisplaced += nbColorsInSolution[i];
   }

   lastCombination->nbCorrect = nbCorrect;
   lastCombination->nbMisplaced = nbMisplaced;
}


void update_current_combination_index(ModelMastermind *mm) {
   assert(mm != NULL);
   mm->history->currentIndex--;
}


void verify_end_game(ModelMastermind *mm) {
   assert(mm != NULL);

   if(mm->history->combinations[mm->history->currentIndex]->nbCorrect == mm->history->nbPawns || mm->history->currentIndex <= 0)
      mm->inGame = false;
}


PAWN_COLOR get_selected_color(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->selectedColor;
}


char *get_pseudo(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->savedPseudo;
}


unsigned int get_nb_pawns(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->history->nbPawns;
}


unsigned int get_nb_combinations(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->history->nbCombinations;
}


bool get_in_game(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->inGame;
}


int get_current_index(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->history->currentIndex;
}


unsigned int get_nb_correct_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->combinations[mm->history->currentIndex]->nbCorrect;
}


unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->combinations[mm->history->currentIndex]->nbMisplaced;
}


PAWN_COLOR get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex) {
   assert(mm != NULL && pawnIndex < mm->history->nbPawns);

   return mm->history->combinations[mm->history->currentIndex]->pawns[pawnIndex];
}


void set_proposition_in_history(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->history->combinations[mm->history->currentIndex]->pawns[i] = mm->proposition[i];
}


void set_role(ModelMainMenu *mmm, ROLE role) {
   assert(mmm != NULL);
   mmm->role = role;
}


void set_nb_pawns_slider(ModelMainMenu *mmm, unsigned int nbPawns) {
   assert(mmm != NULL);
   mmm->nbPawns = nbPawns;
}


void set_pseudo(ModelMainMenu *mmm, char *pseudo) {
   assert(mmm != NULL && strlen(pseudo) <= MAX_PSEUDO_LENGTH);
   strcpy(mmm->pseudo, pseudo);
}


void set_selected_color(ModelMastermind *mm, PAWN_COLOR newColor) {
   assert(mm != NULL);
   mm->selectedColor = newColor;
}


void set_proposition_pawn_selected_color(ModelMastermind *mm, unsigned int i) {
   assert(mm != NULL && i < mm->history->nbPawns);
   mm->proposition[i] = mm->selectedColor;
}
