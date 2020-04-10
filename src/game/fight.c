
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "fight.h"


void launchCharacterAttack(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	if (d->allowAttacks == true) {
		d->attacks = true;

		if (k == kc->attack1) {
			d->attack1 = true;

			// pas le droit de se deplacer lors de ce mouvement
			d->allowJump = false;
			d->allowLeft = false;
			d->allowRight = false;
			d->left = false;
			d->right = false;
			printf("P%d : attack1\n", d->idPlayer);
		}

		else if (k == kc->attack2) {
			d->attack2 = true;

			// pas le droit de se deplacer lors de ce mouvement
			d->allowJump = false;
			d->allowLeft = false;
			d->allowRight = false;
			d->left = false;
			d->right = false;
			printf("P%d : attack2\n", d->idPlayer);
		}

		else if (k == kc->parry) {
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