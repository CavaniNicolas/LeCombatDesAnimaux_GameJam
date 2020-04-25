/* -------------------------------------------------------------------------- */
/* Nom du fichier : fight.h                                                   */
/* Objectifs : Déclarations des fonctions pour le jeu en général              */
/* Fonctions :                                                                */
/*  - initFight                                                               */
/*  - endRound                                                                */
/* -------------------------------------------------------------------------- */

#ifndef FIGHT_H
#define FIGHT_H
#include "character.h"

enum PlanFight {
	PlanBackgroundF = 99,

	PlanHealthBars = 89,

	PlanCharacters = 79,

};


/* -------------------------------------------------------------------------- */
/* initFight                                                                  */
/*       Lance le jeu, init l'affichage, les persos et leurs fonctionnalitées */
/*                                                                            */
/* En entrée: idCharacterG (int) : id du perso choisi par le joueur de gauche */
/*            idCharacterD (int) : id du perso choisi par le joueur de droite */
/*            idMap        (int) : id de la map choisie                       */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void initFight(int idCharacterG, int idCharacterD, int idMap);


/* -------------------------------------------------------------------------- */
/* endRound                                                                   */
/*       Action à faire lorsqu'un round se termine                            */
/*                                                                            */
/* En entrée: characterLost (Element *) : personnage qui a perdu le round     */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void endRound(Element * characterLost);



void actionRoundTransitions(Element * character);

void resurrect(Element * character);

void resetHealthBar(Element * character);

void resetPosition(Element * character);


void toggleAllowMovements(Element * character);



// a ajouter dans lentete when done
//void freeAllData(Element * characterL);


#endif
