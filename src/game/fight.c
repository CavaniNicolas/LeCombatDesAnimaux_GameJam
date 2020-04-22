
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "animations.h"
#include "movements.h"
#include "fight.h"


void initFight(int idCharaLeft, int idCharaRight, int idMap) {
	setDisplayCodeWindow(FIGHT_SCREEN);


	char s[16] = "assets/map1.jpg";
	(void) idMap;
	//s[10] = idMap+48;
	
	createImage(0, 0, LFEN,HFEN, s, FIGHT_SCREEN, PlanBackgroundF);

	Element * characterL = NULL;
	Element * characterR = NULL;
	initCharacter(PLAYER_L, idCharaLeft, &characterL);
	initCharacter(PLAYER_R, idCharaRight, &characterR);


	// Lie les deux personnages entre eux
	addElementToElement(characterL, characterR);
	addElementToElement(characterR, characterL);

	// Init la structure commune et l'insere dans les DataCharacter_t
	initCommonData(characterL);

	// Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer
	setKeyPressedElement(characterL, keyPressed);
	setKeyReleasedElement(characterL, keyUnpressed);
	setActionElement(characterL, actionCharacters);

	// Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer
	setKeyPressedElement(characterR, keyPressed);
	setKeyReleasedElement(characterR, keyUnpressed);
	setActionElement(characterR, actionCharacters);

}


void endRound(Element * characterLost) {
	initIteratorElement(characterLost);
	Element * characterWin = nextIteratorElement(characterLost);

	DataCharacter_t * d = characterLost->data;
	DataCharacter_t * d2 = characterWin->data;

	DataCommon_t * dc = d->dataCommon;

	if (d->dyingReviving) {
		dc->allowAll = false;
		d2->winNum += 1;
		setActionElement(characterLost, actionRoundTransitions);
		setActionElement(characterWin, actionRoundTransitions);

	}

}


void actionRoundTransitions(Element * character) {
	toggleAllowMovements(character);
	moveCharacter(character);
	charactersAnimation(character);
	waitDeath(character);
}


void waitDeath(Element * character) {
	DataCharacter_t * d = character->data;
	DataCommon_t * dc = d->dataCommon;

	if (d->dead == true) {
		if ((int)SDL_GetTicks() - dc->deadTimer >= dc->deadTimerCte) {
			d->dead = false;
			d->hp = d->hpCte;

			printf("getTicks %d, deadTimer %d, deadTimerCte %d\n", (int)SDL_GetTicks(), dc->deadTimer, dc->deadTimerCte);
			puts("lets Revive Soon");
		}
	}
}


void toggleAllowMovements(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	DataCommon_t * dc = d->dataCommon;

	if (dc->allowAll == false) {
		d->allowLeft = false;
		d->allowRight = false;
		d->allowJump = false;
		d->allowAttacks = false;
		d->left = false;
		d->right = false;

		d2->allowLeft = false;
		d2->allowRight = false;
		d2->allowJump = false;
		d2->allowAttacks = false;
		d2->left = false;
		d2->right = false;

	} else {
		d->allowLeft = true;
		d->allowRight = true;
		d->allowJump = true;
		d->allowAttacks = true;

		d2->allowLeft = true;
		d2->allowRight = true;
		d2->allowJump = true;
		d2->allowAttacks = true;

		setActionElement(character, actionCharacters);
		setActionElement(character2, actionCharacters);
	}
}
