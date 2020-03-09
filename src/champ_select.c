
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "champ_select.h"

#include "menu.h"


/******************* CHAMP_SELECT ***********************************/
// init

void ChampSelect() {
	generateAllDisplays();



}


void generateAllDisplays() {
	setDisplayCodeWindow(CHAMP_SELECT);
	int white[4] = {255, 255, 255, 255};
	int black[4] = {0, 0, 0, 255};

	int xStatBlock = 0.6 * LFEN;
	int yStatBlock = 0.05 * HFEN;
	int wStatBlock = 0.4 * LFEN - yStatBlock;
	int hStatBlock = HFEN - 2 * yStatBlock;

	createImage(0, 0, LFEN, HFEN, "assets/map0.jpg", CHAMP_SELECT, PlanBackgroundCS);

	// Block d'info à droite
	createBlock(xStatBlock, yStatBlock, wStatBlock, hStatBlock, white, CHAMP_SELECT, PlanBlock);
	createBlock(xStatBlock+2, yStatBlock+2, wStatBlock-4, hStatBlock-4, black, CHAMP_SELECT, PlanBlock-1);
	createBlock(xStatBlock, yStatBlock+0.4*hStatBlock, wStatBlock, 2, white, CHAMP_SELECT, PlanBlock-1); // Ligne séparatrice dans le block

	// Button OK
	createValidateInBlock(xStatBlock, yStatBlock, wStatBlock, hStatBlock);

	// Stats Texts
	createStatsNames(xStatBlock, yStatBlock+0.4*hStatBlock, wStatBlock, 0.6*hStatBlock);

	// Characters
	int xCharBlock = yStatBlock;
	int yCharBlock = yStatBlock;
	int wCharBlock = 0.6 * LFEN - 4 * yStatBlock;
	int hCharBlock = hStatBlock;

createBlock(xCharBlock, yCharBlock, wCharBlock, hCharBlock, white, CHAMP_SELECT, PlanChampSelect);
createBlock(xCharBlock+2, yCharBlock+2, wCharBlock-4, hCharBlock-4, black, CHAMP_SELECT, PlanChampSelect);
createCharactersSelect(xCharBlock+2, yCharBlock+2, wCharBlock-4, hCharBlock-4);

	createStatsGraphs(xStatBlock, yStatBlock+0.4*hStatBlock, wStatBlock, 0.6*hStatBlock);
}


void createCharactersSelect(int xBlock, int yBlock, int wBlock, int hBlock) {
	char filenameCharacter[10] = "c0.png";

	int nbPerso                = 9;
	int nbPersoParLigne        = 3;

	int totalSpaceUsed = 0.8 * wBlock;
	int totalSpaceFree = wBlock - totalSpaceUsed;
	int interObjSpace  = totalSpaceFree / (2 * nbPersoParLigne);

	int sIm = totalSpaceUsed / nbPersoParLigne; // side of the square
	int xIm = xBlock;
	int yIm = yBlock + interObjSpace;

	int white[4] = {255, 255, 255, 255};
	int i = 1; int y = 1;

	for (i=1; i<=nbPerso; i++) {

		if (nbPersoParLigne%y < nbPersoParLigne) {
			xIm += interObjSpace;
			createBlock(xIm, yIm, sIm, sIm, white, CHAMP_SELECT, PlanChampSelect);
			xIm += sIm + interObjSpace;
			puts("ici");
		} else {
			y=1;
			xIm = xBlock + interObjSpace;
			yIm += sIm + 2 * interObjSpace;
			createBlock(xIm, yIm, sIm, sIm, white, CHAMP_SELECT, PlanChampSelect);
			xIm += sIm + interObjSpace;
			puts("la");
		}
		y++;

		filenameCharacter[1] = i + 48;
		//createImage(0, 0, LFEN, HFEN, filenameCharacter, CHAMP_SELECT, PlanChampSelect);
	}
}

void createStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock) {
	int statsNb    = 4;
	int fieldSpace = hBlock / statsNb;

	//createBlock();
}

void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock) {
	int statsNb    = 4; // Nombre de champs pour les stats des perso
	int fieldSpace = hBlock / statsNb; 

	int xText =	xBlock;
	int yText = yBlock;
	int wText = 0.4 * wBlock;
	int hText = fieldSpace;

	Element * textInfo     = createImage(xText, yBlock, wText, hText, "assets/texts/Infos_Perso.png", CHAMP_SELECT, PlanBlock-2);
	Element * textHP       = createImage(xText, yBlock+fieldSpace, wText, hText, "assets/texts/HP.png", CHAMP_SELECT, PlanBlock-2);
	Element * textSTRENGTH = createImage(xText, yBlock+2*fieldSpace, wText, hText, "assets/texts/STRENGTH.png", CHAMP_SELECT, PlanBlock-2);
	Element * textSPEED    = createImage(xText, yBlock+3*fieldSpace, wText, hText, "assets/texts/SPEED.png", CHAMP_SELECT, PlanBlock-2);
}

void createValidateInBlock(int xBlock, int yBlock, int wBlock, int hBlock) {
	int red[4] = {255, 0, 0, 255};

	int wVal = wBlock/3;
	int hVal = 0.1*hBlock;
	int xVal = xBlock+wVal;
	int yVal = yBlock+0.4*hBlock - hVal/2 ;

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

	createImage(0, 0, LFEN, HFEN, "assets/fond.jpg", CHAMP_SELECT, PlanBackgroundCS);
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
