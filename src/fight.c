
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "fight.h"
#include "character.h"


void initFight(int idCharacterG, int idCharacterD, ) {
	createImage(0,0,LFEN,HFEN,"assets/beach.jpg",0,PlanDecor);

	Element * character1 = NULL;
	Element * character2 = NULL;

	initCharacter(JOUEUR_G, character1);
	initCharacter(JOUEUR_D, character2);
}