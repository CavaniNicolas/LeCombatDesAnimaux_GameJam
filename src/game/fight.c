
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "character.h"
#include "fight.h"


void initFight(int idCharaLeft, int idCharaRight, int idMap) {
	setDisplayCodeWindow(FIGHT_SCREEN);


	char s[16] = "assets/map1.jpg";
	(void) idMap;
	//s[10] = idMap+48;
	
	createImage(0, 0, LFEN,HFEN, s, FIGHT_SCREEN, PlanBackgroundF);

	initHealthBars();
		updateWindow();
		displayWindow();
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


void initHealthBars() {
	int white[4] = {255, 255, 255, 255};

	int marge = 0.05 * LFEN;
	int xBarRight = LFEN / 2 + marge;
	int wBar = 0.4 * LFEN;
	int hBar = 0.05 * HFEN;

	createBlock(marge, marge/2, wBar, hBar, white, FIGHT_SCREEN, PlanHealthBars); // Contour blanc du block
	createBlock(xBarRight, marge/2, wBar, hBar, white, FIGHT_SCREEN, PlanHealthBars); // Contour blanc du block
}


