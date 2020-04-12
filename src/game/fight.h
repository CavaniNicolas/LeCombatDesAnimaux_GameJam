
#ifndef FIGHT_H
#define FIGHT_H

enum PlanFight {
	PlanBackgroundF = 99,

	PlanHealthBars = 89,

	PlanCharacters = 79,

};


// lance le jeu, init l'affichage et les persos (avec toutes leurs fonctionnalitées)
void initFight(int idCharacterG, int idCharacterD, int idMap);

// affiche les barres de vie initiales
void initHealthBars();


#endif