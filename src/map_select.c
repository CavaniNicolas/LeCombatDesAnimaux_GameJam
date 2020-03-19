
#include <SANDAL2/SANDAL2.h>
#include <string.h>
#include "structure.h"
#include "optimiseDisplay.h"
#include "map_select.h"

#include "fight.h"



void MapSelect() {
	setDisplayCodeWindow(MAP_SELECT);

	generateMapSelectDisplays();
}


void generateMapSelectDisplays() {

	int white[4] = {255, 255, 255, 255};
	int black[4] = {0, 0, 0, 255};

	createImage(0, 0, LFEN, HFEN, "assets/map1.jpg", MAP_SELECT, PlanBackgroundMS);

	int xmarge = 0.1 * LFEN;
	int ymarge = 0.1 * HFEN;
	int wMapBlock = 0.8 * LFEN;
	int hMapBlock = 0.8 * HFEN;

	int nbMap = 3; float fillPercent = 0.8; int nbLines = 0; int nbColumns = 0; int sizeSideIm = 0;
	setOptimizedLinesAndColumns(wMapBlock, hMapBlock, nbMap, fillPercent, &nbLines, &nbColumns, &sizeSideIm);

	int xInterObjSpace = spaceBetweenObjects(nbColumns, sizeSideIm, wMapBlock);
	int yInterObjSpace = spaceBetweenObjects(nbLines, sizeSideIm, hMapBlock);

	createBlock(xmarge, ymarge, wMapBlock, hMapBlock, black, MAP_SELECT, PlanMapLogoBackground);

	int xIm = xInterObjSpace; int yIm = yInterObjSpace; 
	int numLine = 1; int numColumn = 1;
	for (int i=0; i<nbMap; i++) {
		createBlock(xmarge + xIm, ymarge + yIm, sizeSideIm, sizeSideIm, white, MAP_SELECT, PlanMapLogo);
		newOptimisedXY(&xIm, &yIm, &numLine, &numColumn, nbLines, nbColumns, sizeSideIm, xInterObjSpace, yInterObjSpace);
	}

}

/*
void initChoiceMap(int indiceJoueur, int indiceJoueur2, Element * validerPerso) {
	int white[4] = {255,255,255,255};
	int red[4] = {255,0,0,255};
	int largeurMap = HFEN/5;
	int ecartMap = (LFEN-NBMAP*largeurMap)/(NBMAP+1);
	Element * Map = NULL;
	char s[14] = "assets/m9.png";
	createImage(0,0,LFEN,HFEN,"assets/fond.jpg",ECRAN_CHOIX_MAP,PlanDecor);
	createText(LFEN/2-200,HFEN/30,400,150,50,"fonts/arial.ttf","Choix de la map",white,SANDAL2_BLENDED,ECRAN_CHOIX_MAP,PlanTitre);
	Element * retour = createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_MAP,PlanBtnRetourUp);
	DataRetour * d = initDataRetour();
	retour->data = d;
	addClickableElement(retour,rectangleClickable(0.f,0.f,1.f,1.f),0);
	setOnClickElement(retour,RetourDown2);
	setUnClickElement(retour,RetourUp2);
	addElementToElement(retour,validerPerso);
	Element * valider = createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_MAP,PlanBtnValiderUp);
	DataValidate2 * d2 = initDataValidate2(indiceJoueur, indiceJoueur2);
	valider->data = d2;
	addClickableElement(valider,rectangleClickable(0.f,0.f,1.f,1.f),0);
	setOnClickElement(valider,ValiderDown2);
	setUnClickElement(valider,ValiderUp2);
	for(int i = 0; i < NBMAP; i ++) {
		if(!i) Map = createImage(ecartMap+i*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,"assets/m1.png",ECRAN_CHOIX_MAP,PlanMapDown);
		s[8] = i*2+48;
		Map = createImage(ecartMap+i*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,s,ECRAN_CHOIX_MAP,PlanMapUp);
		addElementToElement(valider,Map);
		addElementToElement(Map,valider);
		DataMap * d3 = initDataMap(i);
		Map->data = d3;
		addClickableElement(Map,rectangleClickable(0.f,0.f,1.f,1.f),0);
		setOnClickElement(Map,MapDown);
		setUnClickElement(Map,MapUp);
	}
}

void RetourDown2(Element * retour, int i) {
	(void) i;
	int green[4] = {0,255,0,255};
	int white[4] = {255,255,255,255};
	DataRetour * d = retour->data;
	if(!d->verif) {
		d->verif = 1;
		createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,green,ECRAN_CHOIX_MAP,PlanBtnRetourDown);
	}
}

void RetourUp2(Element * retour, int i) {
	(void) i;
	DataRetour * d = retour->data;
	int white[4] = {255,255,255,255};
	initIteratorElement(retour);
	Element * valider = nextIteratorElement(retour);
	DataValidate * d2 = valider->data;
	d2->indiceJoueur = JOUEUR_G;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanBtnRetourDown);
	setDisplayCodeWindow(ECRAN_CHOIX_PERSO);
	int titrePosY = HFEN/30;
	int titreHeight = 150;
	clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanTitre);
	createText(LFEN/8,titrePosY,400,titreHeight,50,"fonts/arial.ttf","Choix du perso J1",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanTitre);
}

DataValidate2 * initDataValidate2(int indiceJoueur, int indiceJoueur2) {
	DataValidate2 * d = malloc(sizeof(DataValidate2));
	if(d){
		d->verif = 0;
		d->indiceJoueur = indiceJoueur;
		d->indiceJoueur2 = indiceJoueur2;
	}

	return d;
}

void ValiderDown2(Element * valider, int i) {
	(void) i;
	int green[4] = {0,255,0,255};
	int white[4] = {255,255,255,255};
	DataValidate2 * d = valider->data;
	if(!d->verif) {
		d->verif = 1;
		createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,green,ECRAN_CHOIX_MAP,PlanBtnValiderUp);
		printf("player 1 = %d\n", d->indiceJoueur);
		printf("player 2 = %d\n", d->indiceJoueur2);
		printf("map choisie = %d\n", WhoIsSelectedMap(valider));
	}
}

void ValiderUp2(Element * valider, int i) {
	(void) i;
	DataValidate2 * d = valider->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanBtnValiderDown);
	setDisplayCodeWindow(ECRAN_FIGHT);
	initFight(d->indiceJoueur,d->indiceJoueur2,WhoIsSelectedMap(valider));
}

DataMap * initDataMap(int i) {
	DataMap * d = malloc(sizeof(DataMap));
	if(d){
		d->id = i;
		d->verif = 0;
		if(i == 0) d->isSelected = 1;
		else d->isSelected = 0;
	}

	return d;
}

void UnSelectMap(Element * map) {
	initIteratorElement(map);
	Element * valider = nextIteratorElement(map);
	initIteratorElement(valider);
	Element * m = nextIteratorElement(valider);
	DataMap * d = m->data;
	int compteur = 0;
	while (compteur<NBMAP && d->isSelected == 0) {
		m = nextIteratorElement(valider);
		d = m->data;
		compteur ++;
	}
	d->isSelected = 0;
}

int WhoIsSelectedMap(Element * valider) {
	initIteratorElement(valider);
	Element * m = nextIteratorElement(valider);
	DataMap * d = m->data;
	int compteur = 0;
	while (compteur<NBMAP && d->isSelected == 0) {
		m = nextIteratorElement(valider);
		d = m->data;
		compteur ++;
	}
	return d->id;
}

void MapDown(Element * map, int i) {
	(void) i;
	int largeurMap = HFEN/5;
	int ecartMap = (LFEN-NBMAP*largeurMap)/(NBMAP+1);
	DataMap * d = map->data;
	char s[14] = "assets/m9.png";
	if(!d->verif) {
		d->verif = 1;
		if(!d->isSelected)
		{
			UnSelectMap(map);
			clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanMapDown);
			d->isSelected = 1;
			s[8] = d->id*2+49;
			createImage(ecartMap+d->id*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,s,ECRAN_CHOIX_MAP,PlanMapDown);
		}
	}
}

void MapUp(Element * map, int i) {
	(void) i;
	DataMap * d = map->data;
	d->verif = 0;
}
*/