
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "caracter.h"


void initDataCaracter(int id, Element * caracter) {
	DataCaracter_t * d = malloc(sizeof(DataCaracter_t));

	if (d != NULL) {

		d->id = id;
		d->hp = 100;
		d->left = false;
		d->right = false;
		d->jump = false;
		d->attack1 = false;
		d->attack2 = false;
		d->parry1 = false;
		d->parry2 = false;
	}
	caracter->data = d;
}


void initCaracter(int id, Element * caracter) {
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
}


void moveCaracterOn(Element * caracter, SDL_Keycode k) {
	DataCaracter_t * d = caracter->data;
	switch (k) {
		case 'a': // 'q'
 			d->left = true;
			break;

		case 'd':
			d->right = true;
			break;

		case 's':
			d->jump = true;
			break;


		case 'j':
 			d->left = true;
			break;

		case 'l':
			d->right = true;
			break;

		case 'k':
			d->jump = true;
			break;
	}

}

void moveCaracterOff(Element * caracter, SDL_Keycode k) {
	DataCaracter_t * d = caracter->data;
}

void moveCaracter() {

}

setKeyPressedElement(caracter,moveCaracterOn);
setKeyReleasedElement(caracter,moveCaracterOff);
setActionElement(canon,moveCaracter);