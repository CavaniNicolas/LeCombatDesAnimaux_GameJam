
/*
* Projet Game Jam : Le combat des animaux
* Auteur : Nicolas Cavani
*/

#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "title_screen.h"

#include "champ_select.h"
#include "map_select.h"
#include "fight.h"


int main() {
	int black[4] = {0,0,0,255};

	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(LFEN, HFEN, "Le Combat Des Animaux", 0, black, TITLE_SCREEN);

	//Launcher();
	//ChampSelect();
	//MapSelect();
	initFight(0, 0, 1);

printf("%d\n", SDL_GetTicks());
	while (!PollEvent(NULL)) {
		updateWindow();
		displayWindow();
		SDL_Delay(16);
	}

	closeAllWindow();
	closeAllSANDAL2();

	return 0;
}

