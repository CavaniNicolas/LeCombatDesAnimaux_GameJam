
#include <SANDAL2/SANDAL2.h>
#include <string.h>
#include "structure.h"
#include "title_screen.h"

#include "champ_select.h"
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

	createImage(0, 0, LFEN, HFEN, "assets/fond.jpg", TITLE_SCREEN, PlanBackgroundTS);
	createImage(0, 0, LFEN, HFEN, "assets/map0.jpg", CHAMP_SELECT, PlanBackgroundCS);

	Element * start = initStartButton();
	DataStart * dStart = start->data;

	Element * title       = createText(xTitle, yTitle, wTitle, hTitle, textSizeTitle, font, titleText, red, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextMain);
	Element * titleShadow = createText(xTitle-2, yTitle+5, wTitle, hTitle, textSizeTitle, font, titleText, black, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextBack);
	addElementToElement(title, titleShadow);

	title->elementParent = start;

	Element * curtainLeft  = createImage(0, 0, LFEN/2, HFEN, "assets/rideaugauche.png", TITLE_SCREEN, PlanCurtains);
	Element * curtainRight = createImage(LFEN/2, 0, LFEN/2, HFEN, "assets/rideaudroit.png", TITLE_SCREEN, PlanCurtains);

	DataCurtain_t * curtainLeftData = (DataCurtain_t *)malloc(sizeof(DataCurtain_t));
	curtainLeftData->isClosed  = false;
	curtainLeftData->isMaxOpen = false;
	curtainLeftData->isFinished = false;
	DataCurtain_t * curtainRightData = (DataCurtain_t *)malloc(sizeof(DataCurtain_t));
	curtainRightData->isClosed  = false;
	curtainRightData->isMaxOpen = false;
	curtainRightData->isFinished = false;


	curtainLeft->data = curtainLeftData;
	curtainRight->data = curtainRightData;


	dStart->curtainLeft = curtainLeft;
	dStart->curtainRight = curtainRight;

	setActionElement(curtainLeft, moveLeftCurtainLeft);
	setActionElement(curtainRight, moveRightCurtainRight);
	setActionElement(title, zoomInTitle);

/*	if (curtainLeftData->isFinished == true && curtainRightData->isFinished == true) {
		ChampSelect();
	}*/
}

// Curtains

void moveLeftCurtainLeft(Element * curtainLeft) {
	DataCurtain_t * d = curtainLeft->data;
	if (d->isMaxOpen == false) {
		curtainLeft->x -= 5;
puts("blablou ?");
	}

	if (curtainLeft->x < -LFEN/2) {
		d->isMaxOpen = true;
		curtainLeft->events.action = NULL; // Stop moving
		//clearPlanDisplayCode(TITLE_SCREEN, PlanCurtains);
	}
}

void moveRightCurtainRight(Element * curtainRight) {
	DataCurtain_t * d = curtainRight->data;

	if (d->isMaxOpen == false) {
		curtainRight->x += 5;
	}

	if (curtainRight->x > LFEN) {
		d->isMaxOpen = true;
		curtainRight->events.action = NULL; // Stop moving
		//clearPlanDisplayCode(TITLE_SCREEN, PlanCurtains);
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
		setTextElement(title->elementParent, "Start");
	}
}

// Start

Element * initStartButton() {
	int red[4]          = {255, 0, 0, 255};
	int xStart          = 2 * LFEN / 3 - 100;
	int yStart          = HFEN / 2 - 100;
	int wStart          = 350;
	int hStart          = 180;
	int textSizeStart   = 50;
	char font[100]      = "fonts/arial.ttf";

	Element * start = createText(xStart, yStart, wStart, hStart, textSizeStart, font, " ", red, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextMain);

	if (start != NULL) {
		DataStart * d = initDataStart();
		
		if (d != NULL) {
			start->data = d;

			addClickableElement(start, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
			setOnClickElement(start, StartDown);
			setUnClickElement(start, StartUp);

			// pour les actions when hover : setOnMouseMotionElement()
		} else {
			free(start);
		}
	}

	return start;
}


DataStart * initDataStart() {
	DataStart * d = malloc(sizeof(DataStart));
	if (d) {
		d->isClicked = false;
	}
	return d;
}

void StartDown(Element * start, int i) {
	(void) i;
	int green[4]        = {0,255,0,255};

	DataStart * d = start->data;

	if (d->isClicked == false) {
		d->isClicked = true;
		setTextColorElement(start, green);
	
		setActionElement(d->curtainLeft, moveLeftCurtainRight);
		setActionElement(d->curtainRight, moveRightCurtainLeft);
	}
}



void StartUp(Element * start, int i) {
	(void) i;

	int coul[4] = {0,0,0,255};
	DataStart * d = start->data;
	d->isClicked = false;
printf("yolo\n");
	setTextColorElement(start, coul);


	//ChampSelect();
}

// transition


void moveLeftCurtainRight(Element * curtainLeft) {
	DataCurtain_t * d = curtainLeft->data;

	if (d->isClosed == false) {
		curtainLeft->x += 10;
	}

	if (curtainLeft->x >= 0) {
		d->isClosed = true;
		curtainLeft->events.action = NULL; // Stop moving
		setDisplayCodeWindow(CHAMP_SELECT);
		addDisplayCodeElement(curtainLeft, CHAMP_SELECT, PlanCurtains);
		puts("fermé");
	}

	if (d->isClosed == true) {
		d->isFinished = true;
		d->isClosed = false;
		d->isMaxOpen = false;
		setActionElement(curtainLeft, moveLeftCurtainLeft);
		puts("ALLO");
		//free(curtainLeft);
	}
}

void moveRightCurtainLeft(Element * curtainRight) {
	DataCurtain_t * d = curtainRight->data;

	if (d->isClosed == false) {
		curtainRight->x -= 10;
	}

	if (curtainRight->x <= LFEN/2) {
		d->isClosed = true;
		curtainRight->events.action = NULL; // Stop moving
		setDisplayCodeWindow(CHAMP_SELECT);
		addDisplayCodeElement(curtainRight, CHAMP_SELECT, PlanCurtains);
		puts("fermé");
	}

	if (d->isClosed == true) {
		d->isFinished = true;
		d->isClosed = false;
		d->isMaxOpen = false;
		setActionElement(curtainRight, moveRightCurtainRight);
		//ChampSelect();
		puts("ALLO");
		//free(curtainRight);
	}

}
