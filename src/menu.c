
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "menu.h"

// init

void Launcher() {
	int red[4] = {255,0,0,255};
	int green[4] = {0,255,0,255};
	createImage(0,0,LFEN,HFEN,"assets/beach.jpg",ECRAN_TITRE,PlanDecor);

	Element * titre = createText(LFEN/2,HFEN/2,300,50,50,"fonts/arial.ttf","Nom du jeu",red,SANDAL2_BLENDED,ECRAN_TITRE,PlanTitre);
	Element * r1 = createBlock(0,0,LFEN/2,HFEN,green,ECRAN_TITRE,PlanRideau);
	Element * r2 = createBlock(LFEN/2,0,LFEN/2,HFEN,green,ECRAN_TITRE,PlanRideau);

	setActionElement(r1,depRideau1);
	setActionElement(r2,depRideau2);
	setActionElement(titre,aggrandissement);
}

// rideau

void depRideau1(Element * r1) {
	r1->x -= 5;
	if(r1->x < -LFEN) delElement(r1);
}

void depRideau2(Element * r2) {
	r2->x += 5;
	if(r2->x > 2*LFEN) delElement(r2);
}

// titre

void aggrandissement(Element * titre) {
	int red[4] = {255,0,0,255};
	int vitesse = 2;
	titre->x -= vitesse;
	titre->y -= vitesse;
	titre->width += vitesse;
	titre->height += vitesse;

	if(titre->y < HFEN/6) {
		titre->events.action = NULL;
		Element * start = createText(2*LFEN/3,HFEN/2+100,200,100,50,"fonts/arial.ttf","Start",red,SANDAL2_BLENDED,ECRAN_TITRE,PlanStartUp);
		DataStart * d = initDataStart();
		start->data = d;
		addClickableElement(start,rectangleClickable(0.f,0.f,1.f,1.f),0);
		setOnClickElement(start,StartDown);
		setUnClickElement(start,StartUp);
	}
}

// start

DataStart * initDataStart() {
	DataStart * d = malloc(sizeof(DataStart));
	if(d){
		d->verif = 0;
	}

	return d;
}

void StartDown(Element * start, int i) {
	(void) i;
	int green[4] = {0,255,0,255};
	DataStart * d = start->data;
	if(!d->verif) {
		d->verif = 1;
		createText(2*LFEN/3,HFEN/2+100,200,100,50,"fonts/arial.ttf","Start",green,SANDAL2_BLENDED,ECRAN_TITRE,PlanStartDown);
	}
}

void StartUp(Element * start, int i) {
	(void) i;
	DataStart * d = start->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_TITRE,PlanStartDown);
}
