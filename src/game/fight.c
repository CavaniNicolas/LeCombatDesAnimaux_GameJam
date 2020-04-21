
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

	Element * characterL = NULL;
	Element * characterR = NULL;
	initCharacter(PLAYER_L, idCharaLeft, &characterL);
	initCharacter(PLAYER_R, idCharaRight, &characterR);


	// Lie les deux personnages entre eux
	addElementToElement(characterL, characterR);
	addElementToElement(characterR, characterL);


	// Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer
	setKeyPressedElement(characterL, keyPressed);
	setKeyReleasedElement(characterL, keyUnpressed);
	setActionElement(characterL, actionCharacters);

	// Fonctions à appeler lors de l'appuie / le relachement d'une touche / les actions à effectuer
	setKeyPressedElement(characterR, keyPressed);
	setKeyReleasedElement(characterR, keyUnpressed);
	setActionElement(characterR, actionCharacters);

}
