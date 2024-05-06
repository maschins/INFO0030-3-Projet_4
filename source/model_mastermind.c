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
#include <math.h>
#include <unistd.h>

#include "model_mastermind.h"

struct combination_t {
   unsigned int nbCorrect;   /*!< Number of correctly placed pawns with correct color in the combination */
   unsigned int nbMisplaced; /*!< Number of wrongly placed pawns with correct color in the combination */
   PAWN_COLOR *pawns;        /*!< Combination of pawns */
};


struct history_t {
   unsigned int nbPawns;         /*!< Number of pawns of a combination */
   unsigned int nbCombinations;  /*!< Number of combinations in the histroy */
   int currentIndex;             /*!< Index of the last combination in the history */
   Combination **combinations;   /*!< History of combinations proposed by the guesser */
};


struct model_mastermind_t {
   ROLE role;                             /*!< Player role */
   char savedPseudo[MAX_PSEUDO_LENGTH];   /*!< Player pseudo */
   bool inGame;                           /*!< State of the game */
   PAWN_COLOR selectedColor;              /*!< Selected color */
   Combination *proposition;              /*!< Guesser proposition */
   bool validSolution;                    /*!< Validity of the solution */
   PAWN_COLOR *solution;                  /*!< Proposer combination */
   History *history;                      /*!< Combinations settings and history */
   FEEDBACK_COLOR *feedback;              /*!< Player feedback given to computer */ 
   unsigned int nbConfigs;                /*!< Total of possible combinations */
   unsigned int lastConfigIndex;          /*!< Index of last combination proposed by the compute */
   Combination **configs;                 /*!< All the possible configurations */
   SavedScores *save;                     /*!< Structure containing the previously saved scores */
};


struct model_main_menu_t {
   char pseudo[MAX_PSEUDO_LENGTH];  /*!< Saved player pseudo */
   bool validPseudo;                /*!< State of pseudo validity */
   ROLE role;                       /*!< Player role */
   unsigned int nbPawns;            /*!< Number of pawns selected */
};

struct score_t {
   char pseudo[MAX_PSEUDO_LENGTH]; /*!< Saved player pseudo */
   unsigned score;                 /*!< Score of saved player */
};

struct saved_scores_t {
   unsigned length;                /*!< Number of scores saved */
   Score **savedScores;            /*!< Saved score from players */
};


/**
 * \fn static Combination *create_combination(unsigned int nbPawns)
 * \brief Allocates memory for Combination structure and returns a pointer to
 * Combination.
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
 * \fn static History *create_history(unsigned int nbPawns, unsigned int
 * nbCombinations)
 * \brief Allocates memory for History structure and returns a pointer
 * to History.
 * 
 * \param nbPawns Number of pawns of a combination.
 * \param nbCombinations Number of combinations that the player can propose
 * during the game.
 * 
 * \post The memory for a History structure is allocated.
 * 
 * \return history a pointer to History,
 *         NULL in case of error.
 * 
 * */
static History *
create_history(unsigned int nbPawns, unsigned int nbCombinations);


/**
 * \fn static void destroy_history(History *history)
 * \brief Free the memory allocated to a History structure.
 * 
 * \param history a valid pointer to History.
 * 
 * \pre history != NULL.
 * \post The memory for the History structure is freed.
 * 
 * */
static void destroy_history(History *history);

/**
 * \fn static void update_score(ModelMastermind *mm)
 * \brief updates the score
 */
static void update_score(ModelMastermind *mm);


static Combination **
create_configs(unsigned int nbConfigs, unsigned int nbPawns);


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


static History *
create_history(unsigned int nbPawns, unsigned int nbCombinations) {
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

   strcpy(mmm->pseudo, "Guest");
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
   mm->validSolution = false;

   mm->proposition = create_combination(mmm->nbPawns);
   if(mm->proposition == NULL){
      free(mm);
      return NULL;
   }

   mm->solution = malloc(mmm->nbPawns * sizeof(PAWN_COLOR));
   if(mm->solution == NULL){
      destroy_combination(mm->proposition);
      free(mm);
      return NULL;
   }

   mm->feedback = malloc(mmm->nbPawns * sizeof(FEEDBACK_COLOR));
   if(mm->feedback == NULL){
      free(mm->solution);
      destroy_combination(mm->proposition);
      free(mm);
      return NULL;
   }

   for(unsigned int i = 0; i < mmm->nbPawns; i++){
      mm->solution[i] = PAWN_DEFAULT;
      mm->feedback[i] = FB_DEFAULT;
   }

   mm->history = create_history(mmm->nbPawns, NB_COMBINATIONS);
   if(mm->history == NULL){
      free(mm->feedback);
      free(mm->solution);
      destroy_combination(mm->proposition);
      free(mm);
      return NULL;
   }

   mm->nbConfigs = pow(NB_PAWN_COLORS, mm->history->nbPawns);
   mm->lastConfigIndex = 1;

   mm->configs = create_configs(mm->nbConfigs, mm->history->nbPawns);
   if(mm->configs == NULL){
      destroy_history(mm->history);
      free(mm->feedback);
      free(mm->solution);
      destroy_combination(mm->proposition);
      free(mm);
      return NULL;
   }

   mm->save = load_scores(SAVED_SCORES_PATH);
   if(mm->save == NULL){
      free(mm->solution);
      free(mm->proposition);
      destroy_history(mm->history);
      //TODO create destroyer for configs
      free(mm);
      return NULL;
   }

   return mm;
}


void destroy_model_mastermind(ModelMastermind *mm) {
   if(mm != NULL){
      if(mm->proposition != NULL)
         destroy_combination(mm->proposition);
      if(mm->solution != NULL)
         free(mm->solution);
      if(mm->feedback != NULL)
         free(mm->feedback);
      destroy_history(mm->history);
      free(mm);
   }
}


void generate_random_solution(ModelMastermind *mm) {
   assert(mm != NULL);

   srand(time(NULL));
   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->solution[i] = rand() % (NB_PAWN_COLORS - 1);
}


bool verify_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      if(mm->proposition->pawns[i] == PAWN_DEFAULT)
         return false;

   return true;
}


void reset_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   mm->proposition->nbCorrect = 0;
   mm->proposition->nbMisplaced = 0;

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->proposition->pawns[i] = PAWN_DEFAULT;
}


void reset_feedback(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->feedback[i] = FB_DEFAULT;
}


void
determine_feedback_proposition(ModelMastermind *mm, Combination *proposition,
                               PAWN_COLOR *solution) {
   assert(proposition != NULL && solution != NULL);

   unsigned int nbColorsInProposition[NB_PAWN_COLORS];
   unsigned int nbColorsInSolution[NB_PAWN_COLORS];

   for(unsigned int i = 0; i < NB_PAWN_COLORS; i++){
      nbColorsInProposition[i] = 0;
      nbColorsInSolution[i] = 0;
   }

   for(unsigned int i = 0; i < mm->history->nbPawns; i++){
      if(proposition->pawns[i] == solution[i]){
         proposition->nbCorrect++;
      } else{
         nbColorsInProposition[proposition->pawns[i]]++;
         nbColorsInSolution[solution[i]]++;
      }
   }

   for(unsigned int i = 0; i < NB_PAWN_COLORS; i++){
      if(nbColorsInProposition[i] < nbColorsInSolution[i])
         proposition->nbMisplaced += nbColorsInProposition[i];
      else
         proposition->nbMisplaced += nbColorsInSolution[i];
   }
}


void update_current_combination_index(ModelMastermind *mm) {
   assert(mm != NULL);

   mm->history->currentIndex--;
}


void verify_end_game(ModelMastermind *mm) {
   assert(mm != NULL);

   if(mm->history->combinations[mm->history->currentIndex]->nbCorrect ==
      mm->history->nbPawns || mm->history->currentIndex <= 0)
      mm->inGame = false;

   update_score(mm);
}


PAWN_COLOR get_selected_color(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->selectedColor;
}


ROLE get_role(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->role;
}


char *get_pseudo(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->savedPseudo;
}


bool get_in_game(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->inGame;
}


bool get_valid_solution(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->validSolution;
}


Combination *get_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->proposition;
}


PAWN_COLOR *get_solution(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->solution;
}


unsigned int get_nb_pawns(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->nbPawns;
}


unsigned int get_nb_combinations(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->nbCombinations;
}


int get_current_index(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->currentIndex;
}


Combination *get_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->combinations[mm->history->currentIndex];
}


PAWN_COLOR
get_pawn_last_combination(ModelMastermind *mm, unsigned int pawnIndex) {
   assert(mm != NULL && pawnIndex < mm->history->nbPawns);

   return mm->history->combinations[mm->history->currentIndex]->pawns[pawnIndex];
}


unsigned int get_nb_correct_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->combinations[mm->history->currentIndex]->nbCorrect;
}


unsigned int get_nb_misplaced_last_combination(ModelMastermind *mm) {
   assert(mm != NULL);

   return mm->history->combinations[mm->history->currentIndex]->nbMisplaced;
}


FEEDBACK_COLOR get_feedback_pawn(ModelMastermind *mm, unsigned int index) {
   assert(mm != NULL);

   return mm->feedback[index];
}


void set_proposition_in_history(ModelMastermind *mm) {
   assert(mm != NULL);

   mm->history->combinations[mm->history->currentIndex]->nbCorrect = mm->proposition->nbCorrect;
   mm->history->combinations[mm->history->currentIndex]->nbMisplaced = mm->proposition->nbMisplaced;

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->history->combinations[mm->history->currentIndex]->pawns[i] = mm->proposition->pawns[i];
}


char *get_main_menu_pseudo(ModelMainMenu *mmm) {
   assert(mmm != NULL);
   return mmm->pseudo;
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
   mm->proposition->pawns[i] = mm->selectedColor;
}


void set_proposition_as_solution(ModelMastermind *mm) {
   assert(mm != NULL);

   for(unsigned int i = 0; i < mm->history->nbPawns; i++)
      mm->solution[i] = mm->proposition->pawns[i];
}


void set_feedback_pawn(ModelMastermind *mm, unsigned int index) {
   assert(mm != NULL);

   mm->feedback[index] = (mm->feedback[index] + 1) % NB_FB_COLORS;
}


void update_last_combination_feedback(ModelMastermind *mm) {
   assert(mm != NULL);

   unsigned int nbCorrect = 0;
   unsigned int nbMisplaced = 0;

   for(unsigned int i = 0; i < mm->history->nbPawns; i++){
      if(mm->feedback[i] == FB_BLACK)
         nbCorrect += 1;

      if(mm->feedback[i] == FB_WHITE)
         nbMisplaced += 1;
   }

   mm->history->combinations[mm->history->currentIndex]->nbCorrect = nbCorrect;
   mm->history->combinations[mm->history->currentIndex]->nbMisplaced = nbMisplaced;
}


void set_valid_solution_true(ModelMastermind *mm) {
   assert(mm != NULL);

   mm->validSolution = true;
}


SavedScores *get_saved_scores(ModelMastermind *mm) {
   assert(mm != NULL);
   return mm->save;
}

SavedScores *load_scores(const char *filePath) {
   assert(filePath != NULL);

   SavedScores *save = malloc(sizeof(SavedScores));
   if(save == NULL)
      return NULL;

   if(access(filePath, F_OK) == 0){
      printf("Previous save found\n");
      FILE *pFile = fopen(filePath, "r");
      if(pFile == NULL){
         return NULL; // File name is ill-formed
      }

      if(!fscanf(pFile, "%u\n", &save->length)){
         free(save);
         fclose(pFile);
         return NULL;//File content ill-formed
      }

      save->savedScores = malloc(save->length * sizeof(Score *));
      if(save->savedScores == NULL){
         free(save);
         fclose(pFile);
         return NULL;
      }

      for(unsigned i = 0; save->length > i; i++){
         save->savedScores[i] = malloc(sizeof(Score));
         if(save->savedScores[i] == NULL){
            for(unsigned j = 0; j < i; j++){
               free(save->savedScores[j]);
            }
            free(save->savedScores);
            free(save);
            fclose(pFile);
            return NULL;
         }
         if(!fscanf(pFile, "%s %u\n", save->savedScores[i]->pseudo,
                    &save->savedScores[i]->score)){
            for(unsigned j = 0; j < i; j++){
               free(save->savedScores[j]);
            }
            free(save);
            fclose(pFile);
            return NULL;
         }
      }
   } else{
      save->length = 0;
      printf("No previous save\n");
      save->savedScores = malloc(sizeof(Score *));
      if(save->savedScores == NULL){
         free(save);
         return NULL;
      }
   }

   printf("load_score finished\n");
   return save;
}

int write_scores(SavedScores *scores, const char *filePath) {
   assert(scores != NULL && filePath != NULL);

   printf("Attend to write scores\n");

   FILE *pFile = fopen(filePath, "w");
   if(pFile == NULL){
      return -1; // File name is ill-formed
   }

   fprintf(pFile, "%u\n", scores->length);

   for(unsigned i = 0; i < scores->length; i++){
      printf("%s %u\n", scores->savedScores[i]->pseudo,
             scores->savedScores[i]->score);
      fprintf(pFile, "%s %u\n", scores->savedScores[i]->pseudo,
              scores->savedScores[i]->score);
   }

   destroy_saved_scores(scores);

   return 0;
}

void destroy_saved_scores(SavedScores *scores) {
   for(unsigned j = 0; j < scores->length; j++){
      free(scores->savedScores[j]);
   }
   free(scores);
}

static Combination **
create_configs(unsigned int nbConfigs, unsigned int nbPawns) {
   Combination **configs = malloc(nbConfigs * sizeof(Combination *));
   if(configs == NULL)
      return NULL;

   for(unsigned int i = 0; i < nbConfigs; i++){
      configs[i] = create_combination(nbPawns);
      if(configs[i] == NULL){
         for(unsigned int j = 0; j < i; ++j)
            destroy_combination(configs[i]);

         free(configs);
         return NULL;
      }

      unsigned int factor = i;
      for(unsigned int j = 0; j < nbPawns; j++){
         configs[i]->pawns[nbPawns - j - 1] = factor % (NB_PAWN_COLORS - 1);
         factor /= (NB_PAWN_COLORS - 1);
      }
   }

   return configs;
}


void find_next_proposition(ModelMastermind *mm) {
   assert(mm != NULL);

   if(mm->history->currentIndex == NB_COMBINATIONS - 1)
      for(unsigned int j = 0; j < mm->history->nbPawns; j++)
         mm->proposition->pawns[j] = mm->configs[0]->pawns[j];

   else{
      int nextCombiIndex = -1;
      for(unsigned int i = mm->lastConfigIndex;
          nextCombiIndex == -1 && i < mm->nbConfigs; i++){
         determine_feedback_proposition(mm, mm->configs[i],
                                        mm->history->combinations[
                                                mm->history->currentIndex +
                                                1]->pawns);

         if(mm->configs[i]->nbCorrect ==
            mm->history->combinations[mm->history->currentIndex +
                                      1]->nbCorrect &&
            mm->configs[i]->nbMisplaced ==
            mm->history->combinations[mm->history->currentIndex +
                                      1]->nbMisplaced)
            nextCombiIndex = i;
      }

      if(nextCombiIndex != -1){
         for(unsigned int j = 0; j < mm->history->nbPawns; j++)
            mm->proposition->pawns[j] = mm->configs[nextCombiIndex]->pawns[j];

         mm->lastConfigIndex = nextCombiIndex + 1;
      }
   }
}

static void update_score(ModelMastermind *mm) {
   assert(mm != NULL);

   printf("Update score\n");
   bool alreadySavedPlayer = false;

   for(unsigned i = 0; i < mm->save->length && !alreadySavedPlayer; i++){
      if(!strcmp(mm->save->savedScores[i]->pseudo, mm->savedPseudo)){
         printf("Player found in save, pseudo: %s score: %u index: %u\n",mm->save->savedScores[i]->pseudo,
                mm->save->savedScores[i]->score, i);
         mm->save->savedScores[i]->score += 1;
         printf("Player found in save, pseudo: %s score: %u index: %u\n",
                mm->save->savedScores[i]->pseudo,
                mm->save->savedScores[i]->score, i);
         alreadySavedPlayer = true;
      }
   }

   if(alreadySavedPlayer == false){
      mm->save->length += 1;
      Score **tmp = realloc(mm->save->savedScores,
                            mm->save->length * sizeof(Score *));
      if(tmp == NULL){
         for(unsigned j = 0; j < mm->save->length-1; j++){
            free(mm->save->savedScores[j]);
         }
         free(mm->save->savedScores);
         free(mm->save);
      }

      else{
         mm->save->savedScores = tmp;
         mm->save->savedScores[mm->save->length-1] = malloc(sizeof (Score));
         if(mm->save->savedScores[mm->save->length-1] == NULL) {
            for(unsigned j = 0; j < mm->save->length-2; j++){
               free(mm->save->savedScores[j]);
            }
            free(mm->save->savedScores);
            free(mm->save);
         }
         else{
            strcpy(mm->save->savedScores[mm->save->length - 1]->pseudo,
                   mm->savedPseudo);
            mm->save->savedScores[mm->save->length - 1]->score = 1;
         }
      }
   }
}
