
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "title_screen.h"

//#include "champ_select.h"

int main() {
	int black[4] = {0,0,0,255};

	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(LFEN, HFEN, "Le Combat Des Animaux", 0, black, ECRAN_TITRE);

	Launcher();
	//ChampSelect();

	while (!PollEvent(NULL)) {
		updateWindow();
		displayWindow();

		SDL_Delay(16);
	}

	//freeCharacters(characterG, characterD);
	closeAllWindow();
	closeAllSANDAL2();



	return 0;
}

