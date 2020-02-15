
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "character.h"


void initDataCharacter(int id, Element * character) {
	DataCharacter_t * d = malloc(sizeof(DataCharacter_t));

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
	character->data = d;
}


void initCharacter(int id, Element * character) {
	DataCharacter_t * d = initDataCharacter(id, character);

	if (d != NULL) {
		switch (id) {
			case JOUEUR_G:
				character = createImage(100,450,300,300,"assets/kingKrool.png",0,PlanCharacter);
			break;

			case JOUEUR_D:
				character = createImage(1000,450,300,300,"assets/donkeyKong.png",0,PlanCharacter);
				character->flip = SANDAL2_FLIP_HOR;
			break;

				default:
			break;
		}
	}
}


void moveCharacterOn(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
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

void moveCharacterOff(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
}

void moveCharacter() {

}

setKeyPressedElement(character,moveCharacterOn);
setKeyReleasedElement(character,moveCharacterOff);
setActionElement(canon,moveCharacter);