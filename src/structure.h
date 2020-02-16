#ifndef MAIN_H
#define MAIN_H

#include <SANDAL2/SANDAL2.h>

#define LFEN 1400
#define HFEN 800
#define NBPERSO 4

enum Player {
	JOUEUR_G = 0,
	JOUEUR_D = 1
};

enum Display {
	ECRAN_TITRE = 0,
	ECRAN_CHOIX_PERSO = 1,
	ECRAN_CHOIX_MAP = 2,
	ECRAN_FIGHT = 3
};

// liste des plans du menu
enum PlanMenu {
  //1 ECRAN_TITRE
	PlanTitreFond = 15,
	PlanTitre = 14,
	PlanStartUp = 8,
	PlanStartDown = 7,
	//PlanAnim = 6,
	PlanRideau = 5,

	//2 ECRAN_CHOIX_PERSO
	PlanContourNoir = 13,
	PlanContourBlanc = 12,
	PlanFondNoir = 11,
	PlanBtnRetourUp = 10,
	PlanBtnRetourDown = 9,
	PlanPerso = 8,
	PlayerContourPersoUp = 7,
	PlayerContourPersoDown = 6,
	PlanInfo = 5,
	PlanInfoModif = 4,
	PlanBtnValiderUp = 3,
	PlanBtnValiderDown = 2
};

typedef struct DataStart {
	int verif;
}DataStart;

typedef struct DataValidate {
	int verif;
}DataValidate;

typedef struct DataRetour {
	int verif;
}DataRetour;

// liste des plans du fight
enum {
	PlanDecor = 20,
	PlanCharacter = 0,
};


#endif
