
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "fight.h"


void launchCharacterAttack(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	if (k == kc->attack1) {
		if (d->allowAttack1 == true) {
			d->attack1 = true;
			printf("P%d : attack1\n", d->idPlayer);
		}
	}

	else if (k == kc->attack2) {
		if (d->allowAttack2 == true) {
			d->attack2 = true;
			printf("P%d : attack2\n", d->idPlayer);
		}
	}

	else if (k == kc->parry) {
		if (d->allowParry == true) {
			d->parry = true;
			printf("P%d : parry\n", d->idPlayer);
		}
	}

}