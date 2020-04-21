
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
	}

}