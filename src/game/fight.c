
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "animations.h"
#include "movements.h"
#include "attacks.h"
#include "fight.h"
#include "restart.h"


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

		showVictory(characterWin);

		setActionElement(characterLost, actionRoundTransitions);
		setActionElement(characterWin, actionRoundTransitions);
		d->left = false;
		d->right = false;
		d2->left = false;
		d2->right = false;
	}

}


void actionRoundTransitions(Element * character) {
	toggleAllowMovements(character);
	moveCharacter(character);
	charactersAnimation(character);
	resurrect(character);
	adaptHealthBar(character);
	resetHealthBar(character);
	resetPosition(character);
	isGameFinished(character);
}


void resurrect(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;
	DataCommon_t * dc = d->dataCommon;

	if (d->dead == true) {
		dc->resetHPBar = true;

		// attente
		if ((int)SDL_GetTicks() - dc->deadTimer >= dc->deadTimerCte) {
			d->dead = false;
			d->hp = d->hpCte;
			d2->hp = d2->hpCte;

			printf("getTicks %d, deadTimer %d, deadTimerCte %d\n", (int)SDL_GetTicks(), dc->deadTimer, dc->deadTimerCte);
			puts("lets Revive Soon");
		}
	}
}


void resetHealthBar(Element * character) {
	DataCharacter_t * d = character->data;
	HealthBar_t * hb = d->healthBar;
	DataCommon_t * dc = d->dataCommon;

	int addW = 2;
	if (dc->resetHPBar == true) {

		if (hb->healthBar->width <= hb->wBarMax - addW) {
			hb->healthBar->width += addW;
			hb->damageBar->width = hb->healthBar->width;

		} else if (hb->healthBar->width != hb->wBarMax) {
			addW = 1;
		}
	}
}


void resetPosition(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;
	DataCommon_t * dc = d->dataCommon;

	if (dc->resetPos == true) {

		// if (character->x > d->xInit - 1 && character->x < d->xInit + 1) {
		// 	d->right = false;
		// 	d->right = false;
		// 	d->isPosReset = true;

		// } else {

		if (character->x < d->xInit) {
			d->right = true;
			d->left = false;

		} else if (character->x > d->xInit) {
			d->left = true;
			d->right = false;

		} else {
			d->right = false;
			d->right = false;
			d->isPosReset = true;
		}
//}
	}

	if (d->isPosReset == true && d2->isPosReset == true) {
		dc->resetPos = false;

		if (dc->endGame == true) {
			restartGameScreen(character);

		} else {
			d->isPosReset = false;
			d2->isPosReset = false;
			dc->allowAll = true;
		}

		printf("hp0 : %d/%d, hp1 : %d/%d\n", d->hp, d->hpCte, d2->hp, d2->hpCte);
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

		d2->allowLeft = false;
		d2->allowRight = false;
		d2->allowJump = false;
		d2->allowAttacks = false;

	} else {
		setActionElement(character, actionCharacters);
		setActionElement(character2, actionCharacters);
		d->allowLeft = true;
		d->allowRight = true;
		d->allowJump = true;
		d->allowAttacks = true;

		d2->allowLeft = true;
		d2->allowRight = true;
		d2->allowJump = true;
		d2->allowAttacks = true;

		dc->resetHPBar = false;
		dc->resetPos = false;
	}
}


void showVictory(Element * characterWin) {
	DataCharacter_t * d = characterWin->data;
	HealthBar_t * hb = d->healthBar;

	int orange[4] = {255, 100, 0, 255};

	int x = 0;
	int y = hb->bubble1->y;
	int sideBubble = hb->bubble1->width;
	int marge = 0.1 * sideBubble;

	if (d->winNum == 1) {
		x = hb->bubble1->x;
	} else if (d->winNum == 2) {
		x = hb->bubble2->x;
	}

	createBlock(x+marge, y+marge, sideBubble-2*marge, sideBubble-2*marge, orange, FIGHT_SCREEN, PlanHealthBars-2);

}

