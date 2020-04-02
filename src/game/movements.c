
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "movements.h"


void moveCharacterOn(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	if (k == kc->left) {
		if (d->allowLeft == true) {
				d->left = true;
		}
	}

	else if (k == kc->right) {
		if (d->allowRight == true) {
			d->right = true;
		}
	}

	else if (k == kc->jump) {
		if (d->jump == false && d->allowJump == true) {
			d->jump = true;
		}
	}

}

void moveCharacterOff(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	if (k == kc->left) {
 		d->left = false;
 	}

	else if (k == kc->right) {
		d->right = false;
	}

}


void moveCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double speed = (d->speed)/8;

	if (d->left) {
		if ((character->x)-speed > 0)
			moveElement(character, -speed, 0);
	}

	if (d->right) {
		if ((character->x)-speed < LFEN-(d->width))
			moveElement(character, speed, 0);
	}
}


void jumpCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double groundLevel = HFEN-50-(d->height);
	// ajouter la gravite propre a un perso

	// si autorisation de sauter (au sol ou en l'air)
	// alors deplacer le perso
	if (d->jump == true) {

		if (character->y - d->jumpForceTmp + GRAVITY < groundLevel) {
			character->y -= (d->jumpForceTmp + GRAVITY);
			d->jumpForceTmp -= GRAVITY;
		}
	// sinon, d->jump==true mais on est plus en l'air
	// se positionner au niveau du sol
	// attendre un peu avant de resauter
		else {
			character->y = groundLevel;
			d->jump = false;
			d->jumpForceTmp = d->jumpForce;
			d->jumpLagTmp = SDL_GetTicks();
		}
	}

	// jumpLag
	if(d->allowJump == false && d->jump == false) {
		if ((int)SDL_GetTicks() - d->jumpLagTmp >= d->jumpLag) {
			d->allowJump = true;
			puts("jump again");
		}
	}

}


void collisionCharacters(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	if (d->idPlayer == PLAYER_L && (character->x + d->width > character2->x)) {
		d->allowRight = false;
		d2->allowLeft = false;
		d->right = false;
		d2->left = false;

	} else {
		d->allowRight = true;
		d2->allowLeft = true;
	}

	if (d->idPlayer == PLAYER_R && (character->x < character2->x + d2->width)) {
		d->allowLeft   = false;
		d2->allowRight = false;
		d->left   = false;
		d2->right = false;

	} else {
		d->allowLeft   = true;
		d2->allowRight = true;
	}
}
