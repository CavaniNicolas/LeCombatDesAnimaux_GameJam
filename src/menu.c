
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "menu.h"
/******************* ECRAN_TITRE ***********************************/
// init

void Launcher() {
	int red[4] = {255,0,0,255};
	int green[4] = {0,255,0,255};
	int black[4] = {0,0,0,255};
	createImage(0,0,LFEN,HFEN,"assets/beach.jpg",ECRAN_TITRE,PlanDecor);

	Element * titre = createText(LFEN/2-100,HFEN/2,500,100,50,"fonts/arial.ttf","Le Combat Des Animaux",red,SANDAL2_BLENDED,ECRAN_TITRE,PlanTitre);
	Element * titre2 = createText(LFEN/2-4-100,HFEN/2+5,500,100,50,"fonts/arial.ttf","Le Combat Des Animaux",black,SANDAL2_BLENDED,ECRAN_TITRE,PlanTitreFond);
	addElementToElement(titre,titre2);
	Element * r1 = createBlock(0,0,LFEN/2,HFEN,green,ECRAN_TITRE,PlanRideau);
	Element * r2 = createBlock(LFEN/2,0,LFEN/2,HFEN,green,ECRAN_TITRE,PlanRideau);

	setActionElement(r1,depRideau1);
	setActionElement(r2,depRideau2);
	setActionElement(titre,aggrandissement);
}

// rideau

void depRideau1(Element * r1) {
	r1->x -= 5;
	if(r1->x < -LFEN) clearPlanDisplayCode(ECRAN_TITRE,PlanRideau);
}

void depRideau2(Element * r2) {
	r2->x += 5;
}

// titre

void aggrandissement(Element * titre) {
	int red[4] = {255,0,0,255};
	int vitesse = 2;
	initIteratorElement(titre);
	Element * titre2 = nextIteratorElement(titre);
	titre->x -= vitesse;
	titre->y -= vitesse;
	titre->width += vitesse;
	titre->height += vitesse;
	titre2->x -= vitesse;
	titre2->y -= vitesse;
	titre2->width += vitesse;
	titre2->height += vitesse;

	if(titre->y < LFEN/8-150) {
		titre->events.action = NULL;
		Element * start = createText(2*LFEN/3-100,HFEN/2-100,350,180,50,"fonts/arial.ttf","Start",red,SANDAL2_BLENDED,ECRAN_TITRE,PlanStartUp);
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
		createText(2*LFEN/3-100,HFEN/2-100,350,180,50,"fonts/arial.ttf","Start",green,SANDAL2_BLENDED,ECRAN_TITRE,PlanStartDown);
	}
}

void StartUp(Element * start, int i) {
	(void) i;
	DataStart * d = start->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_TITRE,PlanStartDown);
	setDisplayCodeWindow(ECRAN_CHOIX_PERSO);
	initChoicePerso(JOUEUR_G, NULL);
}

/******************* ECRAN_CHOIX_PERSO ***********************************/
// init

void initChoicePerso(int indiceJoueur, Element * valider) {
	int white[4] = {255,255,255,255};
	int red[4] = {255,0,0,255};
	int black[4] = {0,0,0,255};
	Element * Perso = NULL;
	Element * txtinfo = NULL;
	int positionContourBlanc = LFEN/2+100;
	int largeurPerso = HFEN/6;
	int nbPersoParLigne = 2;
	int ecartPerso = (positionContourBlanc-nbPersoParLigne*largeurPerso)/(nbPersoParLigne+1);
	int titrePosY = HFEN/30;
	int titreHeight = 150;
	char titre[20] = "Choix du perso J0";
	titre[16] = indiceJoueur+49;
	if(indiceJoueur == JOUEUR_G)
	{
		createImage(0,0,LFEN,HFEN,"assets/beach.jpg",ECRAN_CHOIX_PERSO,PlanDecor);
		createText(LFEN/8,titrePosY,400,titreHeight,50,"fonts/arial.ttf",titre,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanTitre);
		txtinfo = createText(5*LFEN/8-20,HFEN/30,400,150,50,"fonts/arial.ttf","Infos Personnage",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfo);
		Element * txtpv = createText(LFEN/2+100,HFEN/30+170,150,80,40,"fonts/arial.ttf","Pv",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfo);
		Element * txtforce = createText(LFEN/2+115,txtpv->y+txtpv->height,150,80,50,"fonts/arial.ttf","Force",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfo);
		Element * txtvitesse = createText(LFEN/2+100,txtforce->y+txtforce->height,180,90,50,"fonts/arial.ttf","Vitesse",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfo);
		Element * txtattaque = createText(LFEN/2+80,txtvitesse->y+txtvitesse->height,320,110,50,"fonts/arial.ttf","Attaque Speciale",white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfo);
		addElementToElement(txtinfo,txtpv);
		addElementToElement(txtinfo,txtforce);
		addElementToElement(txtinfo,txtvitesse);
		addElementToElement(txtinfo,txtattaque);
		GenerateInfo(0, txtinfo);
		createBlock(positionContourBlanc,HFEN/23,LFEN/2-200,HFEN-2*HFEN/23,white,ECRAN_CHOIX_PERSO,PlanContourBlanc);
		createBlock(positionContourBlanc+2,HFEN/23+2,LFEN/2-204,HFEN-2*HFEN/23-4,black,ECRAN_CHOIX_PERSO,PlanFondNoir);
		valider = createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_PERSO,PlanBtnValiderUp);
		DataValidate * d = initDataValidate(indiceJoueur);
		valider->data = d;
		addClickableElement(valider,rectangleClickable(0.f,0.f,1.f,1.f),0);
		setOnClickElement(valider,ValiderDown);
		setUnClickElement(valider,ValiderUp);
		Element * retour = createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_PERSO,PlanBtnRetourUp);
		DataRetour * d2 = initDataRetour();
		retour->data = d2;
		addClickableElement(retour,rectangleClickable(0.f,0.f,1.f,1.f),0);
		setOnClickElement(retour,RetourDown);
		setUnClickElement(retour,RetourUp);
		for(int i = 0; i < NBPERSO; i ++) {
			if(!i) Perso = createImage(ecartPerso+(i%nbPersoParLigne)*(largeurPerso+ecartPerso),titrePosY+titreHeight+(i/nbPersoParLigne)*(largeurPerso+ecartPerso),largeurPerso,largeurPerso,"assets/p9.png",ECRAN_CHOIX_PERSO,PlanPersoDown);
			Perso = createImage(ecartPerso+(i%nbPersoParLigne)*(largeurPerso+ecartPerso),titrePosY+titreHeight+(i/nbPersoParLigne)*(largeurPerso+ecartPerso),largeurPerso,largeurPerso,"assets/p0.png",ECRAN_CHOIX_PERSO,PlanPersoUp);
			addElementToElement(valider,Perso);
			addElementToElement(Perso,valider);
			addElementToElement(Perso,txtinfo);
			DataPerso * d3 = initDataPerso(i);
			Perso->data = d3;
			addClickableElement(Perso,rectangleClickable(0.f,0.f,1.f,1.f),0);
			setOnClickElement(Perso,PersoDown);
			setUnClickElement(Perso,PersoUp);
		}
	}
	else if(indiceJoueur == JOUEUR_D)
	{
		DataValidate * v2 = valider->data;
		printf("indice joueur g = %d\n", v2->idJoueurG);
		createText(LFEN/8,titrePosY,400,titreHeight,50,"fonts/arial.ttf",titre,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanTitre);
		initIteratorElement(valider);
		Perso = nextIteratorElement(valider);
		DataPerso * d = Perso->data;
		initIteratorElement(Perso);
		txtinfo = nextIteratorElement(Perso);
		txtinfo = nextIteratorElement(Perso);
		clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanInfoModif);
		GenerateInfo(0, txtinfo);
		clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanPersoDown);
		createImage(ecartPerso,titrePosY+titreHeight,largeurPerso,largeurPerso,"assets/p9.png",ECRAN_CHOIX_PERSO,PlanPersoDown);
		UnSelectPerso(valider);
		d->isSelected = 1;
	}
}

void GenerateInfo(int idPerso, Element * txtinfo) {
	int white[4] = {255,255,255,255};
	char nom[20] = "Toto";
	char caracteristique[50] = "100";
	initIteratorElement(txtinfo);
	Element * txtpv = nextIteratorElement(txtinfo);
	Element * txtforce = nextIteratorElement(txtinfo);
	Element * txtvitesse = nextIteratorElement(txtinfo);
	Element * txtattaque = nextIteratorElement(txtinfo);
	Element * txt = createText(5*LFEN/8,txtinfo->y+txtinfo->height-40,150,80,50,"fonts/arial.ttf",nom,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfoModif);
	txtpv->y = txt->y+txt->height;
	txtforce->y = txtpv->y+txtpv->height;
	txtvitesse->y = txtforce->y+txtforce->height;
	txtattaque->y = txtvitesse->y+txtvitesse->height;
	createText(txtpv->x+txtpv->width+20,txtpv->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfoModif);
	createText(txtforce->x+txtforce->width+20,txtforce->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfoModif);
	createText(txtvitesse->x+txtvitesse->width+20,txtvitesse->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfoModif);
	createText(txtattaque->x+txtattaque->width-60,txtattaque->y,320,110,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,ECRAN_CHOIX_PERSO,PlanInfoModif);
}

DataValidate * initDataValidate(int indiceJoueur) {
	DataValidate * d = malloc(sizeof(DataValidate));
	if(d){
		d->verif = 0;
		d->indiceJoueur = indiceJoueur;
		d->idJoueurG = 0;
	}

	return d;
}

void ValiderDown(Element * valider, int i) {
	(void) i;
	int green[4] = {0,255,0,255};
	int white[4] = {255,255,255,255};
	DataValidate * d = valider->data;
	if(!d->verif) {
		d->verif = 1;
		createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,green,ECRAN_CHOIX_PERSO,PlanBtnValiderDown);
		if(d->indiceJoueur == JOUEUR_G) printf("perso joueur gauche = %d\n", WhoIsSelectedPerso(valider));
		else printf("perso joueur droite = %d\n", WhoIsSelectedPerso(valider));
	}
}

void ValiderUp(Element * valider, int i) {
	(void) i;
	DataValidate * d = valider->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanBtnValiderDown);
	if(d->indiceJoueur == JOUEUR_G)
	{
		d->indiceJoueur = JOUEUR_D;
		d->idJoueurG = WhoIsSelectedPerso(valider);
		printf("ici %d\n", d->idJoueurG);
		initChoicePerso(JOUEUR_D, valider);
		clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanTitre);
	}
	else if(d->indiceJoueur == JOUEUR_D)
	{
		printf("là %d\n", d->idJoueurG);
		setDisplayCodeWindow(ECRAN_CHOIX_MAP);
		initChoiceMap(d->idJoueurG,WhoIsSelectedPerso(valider));
	}
}

DataRetour * initDataRetour() {
	DataRetour * d = malloc(sizeof(DataRetour));
	if(d){
		d->verif = 0;
	}

	return d;
}

void RetourDown(Element * retour, int i) {
	(void) i;
	int green[4] = {0,255,0,255};
	int white[4] = {255,255,255,255};
	DataRetour * d = retour->data;
	if(!d->verif) {
		d->verif = 1;
		createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,green,ECRAN_CHOIX_PERSO,PlanBtnRetourDown);
	}
}

void RetourUp(Element * retour, int i) {
	(void) i;
	DataRetour * d = retour->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanBtnRetourDown);
	setDisplayCodeWindow(ECRAN_TITRE);
}

DataPerso * initDataPerso(int i) {
	DataPerso * d = malloc(sizeof(DataPerso));
	if(d){
		d->id = i;
		d->verif = 0;
		if(i == 0) d->isSelected = 1;
		else d->isSelected = 0;
	}

	return d;
}

void UnSelectPerso(Element * perso) {
	initIteratorElement(perso);
	Element * valider = nextIteratorElement(perso);
	initIteratorElement(valider);
	Element * p = nextIteratorElement(valider);
	DataPerso * d = p->data;
	int compteur = 0;
	while (compteur<NBPERSO && d->isSelected == 0) {
		p = nextIteratorElement(valider);
		d = p->data;
		compteur ++;
	}
	d->isSelected = 0;
}

int WhoIsSelectedPerso(Element * valider) {
	initIteratorElement(valider);
	Element * p = nextIteratorElement(valider);
	DataPerso * d = p->data;
	int compteur = 0;
	while (compteur<NBPERSO && d->isSelected == 0) {
		p = nextIteratorElement(valider);
		d = p->data;
		compteur ++;
	}
	return d->id;
}

void PersoDown(Element * perso, int i) {
	(void) i;
	int positionContourBlanc = LFEN/2+100;
	int largeurPerso = HFEN/6;
	int nbPersoParLigne = 2;
	int titrePosY = HFEN/30;
	int titreHeight = 150;
	int ecartPerso = (positionContourBlanc-nbPersoParLigne*largeurPerso)/(nbPersoParLigne+1);
	DataPerso * d = perso->data;
	if(!d->verif) {
		d->verif = 1;
		if(!d->isSelected)
		{
			UnSelectPerso(perso);
			clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanInfoModif);
			initIteratorElement(perso);
			Element * txtinfo = nextIteratorElement(perso);
			txtinfo = nextIteratorElement(perso);
			GenerateInfo(d->id,txtinfo);
			clearPlanDisplayCode(ECRAN_CHOIX_PERSO,PlanPersoDown);
			d->isSelected = 1;
			createImage(ecartPerso+(d->id%nbPersoParLigne)*(largeurPerso+ecartPerso),titrePosY+titreHeight+(d->id/nbPersoParLigne)*(largeurPerso+ecartPerso),largeurPerso,largeurPerso,"assets/p9.png",ECRAN_CHOIX_PERSO,PlanPersoDown);
		}
	}
}

void PersoUp(Element * perso, int i) {
	(void) i;
	DataPerso * d = perso->data;
	d->verif = 0;
}

/******************* ECRAN_CHOIX_MAP ***********************************/
// init

void initChoiceMap(int indiceJoueur, int indiceJoueur2) {
	int white[4] = {255,255,255,255};
	int red[4] = {255,0,0,255};
	int largeurMap = HFEN/5;
	int ecartMap = (LFEN-NBMAP*largeurMap)/(NBMAP+1);
	Element * Map = NULL;
	createImage(0,0,LFEN,HFEN,"assets/beach.jpg",ECRAN_CHOIX_MAP,PlanDecor);
	createText(LFEN/2-200,HFEN/30,400,150,50,"fonts/arial.ttf","Choix de la map",white,SANDAL2_BLENDED,ECRAN_CHOIX_MAP,PlanTitre);
	Element * retour = createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_MAP,PlanBtnRetourUp);
	DataRetour * d = initDataRetour();
	retour->data = d;
	addClickableElement(retour,rectangleClickable(0.f,0.f,1.f,1.f),0);
	setOnClickElement(retour,RetourDown2);
	setUnClickElement(retour,RetourUp2);
	Element * valider = createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,red,ECRAN_CHOIX_MAP,PlanBtnValiderUp);
	DataValidate2 * d2 = initDataValidate2(indiceJoueur, indiceJoueur2);
	valider->data = d2;
	addClickableElement(valider,rectangleClickable(0.f,0.f,1.f,1.f),0);
	setOnClickElement(valider,ValiderDown2);
	setUnClickElement(valider,ValiderUp2);
	for(int i = 0; i < NBMAP; i ++) {
		if(!i) Map = createImage(ecartMap+i*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,"assets/p9.png",ECRAN_CHOIX_MAP,PlanMapDown);
		Map = createImage(ecartMap+i*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,"assets/p0.png",ECRAN_CHOIX_MAP,PlanMapUp);
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
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanBtnRetourDown);
	setDisplayCodeWindow(ECRAN_CHOIX_PERSO);
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
	DataValidate * d = valider->data;
	d->verif = 0;
	clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanBtnValiderDown);
	setDisplayCodeWindow(ECRAN_FIGHT);
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
	if(!d->verif) {
		d->verif = 1;
		if(!d->isSelected)
		{
			UnSelectMap(map);
			clearPlanDisplayCode(ECRAN_CHOIX_MAP,PlanMapDown);
			d->isSelected = 1;
			createImage(ecartMap+d->id*(largeurMap+ecartMap),2*HFEN/5,largeurMap,largeurMap,"assets/p9.png",ECRAN_CHOIX_MAP,PlanMapDown);
		}
	}
}

void MapUp(Element * map, int i) {
	(void) i;
	DataMap * d = map->data;
	d->verif = 0;
}
