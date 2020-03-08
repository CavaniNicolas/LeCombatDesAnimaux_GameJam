
#include <SANDAL2/SANDAL2.h>
#include <string.h>
#include "structure.h"
#include "title_screen.h"

#include "menu.h"

/******************* TITLE_SCREEN ***********************************/
// Init title_screen

void Launcher() {
	int  red[4]         = {255, 0, 0, 255};
	int  black[4]       = {0, 0, 0, 255};
	int  xTitle         = LFEN / 2 - 100;
	int  yTitle         = HFEN / 2;
	int  wTitle         = 500;
	int  hTitle         = 100;
	int  textSizeTitle  = 50;
	char font[100]      = "fonts/arial.ttf";
	char titleText[100] = "Le Combat Des Animaux";

	createImage(0, 0, LFEN, HFEN, "assets/fond.jpg", TITLE_SCREEN, PlanBackground);

	Element * title       = createText(xTitle, yTitle, wTitle, hTitle, textSizeTitle, font, titleText, red, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextMain);
	Element * titleShadow = createText(xTitle-2, yTitle+5, wTitle, hTitle, textSizeTitle, font, titleText, black, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextBack);
	addElementToElement(title, titleShadow);

	Element * curtainLeft  = createImage(0, 0, LFEN/2, HFEN, "assets/rideaugauche.png", TITLE_SCREEN, PlanCurtains);
	Element * curtainRight = createImage(LFEN/2, 0, LFEN/2, HFEN, "assets/rideaudroit.png", TITLE_SCREEN, PlanCurtains);

	setActionElement(curtainLeft, moveCurtainLeft);
	setActionElement(curtainRight, moveCurtainRight);
	setActionElement(title, zoomInTitle);
}

// Curtains

void moveCurtainLeft(Element * curtainLeft) {
	curtainLeft->x -= 5;
	if (curtainLeft->x < -LFEN) {
		clearPlanDisplayCode(TITLE_SCREEN, PlanCurtains);
		free(curtainLeft);
	}
}

void moveCurtainRight(Element * curtainRight) {
	curtainRight->x += 5;
	if (curtainRight->x > LFEN) {
		clearPlanDisplayCode(TITLE_SCREEN, PlanCurtains);
		free(curtainRight);
	}
}

// Title

void zoomInTitle(Element * title) {
	int speed    = 2;
	int yMaxZoom = LFEN/8-150;

	initIteratorElement(title);
	Element * titleShadow = nextIteratorElement(title);

	title->x      -= speed;
	title->y      -= speed;
	title->width  += speed;
	title->height += speed;

	titleShadow->x      -= speed;
	titleShadow->y      -= speed;
	titleShadow->width  += speed;
	titleShadow->height += speed;

	if (title->y < yMaxZoom) {
		title->events.action = NULL; // Stop moving
		displayStartButton();
	}
}

// Start

void displayStartButton() {
	int red[4]   = {255, 0, 0, 255};
	int xStart          = 2 * LFEN / 3 - 100;
	int yStart          = HFEN / 2 - 100;
	int wStart          = 350;
	int hStart          = 180;
	int textSizeStart   = 50;
	char font[50]       = "fonts/arial.ttf";
	char startText[100] = "Start";

	Element * start = createText(xStart, yStart, wStart, hStart, textSizeStart, font, startText, red, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextMain);
	
	DataStart * d = initDataStart();
	start->data = d;

	addClickableElement(start, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
	setOnClickElement(start, StartDown);
	setUnClickElement(start, StartUp);

	// pour les actions when hover : setOnMouseMotionElement()

}


DataStart * initDataStart() {
	DataStart * d = malloc(sizeof(DataStart));
	if (d) {
		d->verif = 0;
	}
	return d;
}

void StartDown(Element * start, int i) {
	(void) i;
	int green[4]        = {0,255,0,255};
	int xStart          = 2 * LFEN / 3 - 100;
	int yStart          = HFEN / 2 - 100;
	int wStart          = 350;
	int hStart          = 180;
	int textSizeStart   = 50;
	char font[100]      = "fonts/arial.ttf";
	char startText[100] = "Start";

	DataStart * d = start->data;
	if (!d->verif) {
		d->verif = 1;
		createText(xStart, yStart, wStart, hStart, textSizeStart, font, startText, green, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextFront);
	}
}

void StartUp(Element * start, int i) {
	(void) i;

	DataStart * d = start->data;
	d->verif = 0;

	clearPlanDisplayCode(TITLE_SCREEN, PlanTextFront);

	// free le texte

	initChoicePerso();
}
