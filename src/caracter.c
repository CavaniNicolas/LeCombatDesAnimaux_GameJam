
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "caracter.h"


void initDataCaracter(int id, Element * caracter) {
	DataCaracter_t * d = malloc(sizeof(DataCaracter_t));

	if (d != NULL) {

		d->id = id;
		d->hp = 100;
		d->left = 0;
		d->right = 0;
		d->jump = 0;
		d->attack1 = 0;
		d->attack2 = 0;
		d->parry1 = 0;
		d->parry2 = 0;

		d->caracter = caracter;
	}
}


Element * initCaracter(int id, Element * caracter) {
	DataCaracter_t * d = initDataCaracter(id, caracter);

	if (d != NULL) {
		switch (id) {
			case JOUEUR_G:
				caracter = createImage(100,450,300,300,"assets/kingKrool.png",0,PlanCaracter);
			break;

			case JOUEUR_D:
				caracter = createImage(1000,450,300,300,"assets/donkeyKong.png",0,PlanCaracter);
				caracter->flip = SANDAL2_FLIP_HOR;
			break;

				default:
			break;
		}
	}

	return caracter;
}


void moveCaracter(Element * caracter, SDL_Keycode k) {
	DataCaracter_t * d = caracter->data;
	switch (k) {
		case 'a': // 'q'
 			
			break;
		case 'd':

			break;
		case 'j':

			break;
		case 'l':

			break;
	}

}

void stopCaracter(Element * caracter, SDL_Keycode k) {
	DataCaracter_t * d = caracter->data;
}

setKeyPressedElement(caracter,moveCaracter);
setKeyReleasedElement(caracter,stopCaracter);
setActionElement(canon,moveCaracter);