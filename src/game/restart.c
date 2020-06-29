
#include <SANDAL2/SANDAL2.h>
#include "../structure.h"
#include "restart.h"
#include "fight.h"
#include "../menu/champ_select.h"


void isGameFinished(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	DataCommon_t * dc = d->dataCommon;

	if (d->winNum == 2 || d2->winNum == 2) {
		dc->endGame = true;
	}

	if (dc->restartChoice != None) {
		restartActions(character);
	}
}


void restartGameScreen(Element * character) {
	DataCharacter_t * d = character->data;
	DataCommon_t * dc = d->dataCommon;

	int white[4] = {255, 255, 255, 255};
	int blue[4] = {0, 0, 255, 255};
	int green[4] = {0, 255, 0, 255};

	int width = 0.2 * LFEN;
	int height = 0.1 * HFEN;

	int middleW = 0.5 * LFEN;
	int middleH = 0.5 * HFEN;

	int x = middleW - (width / 2);

	Element * again = createBlock(x, middleH-(2*height), width, height, white, FIGHT_SCREEN, PlanRestartButtons); // Again
	Element * restart = createBlock(x, middleH-(height/2), width, height, blue, FIGHT_SCREEN, PlanRestartButtons); // Restart
	Element * quit = createBlock(x, middleH+height, width, height, green, FIGHT_SCREEN, PlanRestartButtons); // Quit

	again->data = dc;
	restart->data = dc;
	quit->data = dc;

	addClickableElement(again, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
	addClickableElement(restart, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
	addClickableElement(quit, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);

	setOnClickElement(again, choiceClicked);
	setOnClickElement(restart, choiceClicked);
	setOnClickElement(quit, choiceClicked);

}


void choiceClicked(Element * box, int i) {
	(void) i;

	DataCommon_t * dc = box->data;

	int middleH = 0.5 * HFEN;;

	if (dc->restartChoice == None) {

		if (box->y < middleH-(box->height/2)) {
			dc->restartChoice = Again;
		} else if (box->y > middleH) {
			dc->restartChoice = Quit;
		} else {
			dc->restartChoice = Restart;
		}
	}

}


void restartActions(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	DataCommon_t * dc = d->dataCommon;

	clearPlanDisplayCode(FIGHT_SCREEN, PlanRestartButtons);
	clearPlanDisplayCode(FIGHT_SCREEN, PlanHealthBars-2);
	// removeWinBubbles();

	switch (dc->restartChoice) {

		case Again:
			d->winNum = 0;
			d2->winNum = 0;
			dc->endGame = false;

			dc->restartChoice = None;
			break;

		case Restart:
			dc->restartChoice = None;
			freeCharacter(character);
			ChampSelect();
			break;

		case Quit:
			freeCharacter(character);
			closeAllWindow();
			closeAllSANDAL2();
			break;

	}
}

void freeCharacter(Element * character) {
	initIteratorElement(character);
	Element * character2 = nextIteratorElement(character);

	DataCharacter_t * d = character->data;
	DataCharacter_t * d2 = character2->data;

	free(d->dataCommon);

	free(d->keyPressed);
	free(d->healthBar);
	free(d->keyCodes);
	free(d);
	free(character);

	free(d2->keyPressed);
	free(d2->healthBar);
	free(d2->keyCodes);
	free(d2);
	free(character2);
}