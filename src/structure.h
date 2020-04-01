#ifndef MAIN_H
#define MAIN_H

#define LFEN 1400
#define HFEN 800
#define NBPERSO 2
#define NBMAP 3
#define GRAVITY 4

enum Player {
	PLAYER_L = 0,
	PLAYER_R = 1
};

enum Display { //good
	TITLE_SCREEN = 0,
	CHAMP_SELECT = 1,
	MAP_SELECT = 2,

	FIGHT_SCREEN = 3
};

#endif
