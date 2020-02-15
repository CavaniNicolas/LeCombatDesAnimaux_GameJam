
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "caracter.h"

int main() {
	int black[4] = {0,0,0,255};

	initAllSANDAL2(IMG_INIT_JPG);
	createWindow(LFEN,HFEN,"Le Combat Des Animaux",0,black,ECRAN_TITRE);

	createImage(0,0,LFEN,HFEN,"assets/beach.jpg",0,PlanDecor);


	Element * caracter1 = NULL;
	Element * caracter2 = NULL;

	initCaracter(0, caracter1);
	initCaracter(1, caracter2);



	while (!PollEvent(NULL)) {
		updateWindow();
		displayWindow();

		SDL_Delay(16);
	}

	closeAllWindow();
	closeAllSANDAL2();
	return 0;
}