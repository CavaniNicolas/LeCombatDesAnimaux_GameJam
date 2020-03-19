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
	MAP_SELECT = 2,

	//a supprimer un fois terminé
	ECRAN_CHOIX_MAP = 2,
	ECRAN_FIGHT = 3
};

#endif
