
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "attacks.h"


void launchCharacterAttack(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	if (d->allowAttacks == true) {
		d->attacks = true;

		if (kp->attack1_P) {
			d->attack1 = true;

			// pas le droit de se deplacer lors de ce mouvement
			d->allowJump = false;
			d->allowLeft = false;
			d->allowRight = false;
			d->left = false;
			d->right = false;
			printf("P%d : attack1\n", d->idPlayer);
		}

		else if (kp->attack2_P) {
			d->attack2 = true;

			// pas le droit de se deplacer lors de ce mouvement
			d->allowJump = false;
			d->allowLeft = false;
			d->allowRight = false;
			d->left = false;
			d->right = false;
			printf("P%d : attack2\n", d->idPlayer);
		}

		else if (kp->parry_P) {
			d->parry = true;

			// pas le droit de se deplacer lors de ce mouvement
			d->allowJump = false;
			d->allowLeft = false;
			d->allowRight = false;
			d->left = false;
			d->right = false;
			printf("P%d : parry\n", d->idPlayer);
		}
	damageOpponent(character);
	}
}


void isCharacterInRange(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	if ((d->idPlayer == PLAYER_L && (character->x + d->width > character2->x)) || 
		(d->idPlayer == PLAYER_R && (character->x < character2->x + d2->width))) {
		d->inRange = true;
		d2->inRange = true;
	} else {
		d->inRange = false;
		d2->inRange = false;
	}

}


void damageOpponent(Element * characterAttacking) {
	initIteratorElement(characterAttacking);
	Element * character2 = nextIteratorElement(characterAttacking);

	DataCharacter_t * d = characterAttacking->data;
	DataCharacter_t * d2 = character2->data;

	isCharacterInRange(characterAttacking);
printf("%d\n", d->inRange);

	if (d->inRange) {
		if (d2->parry) {
			d2->hp = d2->hp - d->strengthCte * 0.4;

		} else {
			d2->hp = d2->hp - d->strength;
		}
	}

	resizeHealthBar(character2);
}


void resizeHealthBar(Element * characterHurt) {
	DataCharacter_t * d = characterHurt->data;
	HealthBar_t * hb = d->healthBar;

	if (d->hp > 0) {
		hb->healthBar->width = (d->hp * hb->wBarMax / d->hpCte) - 4;

	} else {
		hb->healthBar->width = 0;
		d->dead = true;
		printf("Joueur %d a perdu\n", d->idPlayer);
		endRound(characterHurt);
	}
}


void endRound(Element * characterLost) {
	initIteratorElement(characterLost);
	Element * character2 = nextIteratorElement(characterLost);

	DataCharacter_t * d = characterLost->data;
	DataCharacter_t * d2 = character2->data;

	int deadTimer = SDL_GetTicks();

	if (d->dead) {
		d->allowLeft = false;
		d->allowRight = false;
		d->allowJump = false;
		d->allowAttacks = false;

		d2->allowLeft = false;
		d2->allowRight = false;
		d2->allowJump = false;
		d2->allowAttacks = false;

		while (SDL_GetTicks() - deadTimer) {
			
		}
	}

}
