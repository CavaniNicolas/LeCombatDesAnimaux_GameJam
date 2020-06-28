
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "attacks.h"
#include "fight.h"


void launchCharacterAttack(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	if (d->allowAttacks == true) {
		d->attacks = true;

		if (kp->attack1_P) {
			d->attack1 = true;

			printf("P%d : attack1\n", d->idPlayer);
			damageOpponent(character);
		}

		else if (kp->attack2_P) {
			d->attack2 = true;

			printf("P%d : attack2\n", d->idPlayer);
		}

		else if (kp->parry_P) {
			d->parry = true;

			printf("P%d : parry\n", d->idPlayer);
		}

		// pas le droit de se deplacer lors de ces mouvements
		d->allowJump = false;
		d->allowLeft = false;
		d->allowRight = false;
		d->left = false;
		d->right = false;
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
	Element * characterHurt = nextIteratorElement(characterAttacking);

	DataCharacter_t * d = characterAttacking->data;
	DataCharacter_t * d2 = characterHurt->data;

	isCharacterInRange(characterAttacking);
printf("%d\n", d->inRange);

	if (d->inRange) {
		if (d2->parry) {
			d2->hp = d2->hp - d->strengthCte * 0.4;

		} else {
			d2->hp = d2->hp - d->strength;
		}
		showHealthBar(characterHurt);
	}


	if (d2->hp <= 0) {
		d2->dyingReviving = true;
		printf("Joueur %d a perdu\n", d2->idPlayer);
		endRound(characterHurt);
	}
}


void showHealthBar(Element * characterHurt) {
	DataCharacter_t * d = characterHurt->data;
	HealthBar_t * hb = d->healthBar;

	if (d->hp > 0) {
		hb->healthBar->width = (d->hp * hb->wBarMax / d->hpCte) - 4;

	} else {
		hb->healthBar->width = 0;
	}
}


void adaptHealthBar(Element * character) {
	DataCharacter_t * d = character->data;
	HealthBar_t * hb = d->healthBar;

	if (hb->damageBar->width > hb->healthBar->width) {
		hb->damageBar->width -= 4;

	} else {
		hb->damageBar->width = hb->healthBar->width;
	}
}
