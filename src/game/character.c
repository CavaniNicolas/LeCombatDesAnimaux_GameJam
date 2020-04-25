
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "../structure.h"
#include "fight.h"
#include "character.h"
#include "animations.h"
#include "movements.h"
#include "attacks.h"


void keyPressed(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;
	KeyPressed_t * kp = d->keyPressed;

	/*Si on appuie sur une touche d'attaque*/
	if (k == kc->attack1) {
		kp->attack1_P = true;
	}
	if (k == kc->attack2) {
		kp->attack2_P = true;
	}
	if (k == kc->parry) {
		kp->parry_P = true;
	}

	/*Si on appuie sur une touche de déplacement*/
	if (k == kc->left) {
		kp->left_P = true;
	}
	if (k == kc->right) {
		kp->right_P = true;
	}
	if (k == kc->jump) {
		kp->jump_P = true;
	}
}


void keyUnpressed(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;
	KeyPressed_t * kp = d->keyPressed;

	/*Si on relache une touche d'attaque*/
	if (k == kc->attack1) {
		kp->attack1_P = false;
	}
	if (k == kc->attack2) {
		kp->attack2_P = false;
	}
	if (k == kc->parry) {
		kp->parry_P = false;
	}

	/*Si on relache une touche de déplacement*/
	if (k == kc->left) {
		kp->left_P = false;
	}
	if (k == kc->right) {
		kp->right_P = false;
	}
	if (k == kc->jump) {
		kp->jump_P = false;
	}
}


void keyOnActions(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	/*Si on appuie sur une touche d'attaque*/
	if (kp->attack1_P || kp->attack2_P || kp->parry_P) {
		launchCharacterAttack(character);
	}

	/*Si on appuie sur une touche de déplacement*/
	else if (kp->left_P || kp->right_P || kp->jump_P) {
		moveCharacterOn(character);
	}

}


void keyOffActions(Element * character) {
	DataCharacter_t * d = character->data;
	KeyPressed_t * kp = d->keyPressed;

	//Si on relache une touche de déplacement
	if (kp->left_P == false || kp->right_P == false) {
		moveCharacterOff(character);
	}
}


void actionCharacters(Element * character) {
	moveCharacter(character);
	jumpCharacter(character);
	collisionCharacters(character);
	charactersAnimation(character);
	keyOnActions(character);
	keyOffActions(character);
	adaptHealthBar(character);
}


void initCharacter(int idPlayer, int idChara, Element ** character) {
	DataCharacter_t * d = initDataCharacter(idPlayer, idChara);
	char   filename[50];

	if (!getCharactersFilename(idChara, filename)) {
		printf("Error fetching character's filename\n");
	} else {

		if (d != NULL) {

			(*character) = createImage(d->xInit, d->yInit, d->width, d->height, filename, FIGHT_SCREEN, PlanCharacters);
			createCharacterAnimations(*character);

			if (idPlayer == PLAYER_R) {
				(*character)->flip = SANDAL2_FLIP_HOR;
			}

			(*character)->data = d;
		}
	}
}


DataCharacter_t * initDataCharacter(int idPlayer, int idChosen) {
	DataCharacter_t * d = (DataCharacter_t *)malloc(sizeof(DataCharacter_t));
	KeyCodes_t * kc = (KeyCodes_t *)malloc(sizeof(KeyCodes_t));
	HealthBar_t * hb = (HealthBar_t *)malloc(sizeof(HealthBar_t));
	KeyPressed_t * kp = (KeyPressed_t *)malloc(sizeof(KeyPressed_t));
	FILE * file = fopen("assets/stats/DataCharacters.txt", "r");

	int groundLevel = 0;

	if (d != NULL && kc != NULL && kp != NULL && hb != NULL && file != NULL) {

		initKeyCodes(kc, idPlayer);
		d->keyCodes = kc;

		d->winNum = 0;
		initHealthBar(hb, idPlayer);
		d->healthBar = hb;

		initKeyPressed(kp);
		d->keyPressed = kp;


		getStatsInFile(file, d, idChosen);

		d->idPlayer = idPlayer;

		groundLevel = HFEN - 50 - (d->height);
		if (idPlayer == PLAYER_L) {
			d->xInit = 0.1*LFEN;
		} else { // PLAYER_R
			d->xInit = LFEN - 0.1*LFEN - (d->width);
		}
		d->yInit = groundLevel;

		d->left         = false;
		d->allowLeft    = false;
		d->right        = false;
		d->allowRight   = false;
		d->jump         = false;
		d->allowJump    = true;
		d->crouch       = false;

		d->attacks      = false;
		d->allowAttacks = true;

		d->attack1      = false;
		d->attack2      = false;
		d->parry        = false;

		d->inRange      = false;

		d->dyingReviving = false;
		d->dieReviveBeg  = false;
		d->dead          = false;

	} else {
		free(d);
		free(kc);
		free(kp);
		free(hb);
	}

	fclose(file);
	return d;
}


void initCommonData(Element * characterL) {
	initIteratorElement(characterL);
	Element * characterR = nextIteratorElement(characterL);

	DataCharacter_t * d = characterL->data;
	DataCharacter_t * d2 = characterR->data;

	DataCommon_t * dc = (DataCommon_t *)malloc(sizeof(DataCommon_t));

	if (dc != NULL) {
		dc->allowAll = true;
		dc->deadTimerCte = 2000;
		dc->deadTimer = 0;
		dc->resetHPBar = false;
		dc->resetPos = false;

		d->dataCommon = dc;
		d2->dataCommon = dc;

	} /*else {
		freeAllData(characterL);
	}*/
}


void getStatsInFile(FILE * file, DataCharacter_t * d, int idChosen) {
	int idChara = -1;
	char line[6];

	while (!feof(file) && idChara != idChosen) {
		fgets(line, 6, file);
		idChara = atoi(line);
	}
	d->idChara = idChara;

	fgets(line, 6, file);
	d->hpCte = atoi(line);
	d->hp = d->hpCte;
//printf("hp %d\n", d->hp);

	fgets(line, 6, file);
	d->strengthCte = atoi(line);
	d->strength = d->strengthCte;
//printf("strength %d\n", d->strengthCte);

	fgets(line, 6, file);
	d->speedCte = atoi(line);
	d->speed = d->speedCte;
//printf("speed %d\n", d->speed);

	fgets(line, 6, file);
	d->height = (HFEN * atof(line));
//printf("height %d\n", d->height);

	fgets(line, 6, file);
	d->width = (d->height * atof(line));
//printf("width %d\n", d->width);

	fgets(line, 6, file);
	d->hitboxSize = (d->width * atof(line) / 100);
//printf("hitbox %d\n", d->hitboxSize);

	fgets(line, 6, file);
	d->jumpForceCte = atoi(line);
	d->jumpForceTmp = d->jumpForceCte;
//printf("jumpForce %d\n", d->jumpForceCte);

	fgets(line, 6, file);
	d->jumpLagCte = atoi(line);
//printf("jumpLag %d\n", d->jumpLagCte);
}


void initKeyCodes(KeyCodes_t * kc, int idPlayer) {

	if (idPlayer == PLAYER_L) {
		kc->left    = 'a';
		kc->right   = 'e';
		kc->jump    = 'z';
		kc->attack1 = 's';
		kc->attack2 = 'f';
		kc->parry   = 'd';

	} else { //idPlayer == PLAYER_R
		kc->left    = 'y';
		kc->right   = 'i';
		kc->jump    = 'u';
		kc->attack1 = 'j';
		kc->attack2 = 'l';
		kc->parry   = 'k';
	}
}


void initKeyPressed(KeyPressed_t * kp) {
	kp->left_P    = false;
	kp->right_P   = false;
	kp->jump_P    = false;
	kp->attack1_P = false;
	kp->parry_P   = false;
	kp->attack2_P = false;
}


void initHealthBar(HealthBar_t * hb, int idPlayer) {
	int white[4] = {255, 255, 255, 255};
	int red[4] = {255, 0, 0, 255};
	int darkRed[4] = {120, 15, 0, 255};
	//int orange[4] = {255, 100, 0, 255};
	int blue[4] = {0, 0, 255, 255};

	char filename[40] = "assets/characters/logos/logo0.png";

	int marge = 0.05 * LFEN;
	int yBar = marge/2;
	int xBarRight = LFEN / 2 + marge;
	int wBar = 0.4 * LFEN;
	int hBar = 0.05 * HFEN;

	int sideBubble = 0.8*hBar;
	int yBubble = yBar+hBar+1;

	Element * healthBar = NULL;
	Element * damageBar = NULL;
	Element * bubble1 = NULL;
	Element * bubble2 = NULL;

	if (idPlayer == PLAYER_L) { //Left
		createBlock(marge, yBar, wBar, hBar, white, FIGHT_SCREEN, PlanHealthBars); // Contour blanc du block Left
		healthBar = createBlock(marge+2, yBar+2, wBar-4, hBar-4, red, FIGHT_SCREEN, PlanHealthBars-5); // contenu rouge du block Left
		damageBar = createBlock(marge+2, yBar+2, wBar-4, hBar-4, darkRed, FIGHT_SCREEN, PlanHealthBars-4); // contenu rouge foncé du block Left

		//createBlock(marge-hBar, yBar, hBar, hBar, orange, FIGHT_SCREEN, PlanHealthBars-1); //Logo Perso Left
		createImage(marge-hBar, yBar, hBar, hBar, filename, FIGHT_SCREEN, PlanHealthBars-1); //Logo Perso Left

		bubble1 = createBlock(marge+wBar-2.5*sideBubble, yBubble, sideBubble, sideBubble, blue, FIGHT_SCREEN, PlanHealthBars-1); //Bubble1Left du BO3
		bubble2 = createBlock(marge+wBar-sideBubble, yBubble, sideBubble, sideBubble, blue, FIGHT_SCREEN, PlanHealthBars-1); //Bubble2Left du BO3

	} else { //Right
		createBlock(xBarRight, yBar, wBar, hBar, white, FIGHT_SCREEN, PlanHealthBars); // Contour blanc du block Right
		healthBar = createBlock(xBarRight+2, yBar+2, wBar-4, hBar-4, red, FIGHT_SCREEN, PlanHealthBars-5); // contenu rouge du block Right
		damageBar = createBlock(xBarRight+2, yBar+2, wBar-4, hBar-4, darkRed, FIGHT_SCREEN, PlanHealthBars-4); // contenu rouge du block Right

		//createBlock(xBarRight+wBar, yBar, hBar, hBar, orange, FIGHT_SCREEN, PlanHealthBars-1); //Logo Perso Right
		Element * logoRight = createImage(xBarRight+wBar, yBar, hBar, hBar, filename, FIGHT_SCREEN, PlanHealthBars-1); //Logo Perso Right
		logoRight->flip = SANDAL2_FLIP_HOR;

		bubble1 = createBlock(xBarRight, yBubble, sideBubble, sideBubble, blue, FIGHT_SCREEN, PlanHealthBars-1); //Bubble1Right du BO3
		bubble2 = createBlock(xBarRight+1.5*sideBubble, yBubble, sideBubble, sideBubble, blue, FIGHT_SCREEN, PlanHealthBars-1); //Bubble2Right du BO3
	}

	if (healthBar != NULL && bubble1 != NULL && bubble2 != NULL) {
		hb->wBarMax = wBar-4;
		hb->healthBar = healthBar;
		hb->damageBar = damageBar;
		hb->bubble1 = bubble1;
		hb->bubble2 = bubble2;
	}
}


int getCharactersFilename(int idChara, char filename[50]) {
	int error = 1;
	DIR * rep = opendir("./assets/sprites");
	char filenameTmp[30] = "s_.png";

	if (rep != NULL) {
		struct dirent * ent = NULL;

		while ((ent = readdir(rep)) != NULL) {
			if (ent->d_name[1] - 48 == idChara) {
				strcpy(filenameTmp, ent->d_name);
			}
		}

		if (filenameTmp[1] == '_') {
			error = 0;
		}

		snprintf(filename, 50, "./assets/sprites/%s", filenameTmp);

		closedir(rep);
	} else {
		error = 0;
	}
	return error;
}

