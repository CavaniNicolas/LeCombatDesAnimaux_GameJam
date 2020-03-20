
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "fight.h"
#include "character.h"


void initFight(int idCharacterG, int idCharacterD, int idMap) {
	setDisplayCodeWindow(ECRAN_FIGHT);


	char s[16] = "assets/map1.jpg";
	s[10] = idMap+48;
	createImage(0, 0, LFEN,HFEN, s, ECRAN_FIGHT, 1);

	Element * characterG = NULL;
	Element * characterD = NULL;
	initCharacter(JOUEUR_G, idCharacterG, &characterG);
	initCharacter(JOUEUR_D, idCharacterD, &characterD);

	/*Lie les deux personnages entre eux*/
	addElementToElement(characterG, characterD);
	addElementToElement(characterD, characterG);

	/*Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer*/
	setKeyPressedElement(characterG, moveCharacterOn);
	setKeyReleasedElement(characterG, moveCharacterOff);
	setActionElement(characterG, actionCharacters);

	/*Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer*/
	setKeyPressedElement(characterD, moveCharacterOn);
	setKeyReleasedElement(characterD, moveCharacterOff);
	setActionElement(characterD, actionCharacters);
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

	if (d->idPlayer == JOUEUR_G && (character->x + d->width > character2->x)) {
		d->allowRight = false;
		d2->allowLeft = false;
		d->right = false;
		d2->left = false;

	} else {
		d->allowRight = true;
		d2->allowLeft = true;
	}

	if (d->idPlayer == JOUEUR_D && (character->x < character2->x + d2->width)) {
		d->allowLeft   = false;
		d2->allowRight = false;
		d->left   = false;
		d2->right = false;

	} else {
		d->allowLeft   = true;
		d2->allowRight = true;
	}
}