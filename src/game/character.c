
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "../structure.h"
#include "character.h"
#include "movements.h"
#include "animations.h"
#include "fight.h"

void initFight(int idCharaLeft, int idCharaRight, int idMap) {
	setDisplayCodeWindow(FIGHT_SCREEN);


	char s[16] = "assets/map1.jpg";
	//s[10] = idMap+48;
	
	createImage(0, 0, LFEN,HFEN, s, FIGHT_SCREEN, 1);

	Element * characterL = NULL;
	Element * characterR = NULL;
	initCharacter(PLAYER_L, idCharaLeft, &characterL);
	initCharacter(PLAYER_R, idCharaRight, &characterR);


	/*Lie les deux personnages entre eux*/
	addElementToElement(characterL, characterR);
	addElementToElement(characterR, characterL);

	/*Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer*/
	setKeyPressedElement(characterL, keyOnActions);
	setKeyReleasedElement(characterL, keyOffActions);
	setActionElement(characterL, actionCharacters);

	/*Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer*/
	setKeyPressedElement(characterR, keyOnActions);
	setKeyReleasedElement(characterR, keyOffActions);
	setActionElement(characterR, actionCharacters);
}


void keyOnActions(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	/*Si on appuie sur une touche de déplacement*/
	if (k == kc->left || k == kc->right || k == kc->jump) {
		moveCharacterOn(character, k);
	}

	/*Si on appuie sur une touche d'attaque*/
	if (k == kc->attack1 || k == kc->attack2 || k == kc->parry) {
		launchCharacterAttack(character, k);
	}
}


void keyOffActions(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	KeyCodes_t * kc = d->keyCodes;

	/*Si on relache une touche de déplacement*/
	if (k == kc->left || k == kc->right || k == kc->jump) {
		moveCharacterOff(character, k);
	}
}


void actionCharacters(Element * character) {
	moveCharacter(character);
	jumpCharacter(character);
	collisionCharacters(character);
	charactersAnimation(character);
}


void initCharacter(int idPlayer, int idChara, Element ** character) {
	DataCharacter_t * d = initDataCharacter(idPlayer, idChara);
	double x = 0;
	double y = 0;
	char   filename[50];
	double groundLevel = HFEN-50-(d->height);

	if (!getCharactersFilename(idChara, filename)) {
		printf("Error fetching character's filename\n");
	} else {

		if (d != NULL) {

			if (idPlayer == PLAYER_L) {
				x = 100;
				y = groundLevel;
			} else { // PLAYER_R
				x = LFEN-100-(d->width);
				y = groundLevel;
			}

			(*character) = createImage(x, y, d->width, d->height, filename, FIGHT_SCREEN, 0);
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

	if (d != NULL && kc != NULL) {

		initKeyCodes(kc, idPlayer);
		d->keyCodes = kc;

		FILE * file = NULL;
		file = fopen("assets/stats/DataCharacters.txt", "r");

		if (file != NULL) {

			int idChara = -1;
			char line[6];

			d->idPlayer = idPlayer;

			d->left       = false;
			d->allowLeft  = false;
			d->right      = false;
			d->allowRight = false;
			d->jump       = false;
			d->allowJump  = true;
			d->crouch     = false;

			d->attack1      = false;
			d->allowAttack1 = true;
			d->attack2      = false;
			d->allowAttack2 = true;
			d->parry        = false;
			d->allowParry   = true;


			while (!feof(file) && idChara != idChosen) {
				fgets(line, 6, file);
				idChara = atoi(line);
			}
			d->idChara = idChara;

			fgets(line, 6, file);
			d->hp = atoi(line);

			fgets(line, 6, file);
			d->strength = atoi(line);

			fgets(line, 6, file);
			d->speed = atoi(line);

			fgets(line, 6, file);
			d->width = atoi(line);

			fgets(line, 6, file);
			d->height = atoi(line);

			fgets(line, 6, file);
			d->jumpForce = atoi(line);
			d->jumpForceTmp = d->jumpForce;

			fgets(line, 6, file);
			d->jumpLag = atoi(line);
		}

		fclose(file);
	}

	return d;
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

