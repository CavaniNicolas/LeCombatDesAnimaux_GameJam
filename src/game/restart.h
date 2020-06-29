/* -------------------------------------------------------------------------- */
/* Nom du fichier : restart.h                                                 */
/* Objectifs : Déclarations des fonctions pour le restart du jeu              */
/* Fonctions :                                                                */
/*  -                                                                         */
/* -------------------------------------------------------------------------- */

#ifndef RESTART_H
#define RESTART_H
#include "character.h"


enum EndGameChoice {
	None = 0,
	Again = 1,
	Restart = 2,
	Quit = 3,
};


void isGameFinished(Element * character);


void restartGameScreen(Element * character);


void removeWinBubbles();


void choiceClicked(Element * box, int i);


void restartActions(Element * character);


void freeCharacter(Element * character);

#endif

