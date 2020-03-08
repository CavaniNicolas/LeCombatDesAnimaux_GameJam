
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "champ_select.h"

#include "menu.h"


/******************* CHAMP_SELECT ***********************************/
// init

void ChampSelect() {
	setDisplayCodeWindow(CHAMP_SELECT);
	int white[4]             = {255, 255, 255, 255};
	int black[4]             = {0, 0, 0, 255};

	int xBlock = LFEN / 2 + 120;
	int yBlock = HFEN / 23;
	int wBlock = LFEN - 50 - xBlock;
	int hBlock = HFEN - 2 * yBlock;

	int statsNb = 3; // Nombre de champs pour les stats des perso

	createImage(0, 0, LFEN, HFEN, "assets/map0.jpg", CHAMP_SELECT, PlanBackground);

	// Block d'info à droite
	createBlock(xBlock, yBlock, wBlock, hBlock, white, CHAMP_SELECT, PlanBlock);
	createBlock(xBlock+2, yBlock+2, wBlock-4, hBlock-4, black, CHAMP_SELECT, PlanBlock-1);
	createBlock(xBlock, HFEN/2-50, wBlock, 2, white, CHAMP_SELECT, PlanBlock-1); // Ligne séparatrice dans le block

	createValidateInBlock(xBlock, yBlock, wBlock, hBlock);

	createStatsNames(xBlock, HFEN/2-50, wBlock, hBlock - yBlock - HFEN/2-50, statsNb);


}

void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock, int statsNb) {
	int white[4]             = {255, 255, 255, 255};
	int sbf = hBlock / (statsNb + 1); // spaceBetweenFields
	(void) wBlock;

	int xText =	xBlock + 30;
	int yText = yBlock;
	int wText = 200;
	int hText = 50;

	Element * textInfo     = createText(xText , yText+sbf, wText, hText, 50, "fonts/arial.ttf", "Infos Personnage", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanBlock-2);
	Element * textHP       = createText(xText , yText+2*sbf, wText, hText, 50, "fonts/arial.ttf", "HP", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanBlock-2);
	Element * textSTRENGTH = createText(xText , yText+3*sbf, wText, hText, 50, "fonts/arial.ttf", "STRENGTH", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanBlock-2);
	Element * textSPEED    = createText(xText , yText+4*sbf, wText, hText, 50, "fonts/arial.ttf", "SPEED", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanBlock-2);
}

void createValidateInBlock(int xBlock, int yBlock, int wBlock, int hBlock) {
	int red[4] = {255, 0, 0, 255};
	(void) yBlock;

	int wVal = wBlock/3;
	int hVal = 0.1*hBlock;
	int xVal = xBlock+wVal;
	int yVal = HFEN/2-50 - hVal/2 ;

	Element * okButton = createBlock(xVal, yVal, wVal, hVal, red, CHAMP_SELECT, PlanBlock-4);

	// fcts a assigner a ce block lorsquon clic dessus
}


void initChoicePerso() {
	int white[4]             = {255, 255, 255, 255};
	int red[4]               = {255, 0, 0, 255};
	int black[4]             = {0, 0, 0, 255};

	Element * Perso          = NULL;

	int positionContourBlanc = LFEN / 2 + 100;
	int largeurPerso         = HFEN / 6;
	int nbPersoParLigne      = 2;
	int ecartPerso           = (positionContourBlanc-nbPersoParLigne*largeurPerso) / (nbPersoParLigne+1);
	int xTitle               = LFEN / 8;
	int yTitle               = HFEN / 30;
	int titreHeight          = 150;
	char s[14]               = "assets/p9.png";

	createImage(0, 0, LFEN, HFEN, "assets/fond.jpg", CHAMP_SELECT, PlanBackground);
	createText(xTitle, yTitle, 600, titreHeight, 50, "fonts/arial.ttf", "Choix du perso J1", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanTitre);

	Element * txtinfo     = createText(5*xTitle-20, yTitle, 400, 150, 50, "fonts/arial.ttf", "Infos Personnage", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanInfo);
	Element * textHP      = createText(LFEN/2+100, yTitle+170, 150, 80, 40, "fonts/arial.ttf", "Pv", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanInfo);
	Element * txtSTRENGTH = createText(LFEN/2+115, textHP->y+textHP->height, 150, 80, 50, "fonts/arial.ttf", "Force", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanInfo);
	Element * txtSPEED    = createText(LFEN/2+100, txtSTRENGTH->y+txtSTRENGTH->height, 180, 90, 50, "fonts/arial.ttf", "Vitesse", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanInfo);
	Element * txtATTACK   = createText(LFEN/2+80, txtSPEED->y+txtSPEED->height, 320, 110, 50, "fonts/arial.ttf", "Attaque Speciale", white, SANDAL2_BLENDED, CHAMP_SELECT, PlanInfo);
	addElementToElement(txtinfo, textHP);
	addElementToElement(txtinfo, txtSTRENGTH);
	addElementToElement(txtinfo, txtSPEED);
	addElementToElement(txtinfo, txtATTACK);

	GenerateInfo(0, txtinfo);

	createBlock(positionContourBlanc, HFEN/23, LFEN/2-200, HFEN-2*HFEN/23, white, CHAMP_SELECT, PlanContourBlanc);
	createBlock(positionContourBlanc+2, HFEN/23+2, LFEN/2-204,HFEN-2*HFEN/23-4, black, CHAMP_SELECT, PlanFondNoir);

	Element * valider = createButton(5*xTitle+80, yTitle+600, 200, 100, 80, "fonts/arial.ttf", "Valider", white, SANDAL2_BLENDED, red, CHAMP_SELECT, PlanBtnValiderUp);
	DataValidate * d  = initDataValidate();
	valider->data     = d;
	addClickableElement(valider, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
	setOnClickElement(valider, ValiderDown);
	setUnClickElement(valider, ValiderUp);

	Element * retour = createButton(LFEN/30, yTitle, 100, 50, 80, "fonts/arial.ttf", "Retour", white, SANDAL2_BLENDED, red, CHAMP_SELECT, PlanBtnRetourUp);
	DataRetour * d2  = initDataRetour();
	retour->data     = d2;
	addClickableElement(retour, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
	setOnClickElement(retour, RetourDown);
	setUnClickElement(retour, RetourUp);
	addElementToElement(retour,valider);

	for(int i = 0; i < NBPERSO; i ++) {
		if(!i) Perso = createImage(ecartPerso+(i%nbPersoParLigne)*(largeurPerso+ecartPerso), yTitle+titreHeight+(i/nbPersoParLigne)*(largeurPerso+ecartPerso), largeurPerso, largeurPerso, "assets/p1.png", CHAMP_SELECT, PlanPersoDown);
		s[8]  = i*2+48;
		Perso = createImage(ecartPerso+(i%nbPersoParLigne)*(largeurPerso+ecartPerso), yTitle+titreHeight+(i/nbPersoParLigne)*(largeurPerso+ecartPerso), largeurPerso, largeurPerso, s, CHAMP_SELECT, PlanPersoUp);
		addElementToElement(valider, Perso);
		addElementToElement(Perso, valider);
		addElementToElement(Perso, txtinfo);
		DataPerso * d3 = initDataPerso(i);
		Perso->data    = d3;
		addClickableElement(Perso, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
		setOnClickElement(Perso, PersoDown);
		setUnClickElement(Perso, PersoUp);
	}
}

void GenerateInfo(int idPerso, Element * txtinfo) {
	int white[4] = {255,255,255,255};
	
	char nom[20] = "Toto";
	char caracteristique[50] = "100";

	if (idPerso == CROCODILE) {
		strcpy(nom,"kingKrool");
	}
	else {
		strcpy(nom,"donkeyKong");
	}

	initIteratorElement(txtinfo);
	Element * txtpv      = nextIteratorElement(txtinfo);
	Element * txtforce   = nextIteratorElement(txtinfo);
	Element * txtvitesse = nextIteratorElement(txtinfo);
	Element * txtattaque = nextIteratorElement(txtinfo);
	Element * txt        = createText(5*LFEN/8,txtinfo->y+txtinfo->height-40,150,80,50,"fonts/arial.ttf",nom,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);

	txtpv->y      = txt->y+txt->height;
	txtforce->y   = txtpv->y+txtpv->height;
	txtvitesse->y = txtforce->y+txtforce->height;
	txtattaque->y = txtvitesse->y+txtvitesse->height;

	if (idPerso == CROCODILE) {
		strcpy(caracteristique,"100");
		createText(txtpv->x+txtpv->width+20,txtpv->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		strcpy(caracteristique,"100");
		createText(txtforce->x+txtforce->width+20,txtforce->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		strcpy(caracteristique,"32");
		createText(txtvitesse->x+txtvitesse->width+20,txtvitesse->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		//createText(txtattaque->x+txtattaque->width-60,txtattaque->y,320,110,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
	}

	else {
		strcpy(caracteristique,"200");
		createText(txtpv->x+txtpv->width+20,txtpv->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		strcpy(caracteristique,"60");
		createText(txtforce->x+txtforce->width+20,txtforce->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		strcpy(caracteristique,"24");
		createText(txtvitesse->x+txtvitesse->width+20,txtvitesse->y,150,80,50,"fonts/arial.ttf",caracteristique,white,SANDAL2_BLENDED,CHAMP_SELECT,PlanInfoModif);
		//createText
	}
}

DataValidate * initDataValidate() {
	DataValidate * d = malloc(sizeof(DataValidate));
	if(d){
		d->verif = 0;
		d->indiceJoueur = JOUEUR_G;
		d->sauvegarde = 0;
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
		createButton(5*LFEN/8+80,HFEN/30+600,200,100,80,"fonts/arial.ttf","Valider",white,SANDAL2_BLENDED,green,CHAMP_SELECT,PlanBtnValiderDown);
		//if(d->indiceJoueur == JOUEUR_G) printf("perso joueur gauche = %d\n", WhoIsSelectedPerso(valider));
		//else printf("perso joueur droite = %d\n", WhoIsSelectedPerso(valider));
	}
}

void ValiderUp(Element * valider, int i) {
	(void) i;
	DataValidate * d = valider->data;
	int white[4] = {255,255,255,255};
	int titrePosY = HFEN/30;
	int titreHeight = 150;
	d->verif = 0;
	clearPlanDisplayCode(CHAMP_SELECT,PlanBtnValiderDown);
	if(d->indiceJoueur == JOUEUR_G)
	{
		d->indiceJoueur = JOUEUR_D;
		d->sauvegarde = WhoIsSelectedPerso(valider);
		clearPlanDisplayCode(CHAMP_SELECT,PlanTitre);
		createText(LFEN/8,titrePosY,400,titreHeight,50,"fonts/arial.ttf","Choix du perso J2",white,SANDAL2_BLENDED,CHAMP_SELECT,PlanTitre);
	}
	else if(d->indiceJoueur == JOUEUR_D)
	{
		setDisplayCodeWindow(ECRAN_CHOIX_MAP);
		initChoiceMap(d->sauvegarde, WhoIsSelectedPerso(valider), valider);
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
		createButton(LFEN/30,HFEN/30,100,50,80,"fonts/arial.ttf","Retour",white,SANDAL2_BLENDED,green,CHAMP_SELECT,PlanBtnRetourDown);
	}
}

void RetourUp(Element * retour, int i) {
	(void) i;
	DataRetour * d = retour->data;
	int white[4] = {255,255,255,255};
	initIteratorElement(retour);
	Element * valider = nextIteratorElement(retour);
	DataValidate * d2 = valider->data;
	d2->indiceJoueur = JOUEUR_G;
	d->verif = 0;
	clearPlanDisplayCode(CHAMP_SELECT,PlanBtnRetourDown);
	setDisplayCodeWindow(ECRAN_TITRE);
	int titrePosY = HFEN/30;
	int titreHeight = 150;
	clearPlanDisplayCode(CHAMP_SELECT,PlanTitre);
	createText(LFEN/8,titrePosY,400,titreHeight,50,"fonts/arial.ttf","Choix du perso J2",white,SANDAL2_BLENDED,CHAMP_SELECT,PlanTitre);
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
	char s[14] = "assets/p9.png";
	DataPerso * d = perso->data;
	if(!d->verif) {
		d->verif = 1;
		if(!d->isSelected)
		{
			UnSelectPerso(perso);
			clearPlanDisplayCode(CHAMP_SELECT,PlanInfoModif);
			initIteratorElement(perso);
			Element * txtinfo = nextIteratorElement(perso);
			txtinfo = nextIteratorElement(perso);
			GenerateInfo(d->id,txtinfo);
			clearPlanDisplayCode(CHAMP_SELECT,PlanPersoDown);
			d->isSelected = 1;
			s[8] = d->id*2+49;
			createImage(ecartPerso+(d->id%nbPersoParLigne)*(largeurPerso+ecartPerso),titrePosY+titreHeight+(d->id/nbPersoParLigne)*(largeurPerso+ecartPerso),largeurPerso,largeurPerso,s,CHAMP_SELECT,PlanPersoDown);
		}
	}
}

void PersoUp(Element * perso, int i) {
	(void) i;
	DataPerso * d = perso->data;
	d->verif = 0;
}
