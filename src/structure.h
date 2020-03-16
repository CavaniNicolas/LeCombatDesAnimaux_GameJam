#ifndef MAIN_H
#define MAIN_H

#define LFEN 1400
#define HFEN 800
#define NBPERSO 2
#define NBMAP 3
#define GRAVITY 4

enum Player {
	JOUEUR_G = 0,
	JOUEUR_D = 1
};

enum Perso {
	GORILLE = 0,
	CROCODILE = 1,
	DRAGON = 2
};

enum Display { //good
	TITLE_SCREEN = 0,
	CHAMP_SELECT = 1,

	//a supprimer un fois terminé
	ECRAN_TITRE = 0,
	ECRAN_CHOIX_PERSO = 1,
	ECRAN_CHOIX_MAP = 2,
	ECRAN_FIGHT = 3
};


// liste des plans du menu
enum PlanMenu {
	//3 ECRAN_CHOIX_MAP
	PlanMapUp = 5,
	PlanMapDown = 4
};


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
