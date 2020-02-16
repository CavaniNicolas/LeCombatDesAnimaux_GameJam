
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "fight.h"
#include "character.h"


void initFight(int idCharacterG, int idCharacterD, int idMap) {
	char s[16] = "assets/map0.jpg";
	s[10] = idMap+48;
	createImage(0, 0, LFEN,HFEN, s, ECRAN_FIGHT, PlanDecor);

	Element * characterG = NULL;
	Element * characterD = NULL;
	initCharacter(JOUEUR_G, idCharacterG, &characterG);
	initCharacter(JOUEUR_D, idCharacterD, &characterD);

	addElementToElement(characterG, characterD);
	addElementToElement(characterD, characterG);

	setKeyPressedElement(characterG,moveCharacterOn);
	setKeyReleasedElement(characterG,moveCharacterOff);
	setActionElement(characterG,actionCharacters);

	setKeyPressedElement(characterD,moveCharacterOn);
	setKeyReleasedElement(characterD,moveCharacterOff);
	setActionElement(characterD,actionCharacters);
}

void actionCharacters(Element * character) {
	moveCharacter(character);
	collisionCharacters(character);
}

void collisionCharacters(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	// if (character->x > character2->x) {
	// 	puts("ques");
	// 	d->right = false;
	// 	d2->left = false;
	// }

	if (d->idPlayer == JOUEUR_G && (character->x + d->width > character2->x)) {
		//d->limit = true;
		d->right = false;
		d2->left = false;
	}

	if (d->idPlayer == JOUEUR_D && (character->x < character2->x + d2->width)) {
		//d->limit = true;
		d->right = false;
		d2->left = false;
		//printf("%d\n",SDL_GetTicks());
	}
}