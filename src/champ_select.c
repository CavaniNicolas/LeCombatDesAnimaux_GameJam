
#include <SANDAL2/SANDAL2.h>
#include <dirent.h>
#include "optimiseDisplay.h"
#include "structure.h"
#include "champ_select.h"
#include "map_select.h"

//#include "fight.h" // change this into map_select once its finished

void ChampSelect() {
	setDisplayCodeWindow(CHAMP_SELECT);
	generateAllDisplays();

}


void generateAllDisplays() {
	int white[4] = {255, 255, 255, 255};
	int black[4] = {0, 0, 0, 255};

	int marge      = 0.05 * HFEN;

	int xStatBlock = 0.6 * LFEN;
	int hBlock     = HFEN - 2 * marge;

	int wStatBlock = 0.4 * LFEN - marge;

	int wCharBlock = 0.6 * LFEN - 4 * marge;

	createImage(0, 0, LFEN, HFEN, "assets/map0.jpg", CHAMP_SELECT, PlanBackgroundCS);

	// Block d'info à droite
	createBlock(xStatBlock, marge, wStatBlock, hBlock, white, CHAMP_SELECT, PlanBlock); // Contour blanc du block
	createBlock(xStatBlock+2, marge+2, wStatBlock-4, hBlock-4, black, CHAMP_SELECT, PlanBlock-1); // Block noir
	createBlock(xStatBlock, marge+0.4*hBlock, wStatBlock, 2, white, CHAMP_SELECT, PlanBlock-1); // Ligne séparatrice dans le block

	// Button OK
	//createValidateInBlock(xStatBlock, marge, wStatBlock, hBlock);

	int yGraphBlock = marge+0.4*hBlock;
	// Stats Texts
	createStatsNames(xStatBlock, yGraphBlock, wStatBlock/2, 0.6*hBlock);

	// Characters and statsGraphs
	createBlock(marge, marge, wCharBlock, hBlock, white, CHAMP_SELECT, PlanChampSelect); // Contour blanc du block
	createBlock(marge+2, marge+2, wCharBlock-4, hBlock-4, black, CHAMP_SELECT, PlanChampSelect); // Block noir

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
		int xinterObjSpace  = spaceBetweenObjects(nbColumns, sizeSideIm, wBlock);

		/* calcul de l'espace vide entre deux elements selon les y */
		int yinterObjSpace  = spaceBetweenObjects(nbLines, sizeSideIm, hBlock);


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
				newElement = createImage(xIm, yIm, sizeSideIm, sizeSideIm, filenameCharacter, CHAMP_SELECT, PlanChampSelect); // affiche le perso sur lequel on peut clicker

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
		versusImages->leftChara = createImage(xBlock, yBlock, wImage, hBlock, "assets/empty.png", CHAMP_SELECT, PlanCharactersVersus);
		versusImages->rightChara = createImage(xBlock + wImage, yBlock, wImage, hBlock, "assets/empty.png", CHAMP_SELECT, PlanCharactersVersus);
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
		statsGraphs->hpBox = createBlock(xGraph, yBlock+fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphsBackground);
		statsGraphs->strengthBox = createBlock(xGraph, yBlock+2*fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphsBackground);
		statsGraphs->speedBox = createBlock(xGraph, yBlock+3*fieldSpace+quarterFieldSpace, wGraph, hGraph, white, CHAMP_SELECT, PlanStatsGraphsBackground);

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

		MapSelect();
		//initFight(d->idCharaLeftPlayer, d->idCharaRightPlayer, 0);
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
