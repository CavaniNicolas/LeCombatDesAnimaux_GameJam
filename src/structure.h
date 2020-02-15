#ifndef MAIN_H
#define MAIN_H

#include <SANDAL2/SANDAL2.h>

#define LFEN 1400
#define HFEN 800

enum Player {
	JOUEUR_G = 0,
	JOUEUR_D = 1
};

enum Display {
	ECRAN_TITRE = 0,
	ECRAN_CHOIX_PERSO = 1,
	ECRAN_CHOIX_MAP = 2,
	ECRAN_FIGHT = 3
}

// liste des plans du menu
enum PlanMenu {
  //1 ECRAN_TITRE
	PlanTitre = 8,
	PlanStart = 6,
	PlanAnim = 5,
	PlanRideau = 4
}

// liste des plans du fight
enum {
	PlanDecor = 10,
	PlanCharacter = 0,
};


#endif
