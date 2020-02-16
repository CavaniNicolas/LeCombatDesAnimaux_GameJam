#ifndef MAIN_H
#define MAIN_H

#include <SANDAL2/SANDAL2.h>

#define LFEN 1400
#define HFEN 800
#define NBPERSO 4
#define NBMAP 3
#define GRAVITY 4

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
	PlanPersoUp = 8,
	PlanPersoDown = 7,
	PlanInfo = 6,
	PlanInfoModif = 5,
	PlanBtnValiderUp = 3,
	PlanBtnValiderDown = 2,

	//3 ECRAN_CHOIX_MAP
	PlanMapUp = 5,
	PlanMapDown = 4
};

typedef struct DataStart {
	int verif;
}DataStart;

typedef struct DataValidate {
	int verif;
	int indiceJoueur;
	int sauvegarde;
}DataValidate;

typedef struct DataValidate2 {
	int verif;
	int indiceJoueur;
	int indiceJoueur2;
}DataValidate2;

typedef struct DataRetour {
	int verif;
}DataRetour;

typedef struct DataPerso {
	int id;
	int verif;
	int isSelected;
}DataPerso;

typedef struct DataMap {
	int id;
	int verif;
	int isSelected;
}DataMap;

// liste des plans du fight
enum {
	PlanDecor = 20,
	PlanCharacter = 0,
};


#endif
