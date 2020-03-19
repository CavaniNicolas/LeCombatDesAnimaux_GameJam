
/*
* Projet Game Jam : Le combat des animaux
* Auteur : Nicolas Cavani
*/

#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "title_screen.h"

//#include "champ_select.h"

int main() {
	int black[4] = {0,0,0,255};

	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(LFEN, HFEN, "Le Combat Des Animaux", 0, black, TITLE_SCREEN);

	Launcher();
	//ChampSelect();

	while (!PollEvent(NULL)) {
		updateWindow();
		displayWindow();

		SDL_Delay(16);
	}

	closeAllWindow();
	closeAllSANDAL2();

	return 0;
}

