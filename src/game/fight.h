/* -------------------------------------------------------------------------- */
/* Nom du fichier : fight.h                                                   */
/* Objectifs : Déclarations des fonctions pour le jeu en général              */
/* Fonctions :                                                                */
/*  - initFight                                                               */
/* -------------------------------------------------------------------------- */

#ifndef FIGHT_H
#define FIGHT_H

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


#endif
