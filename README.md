# ARK

A repo for the fourth project of INFO0030-3: Porjet de Programmation at Uliège

## Content of the repository

A directory for the report, one for the code, and one for the used images

## Requirements

- A C complier
- GTK 2.0

## Statement

Create a mastermind in C following the guidelines given in [Énoncé.pdf](Énoncé.pdf) using GTK 2.0
This project was done in groups of two

## Marks

Final note: 19.5/20
Reviewer comment: Respect énoncé: Ok.. Exactitude: Ok.. Langage: Il faut vérifier les retours des fonctions.. Style: Evitez le ALL_CAPS pour les noms des énumérations parce que le ALL_CAPS est habituellement associé aux constantes. Pas d'accolades pour les IFs/FORs qui contiennent une seule ligne de code. Evitez le ALL_CAPS pour une variable example: SCORE_LABELS dans view_mastermind.c.. Demo: Très bien.. Rapport: Très bon rapport.. Apprentissage: Ok.

## Known issues

- When closing the score menu with the exit button of the window instead of the ok button; it is deleted instead of hide and a segfault happen when trying to open it again. 
- In the mode where you don't guess, the algorithm make attemps that he should know are false
