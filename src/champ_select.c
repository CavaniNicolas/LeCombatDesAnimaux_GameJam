
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include <dirent.h>
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

	int marge      = 0.05 * HFEN;

	int xStatBlock = 0.6 * LFEN;
	int hBlock     = HFEN - 2 * marge;

	int wStatBlock = 0.4 * LFEN - marge;

	int wCharBlock = 0.6 * LFEN - 4 * marge;

	createImage(0, 0, LFEN, HFEN, "assets/map0.jpg", CHAMP_SELECT, PlanBackgroundCS);

	// Block d'info à droite
	createBlock(xStatBlock, marge, wStatBlock, hBlock, white, CHAMP_SELECT, PlanBlock);
	createBlock(xStatBlock+2, marge+2, wStatBlock-4, hBlock-4, black, CHAMP_SELECT, PlanBlock-1);
	createBlock(xStatBlock, marge+0.4*hBlock, wStatBlock, 2, white, CHAMP_SELECT, PlanBlock-1); // Ligne séparatrice dans le block

	// Button OK
	//createValidateInBlock(xStatBlock, marge, wStatBlock, hBlock);

	int yGraphBlock = marge+0.4*hBlock;
	// Stats Texts
	createStatsNames(xStatBlock, yGraphBlock, wStatBlock/2, 0.6*hBlock);

	// Characters and statsGraphs
	createBlock(marge, marge, wCharBlock, hBlock, white, CHAMP_SELECT, PlanChampSelect);
	createBlock(marge+2, marge+2, wCharBlock-4, hBlock-4, black, CHAMP_SELECT, PlanChampSelect);

	int nbChara = 3; float fillPercent = 0.8; int nbLines = 0; int nbColumns = 0; int sizeSideIm = 0;
	if (0 == checkIfnbCharaIsCorrect(nbChara)) {
		createFieldsChampSelectInBlock(marge+2, marge+2, wCharBlock-4, hBlock-4, nbChara, fillPercent, &nbLines, &nbColumns, &sizeSideIm, xStatBlock, marge, wStatBlock, hBlock);
	} else {
		printf("Assets des personnages pour la ChampSelect manquantes\n");
	}

}


// verifie si il y a suffisament d'assets dans le repertoire pour creer les perso de la champSelect
int checkIfnbCharaIsCorrect(int nbChara) {
	char  error = 1;

	int counter = 0;
	DIR * rep   = opendir("./assets/characters"); /*Pointeur répertoire*/
	char  filename[10];                           /*Nom du fichier*/

	if (rep != NULL) {
		struct dirent * ent = NULL;               /*Pointeur entitée*/

		while ((ent = readdir(rep)) != NULL) {

			if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) { /*Si ce n'est pas un de ces fichiers*/
				strcpy(filename, ent->d_name);
				if (filename[0] == 'c') {
					counter++;
				}
			}
		}

		if (counter == nbChara) {
			error = 0;
		}

		closedir(rep);
	}
	return error;
}


// affiche les cases pour la champ select et les rends clickable
void createFieldsChampSelectInBlock(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm, int xGraph, int yGraph, int wGraph, int hGraph) {
	setOptimizedLinesAndColumns(wBlock, hBlock, nbChara, fillPercent, nbLines, nbColumns, sizeSideIm);
	displayBlocksInOptimizedPosition(xBlock, yBlock, wBlock, hBlock, nbChara, *nbLines, *nbColumns, *sizeSideIm, xGraph, yGraph, wGraph, hGraph);

}


//modifie (optimise) les valeurs de lines et columns si elles sont = 0.
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	if (*nbColumns > 0 && *nbLines > 0) {
		printf("Ne pas entrer à la fois nbColumns et nbLines > 0\n"\
			   "(Ne pas appliquer de contraintes sur les deux paramètres en même temps)\n"\
			   "Mettre 0 pour une optimisation automatique d'une ou des deux variables\n");
		optimizeNumberOfLinesColumns(wBlock, hBlock, nbChara, fillPercent, nbLines, nbColumns, sizeSideIm);

	} else {

		if (*nbColumns > 0) {

			setSecondVariable(*nbColumns, nbLines, sizeSideIm, nbChara, fillPercent, wBlock, hBlock);

		} else if (*nbLines > 0){

			setSecondVariable(*nbLines, nbColumns, sizeSideIm, nbChara, fillPercent, wBlock, hBlock);

		} else {
			optimizeNumberOfLinesColumns(wBlock, hBlock, nbChara, fillPercent, nbLines, nbColumns, sizeSideIm);
		}

	}
}


void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbChara, float fillPercent, int wBlock, int hBlock) {
	int sizeSideImX = 0;
	int sizeSideImY = 0;

	// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
	*varAdapting = nbChara / varCte;
	if (nbChara%varCte != 0) {
		(*varAdapting) ++;
	}

	sizeSideImX = fillPercent * wBlock / varCte;
	sizeSideImY = fillPercent * hBlock / *varAdapting;
	*sizeSideIm  = (sizeSideImX < sizeSideImY)? sizeSideImX : sizeSideImY; // side of the square
}


//calcul le nombre optimal de lignes et colonnes
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm) {
	int good = 0;

	*nbColumns = nbChara;
	*nbLines   = 1;

	int sImX = 0;
	int sImY = 0;

	int sImNouv = 0;
	int ecartSImNouv = 0;

	int sImAncien = 0;
	int ecartSImAncien = (hBlock > wBlock)? hBlock : wBlock;; //max entre hBlock et hBlock

	while (good == 0) {
		sImX = fillPercent * wBlock / *nbColumns;
		sImY = fillPercent * hBlock / *nbLines;
		sImNouv = (sImX < sImY)? sImX : sImY;
		ecartSImNouv = abs(sImX - sImY);

		if (ecartSImNouv > ecartSImAncien) {
			good = 1;

			// on remet les bonnes valeurs de ligne et de colonne correspondantes aux bonnes valeurs de sizeSideIm
			(*nbColumns)++;
			(*nbLines)--;


		} else {
			sImAncien = sImNouv;
			ecartSImAncien = ecartSImNouv;
			(*nbColumns)--;
		}


		if (*nbColumns == 0) {
			good = 1;
			(*nbColumns)++;
		}
		if (*nbLines == 0) {
			good = 1;
			(*nbLines)++;
		}
		if (*nbColumns * *nbLines < nbChara) {
			(*nbLines)++;
		}
	}
	*sizeSideIm = sImAncien;

	printf("colonne = %d, ligne = %d \n", *nbColumns, * nbLines);

}


// affiche les blocs une fois quon connait le nombre de lignes et colonnes souhaitées
void displayBlocksInOptimizedPosition(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, int nbLines, int nbColumns, int sizeSideIm, int xStatBlock, int yStatBlock, int wStatBlock, int hStatBlock) {
	FILE * file = NULL;
	file = fopen("assets/stats/DataCharacters.txt", "r");

	if (file != NULL) {

		Element * element0    = NULL;
		Element * newElement  = NULL;
		Element * prevElement = NULL;

		char filenameCharacter[30] = "assets/characters/c0.png";

		//int white[4] = {255, 255, 255, 255};
		int idChara = 0; int y = 1;

		/* calcul de l'espace vide entre deux elements selon les x */
		int xTotalSpaceUsed = nbColumns * sizeSideIm;
		int xTotalSpaceFree = wBlock - xTotalSpaceUsed;
		int xinterObjSpace  = xTotalSpaceFree / (2 * nbColumns);

		/* calcul de l'espace vide entre deux elements selon les y */
		int yTotalSpaceUsed = nbLines * sizeSideIm;
		int yTotalSpaceFree = hBlock - yTotalSpaceUsed;
		int yinterObjSpace  = yTotalSpaceFree / (2 * nbLines);

		/* position initiale du premier element0 */
		int xIm = xBlock + xinterObjSpace;
		int yIm = yBlock + yinterObjSpace;

		// structure des statsMax
		StatsCharacter_t    * dataNewElement = NULL;
		StatsCharacterMax_t * statsMax       = getCharacterStatsMaxInFile();
		// structure des blocs pour afficher les stats
		StatsGraphs_t * statsGraphs = initStatsGraphs(xStatBlock+0.5*wStatBlock, yStatBlock+0.4*hStatBlock, wStatBlock/2, 0.6*hStatBlock);
		// structure du okButton_t
		Element * okButton = createValidateInBlock(xStatBlock, yStatBlock, wStatBlock, hStatBlock);
		// structure des 2 pointeurs sur les images afficher pour le Versus
		VersusImages_t * versusImages = initVersusImages(xStatBlock+2, yStatBlock+2, wStatBlock-4, hStatBlock * 0.4);

		if (statsMax!=NULL && statsGraphs!=NULL && okButton!=NULL && versusImages!=NULL) {

			for (idChara=0; idChara<nbChara; idChara++) {
				filenameCharacter[19] = 48 + idChara; /*max 10 perso car va de 0 à 9*/

				//createBlock(xIm, yIm, sizeSideIm, sizeSideIm, white, CHAMP_SELECT, PlanChampSelect);
				newElement = createImage(xIm, yIm, sizeSideIm, sizeSideIm, filenameCharacter, CHAMP_SELECT, PlanChampSelect);

				if (newElement != NULL) {

					// initialise les champs (stats) du nouvel element
					newElement->data = getCharacterStatsInFile(file, idChara);

					if (newElement->data != NULL) {
						// ajoute le pointeur sur la structure des statsMax
						dataNewElement = newElement->data;
						dataNewElement->statsMax = statsMax;
						
						// ajoute le pointeur sur la structure okButton_t
						dataNewElement->okButton = okButton;

						// ajoute les blocs où seront affichées les stats
						dataNewElement->statsGraphs = statsGraphs;

						// ajoute la structure des deux images du Versus
						dataNewElement->versusImages = versusImages;

						// rend l'element clickable et lui assigne une action
						addClickableElement(newElement, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
						setOnClickElement(newElement, onClickActionsChampSelect);

						// assemble les elements entre eux (sous la forme d'une liste chainée circulaire)
						if (idChara == 0) {
							element0 = newElement;
						} else {
							prevElement->elementParent = newElement;
						}
						prevElement = newElement;
					}

				}

				/* colonne suivante */
				y++;

				/* calcul d'un saut de ligne nécessaire ou non */
				if (y <= nbColumns) {
					xIm += sizeSideIm + 2 * xinterObjSpace;
				} else {
					xIm = xBlock + xinterObjSpace;
					yIm += sizeSideIm + 2 * yinterObjSpace;
					y = 1;
				}

			}

			if (newElement != NULL) {
				// dernier element de la liste chainée circulaire pointe sur le premier
				newElement->elementParent = element0;
			}
		}

		fclose(file);
	} else {
		printf("Ne peut pas ouvrir le fichier des stats des Perso\n");
	}
}


// init la structure des images du Versus
VersusImages_t * initVersusImages(int xBlock, int yBlock, int wBlock, int hBlock) {
	VersusImages_t * versusImages = (VersusImages_t *)malloc(sizeof(VersusImages_t));

	int wImage = wBlock / 2;

	if (versusImages != NULL) {
		versusImages->leftChara = createImage(xBlock, yBlock, wImage, hBlock, "assets/empty.png", CHAMP_SELECT, PlanChampSelect);
		versusImages->rightChara = createImage(xBlock + wImage, yBlock, wImage, hBlock, "assets/empty.png", CHAMP_SELECT, PlanChampSelect);
		versusImages->rightChara->flip = SANDAL2_FLIP_HOR;
	}

	return versusImages;
}


// creer les blocks de stats pour les perso, qui seront a modifier lors d'un clic
StatsGraphs_t * initStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock) {
	StatsGraphs_t * statsGraphs = (StatsGraphs_t *)malloc(sizeof(StatsGraphs_t));
	int white[4] = {255, 255, 255, 255};
	int orange[4] = {255, 150, 0, 255};

	int statsNb    = 4; // Nombre de champs pour les stats des perso
	int fieldSpace = hBlock / statsNb; 
	int quarterFieldSpace = 0.25*fieldSpace;

	int xGraph = xBlock;
	int wGraph = 0.8 * wBlock;
	int hGraph = fieldSpace/2;


	if (statsGraphs != NULL) {
		statsGraphs->hpBox = createBlock(xGraph, yBlock+fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphs + 1);
		statsGraphs->strengthBox = createBlock(xGraph, yBlock+2*fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphs + 1);
		statsGraphs->speedBox = createBlock(xGraph, yBlock+3*fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphs + 1);

		statsGraphs->hp = createBlock(xGraph+2, yBlock+fieldSpace+2+quarterFieldSpace, wGraph-4, hGraph-4, orange, CHAMP_SELECT, PlanStatsGraphs);
		statsGraphs->strength = createBlock(xGraph+2, yBlock+2*fieldSpace+2+quarterFieldSpace, wGraph-4, hGraph-4, orange, CHAMP_SELECT, PlanStatsGraphs);
		statsGraphs->speed = createBlock(xGraph+2, yBlock+3*fieldSpace+2+quarterFieldSpace, wGraph-4, hGraph-4, orange, CHAMP_SELECT, PlanStatsGraphs);
	}

	return statsGraphs;
}


// rempli les champs stats du perso
StatsCharacter_t * getCharacterStatsInFile(FILE * file, int idChara) {
	StatsCharacter_t * d = (StatsCharacter_t *)malloc(sizeof(StatsCharacter_t));
	int idCharaFile = -1;
	char line[6];

	if (d != NULL) {
		d->isSelected = false;
		while (!feof(file) && idCharaFile != idChara) {
			fgets(line, 6, file);
			idCharaFile = atoi(line);
		}
		// On est au bon endroit dans le fichier pour commencer a lire les stats
		d->idChara = idCharaFile;

		fgets(line, 6, file);
		d->hp = atoi(line);

		fgets(line, 6, file);
		d->strength = atoi(line);

		fgets(line, 6, file);
		d->speed = atoi(line);

	} else {
		printf("Erreur memoire\n");
	}

	return d;
}


StatsCharacterMax_t * getCharacterStatsMaxInFile() {
	FILE * file = fopen("assets/stats/statsMax.txt", "r");

	StatsCharacterMax_t * statsMax = (StatsCharacterMax_t *)malloc(sizeof(StatsCharacterMax_t));

	if (file != NULL) {
		fscanf(file, "%d", &statsMax->hp);
		fscanf(file, "%d", &statsMax->strength);
		fscanf(file, "%le", &statsMax->speed);
	}

	fclose(file);
	return statsMax;
}


// actions a executer quand on clic sur un perso de la champ select
void onClickActionsChampSelect(Element * element, int i) {
	(void) i;
	StatsCharacter_t * d = element->data;
	okButton_t * okButton = d->okButton->data;

	displayCharacterStats(element);
	selectCharacter(element);
	displayCharacterVersus(d->versusImages, d->idChara, okButton->nbClick);
}


// affiche les stats des persos quand on clic dessus
void displayCharacterStats(Element * element) {
	StatsCharacter_t * d = element->data;

	int hpMax = d->statsMax->hp;
	int strengthMax = d->statsMax->strength;
	int speedMax = d->statsMax->speed;

	int hp = d->hp;
	int strength = d->strength;
	int speed = d->speed;

	int widthMax = d->statsGraphs->hpBox->width;

	d->statsGraphs->hp->width = (hp * widthMax / hpMax) - 4;
	d->statsGraphs->strength->width = (strength * widthMax / strengthMax) - 4;
	d->statsGraphs->speed->width = (speed * widthMax / speedMax) - 4;

	// modifie limgage du perso choisie (dans le VERSUS)
	//int setImageElement(Element * e, const char * image)
}


// rempli la structure okButton avec l'id du perso choisi
void selectCharacter(Element * element) {
	StatsCharacter_t * d = element->data;
	okButton_t * dd = d->okButton->data;

	if (dd->nbClick == 0) {
		dd->idCharaLeftPlayer = d->idChara;
	}

	if (dd->nbClick == 1) {
		dd->idCharaRightPlayer = d->idChara;
	}
}


// affiche le bon perso dans le versus
void displayCharacterVersus(VersusImages_t * versusImages, int idChara, int nbClick) {

	char filename[30] = "assets/characters/c0.png";
	filename[19] = idChara + 48;

	if (nbClick == 0) {
		setImageElement(versusImages->leftChara, filename);
	}
	if (nbClick == 1) {
		setImageElement(versusImages->rightChara, filename);
	}
}


void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock) {
	int statsNb    = 4; // Nombre de champs pour les stats des perso
	int fieldSpace = hBlock / statsNb; 

	int xText =	xBlock;
	int wText = 0.9 * wBlock;
	int hText = fieldSpace;

	createImage(xText, yBlock, wText, hText, "assets/texts/Infos_Perso.png", CHAMP_SELECT, PlanBlock-2); // Element * textInfo
	createImage(xText, yBlock+fieldSpace, wText, hText, "assets/texts/HP.png", CHAMP_SELECT, PlanBlock-2); // Element * textHP
	createImage(xText, yBlock+2*fieldSpace, wText, hText, "assets/texts/STRENGTH.png", CHAMP_SELECT, PlanBlock-2); // Element * textSTRENGTH
	createImage(xText, yBlock+3*fieldSpace, wText, hText, "assets/texts/SPEED.png", CHAMP_SELECT, PlanBlock-2); // Element * textSPEED
}

Element * createValidateInBlock(int xBlock, int yBlock, int wBlock, int hBlock) {
	int wVal = wBlock/3;
	int hVal = 0.1*hBlock;
	int xVal = xBlock+wVal;
	int yVal = yBlock+0.4*hBlock - hVal/2 ;

	Element * okButton = createImage(xVal, yVal, wVal, hVal, "assets/GOButton.png", CHAMP_SELECT, PlanOkButton);

	if (okButton != NULL) {

		addClickableElement(okButton, rectangleClickable(0.f, 0.f, 1.f, 1.f), 0);
		setOnClickElement(okButton, validateCharacterChoice);
		setActionElement(okButton, charactersValidation);
	
		okButton_t * okButtonStruct = (okButton_t *)malloc(sizeof(okButton_t));

		if (okButtonStruct != NULL) {
			okButton->data = okButtonStruct;

			okButtonStruct->nbClick = 0;
			okButtonStruct->idCharaLeftPlayer = -1;
			okButtonStruct->idCharaRightPlayer = -1;

		}
	}


	return okButton;
}

void validateCharacterChoice(Element * okButton, int i) {
	(void) i;
	okButton_t * d = okButton->data;

	if (d->nbClick == 0 && d->idCharaLeftPlayer != -1) {
		d->nbClick += 1;
		printf("perso joueur gauche choisi\n");
	}

	if (d->nbClick == 1 && d->idCharaRightPlayer != -1) {
		d->nbClick += 1;
		printf("perso joueur droit choisi\n");
	}

	printf("OK nbClick = %d\n", d->nbClick);

}

void charactersValidation(Element * okButton) {
	okButton_t * d = okButton->data;

	if (d->nbClick == 2) {
		d->nbClick += 1;
		printf("On passe a la MapSelect\n");
		printf("idChara Gauche = %d\n", d->idCharaLeftPlayer);
		printf("idChara Droite = %d\n", d->idCharaRightPlayer);
	}
}


// set Action Element sur element0 de la champSelect, quand nbClick >= 3 alors: free all


/* ------------------------------------------------------------------------------------------------------------------------ */
/*
// passe la valeur de isClicked a true quand on clic sur lelement
void isClickedSetOn(Element * element, int i) {
	(void) i;
	clearPlanDisplayCode(CHAMP_SELECT, PlanStatsGraphs);
	StatsCharacter_t * d = element->data;

	Element    * parentElement = element;
	StatsCharacter_t * dParent = element->data;

	while (dParent->idChara != 0) {
		parentElement = parentElement->elementParent;
		dParent = parentElement->data;
	}

	printf("id = %d\n", dParent->idChara);
	Element * nextElement = parentElement->elementParent;
	StatsCharacter_t * dNext = nextElement->data;

	while (nextElement != parentElement) {
		printf("id = %d\n", dNext->idChara);
		dNext->isClicked = false;
		nextElement = nextElement->elementParent;
		dNext = nextElement->data;
	}

	d->isClicked = true;
	printf("clicked on : id = %d\n",d->idChara);
}
*/


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
