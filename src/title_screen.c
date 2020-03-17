
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

	double  wTitle         = LFEN * 0.3;
	double  hTitle         = 0.2 * wTitle;
	double  xTitle         = (LFEN / 2) - (wTitle / 2);
	double  yTitle         = (HFEN * 0.2) - (hTitle / 2);

	int  textSizeTitle  = 100;
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
	addElementToElement(curtainLeft, curtainRight);

	DataCurtain_t * curtainLeftData = (DataCurtain_t *)malloc(sizeof(DataCurtain_t));
	curtainLeftData->isClosed  = false;
	curtainLeftData->isMaxOpen = false;
	curtainLeftData->isFinished = false;

	curtainLeft->data = curtainLeftData;

	dStart->curtainLeft = curtainLeft;

	setActionElement(curtainLeft, openCurtains);

	setActionElement(title, zoomInTitle);

}

// Curtains

void openCurtains(Element * curtainLeft) {
	initIteratorElement(curtainLeft);
	Element * curtainRight = nextIteratorElement(curtainLeft);

	DataCurtain_t * d = curtainLeft->data;

	if (d->isMaxOpen == false) {
		curtainLeft->x -= 5;
		curtainRight->x += 5;
puts("opening Curtains");
	}

	if (curtainLeft->x < -LFEN/2) {
		d->isMaxOpen = true;
		curtainLeft->events.action = NULL; // Stop moving
	}

	if (d->isFinished == true && d->isMaxOpen == true) {
		clearPlanDisplayCode(CHAMP_SELECT, PlanCurtains);
		free(d);
		clearDisplayCode(TITLE_SCREEN);
	}
}


// Title

void zoomInTitle(Element * title) {
	initIteratorElement(title);
	Element * titleShadow = nextIteratorElement(title);

	double wTitle = title->width;

	double wMax = LFEN * 0.8;

	double wNew = wTitle + 4;
	double hNew = 0.2 * wNew;

	double xNew = (LFEN / 2) - (wNew / 2);
	double yNew = (HFEN * 0.2) - (hNew / 2);

	if (wNew >= wMax) {
		title->events.action = NULL; // Stop moving
		setTextElement(title->elementParent, "Start");
	}

	if (wNew < wMax) {
		title->width = wNew;
		title->x = xNew;
		titleShadow->width = wNew;
		titleShadow->x = xNew - 2;

		title->height = hNew;
		title->y = yNew;
		titleShadow->height = hNew;
		titleShadow->y = yNew + 5;
	}
}

// Start

Element * initStartButton() {
	int red[4]        = {255, 0, 0, 255};

	double wStart     = LFEN * 0.4;
	double hStart     = 0.4 * wStart;
	double xStart     = (LFEN / 2) - (wStart / 4);
	double yStart     = (HFEN * 0.6) - (hStart / 2);

	int textSizeStart = 100;
	char font[100]    = "fonts/arial.ttf";

	Element * start = createText(xStart, yStart, wStart, hStart, textSizeStart, font, " ", red, SANDAL2_BLENDED, TITLE_SCREEN, PlanTextMain);

	if (start != NULL) {
		DataStart * d = initDataStart();
		
		if (d != NULL) {
			start->data = d;

			addClickableElement(start, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
			setOnClickElement(start, StartDown);
			setUnClickElement(start, StartUp);

			setOnMouseMotionElement(start, hoverOnStartButton);
			setUnMouseMotionElement(start, hoverOffStartButton);
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
		d->allowClick = true;
		d->curtainLeft = NULL;
	}
	return d;
}

void StartDown(Element * start, int i) {
	(void) i;
	int green[4]        = {0, 255, 0, 255};

	DataStart * d = start->data;

	if (d->isClicked == false && d->allowClick == true) {
		d->isClicked = true;
		setTextColorElement(start, green);
	
		setActionElement(d->curtainLeft, closeCurtains);
	}
}

void StartUp(Element * start, int i) {
	(void) i;

	int red[4] = {255,0,0,255};

	DataStart * d = start->data;
	
	if (d->allowClick == true) {
		d->allowClick = false;
		setTextColorElement(start, red);
	}
}

// Hover on Start Button
void hoverOnStartButton(Element * start) {
	int orange[4] = {255, 150, 0, 255};

	DataStart * d = start->data;
	if (d->isClicked == false) {
		setTextColorElement(start, orange);
	}
}

// Hover Off Start Button
void hoverOffStartButton(Element * start) {
	int red[4] = {255, 0, 0, 255};

	DataStart * d = start->data;
	if (d->isClicked == false) {
		setTextColorElement(start, red);
	}
}


// transition

void closeCurtains(Element * curtainLeft) {
	DataCurtain_t * d = curtainLeft->data;
	initIteratorElement(curtainLeft);
	Element * curtainRight = nextIteratorElement(curtainLeft);

	if (d->isClosed == false) {
		curtainLeft->x += 10;
		curtainRight->x -= 10;
	}

	if (curtainLeft->x >= 0) {
		d->isClosed = true;

		addDisplayCodeElement(curtainLeft, CHAMP_SELECT, PlanCurtains);
		addDisplayCodeElement(curtainRight, CHAMP_SELECT, PlanCurtains);
		setDisplayCodeWindow(CHAMP_SELECT);
		puts("fermé");
	}

	if (d->isClosed == true) {
		d->isFinished = true;
		d->isClosed = false;
		d->isMaxOpen = false;
		setActionElement(curtainLeft, openCurtains);
		puts("ALLO");
		//free(curtainLeft);
	}

	if (d->isFinished == true) {
		ChampSelect();
	}
}

