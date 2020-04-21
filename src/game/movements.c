
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "movements.h"


void moveCharacterOn(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	if (d->attacks == false) {

		if (kp->left_P) {
			if (d->allowLeft == true) {
				d->left = true;
			}
		}

		if (kp->right_P) {
			if (d->allowRight == true) {
				d->right = true;
			}
		}

		if (kp->left_P && kp->right_P) {
			d->left = false;
			d->right = false;
		}

		if (kp->jump_P) {
			if (d->jump == false && d->allowJump == true) {
				d->jump = true;
				d->allowAttacks = false;
			}
		}
	}

}


void moveCharacterOff(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	if (kp->left_P == false) {
		d->left = false;
	}

	if (kp->right_P == false) {
		d->right = false;
	}

}


void moveCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double speed = d->speed;

	if (d->left) {
		if ((character->x)-speed > 0) {
			moveElement(character, -speed, 0);
		} else {
			d->left = false;
		}
	}

	if (d->right) {
		if ((character->x)-speed < LFEN-(d->width)) {
			moveElement(character, speed, 0);
		} else {
			d->left = false;
		}
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
			d->jumpForceTmp = d->jumpForceCte;
			d->jumpLagTmp = SDL_GetTicks();
			d->speed = d->speedCte * 0.5;
		}
	}

	// jump Lag
	if(d->allowJump == false && d->jump == false) {
		if ((int)SDL_GetTicks() - d->jumpLagTmp >= d->jumpLagCte) {
			d->allowJump = true;
			d->allowAttacks = true;
			d->speed = d->speedCte;
			puts("jump lag end");
		}
	}

}


void collisionCharacters(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	if (d->idPlayer == PLAYER_L && (character->x + d->width - d->hitboxSize > character2->x + d2->hitboxSize)) {
		d->allowRight = false;
		d2->allowLeft = false;
		d->right = false;
		d2->left = false;

	} else {
		d->allowRight = true;
		d2->allowLeft = true;
	}

	if (d->idPlayer == PLAYER_R && (character->x + d->hitboxSize < character2->x + d2->width - d2->hitboxSize)) {
		d->allowLeft   = false;
		d2->allowRight = false;
		d->left   = false;
		d2->right = false;

	} else {
		d->allowLeft   = true;
		d2->allowRight = true;
	}
}
