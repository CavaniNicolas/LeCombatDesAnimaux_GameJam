
#ifndef CHAMPSELECT_H
#define CHAMPSELECT_H


/*********************** CHAMP_SELECT ******************************/

enum PlanChampSelect {
	PlanBackgroundCS = 99,

	PlanBlock = 89,

	PlanChampSelect = 79,



	PlanTitre = 14,
	
	PlanContourNoir = 13,
	PlanContourBlanc = 12,
	PlanFondNoir = 11,
	PlanBtnRetourUp = 10,
	PlanBtnRetourDown = 9,
	PlanPersoUp = 8,
	PlanPersoDown = 7,
	PlanInfo = 6,
	PlanInfoModif = 5,
	PlanBtnValiderUp = 3,
	PlanBtnValiderDown = 2,
};


void ChampSelect();
void createCharactersSelect(int xBlock, int yBlock, int wBlock, int hBlock, int nbPerso, int nbPersoParLigne);
void generateAllDisplays();

// affiche les cases pour la champ select et les rends clickable
void createFieldsChampSelectInBlock(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, int * nbLines, int * nbColumns, int * sizeSideIm);

//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer et autorise de contraindre un des deux parametres
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbChara, int * nbLines, int * nbColumns, int * sizeSideIm);

// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbChara, int wBlock, int hBlock);

//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbChara, int * nbLines, int * nbColumns, int * sizeSideIm);

// affiche les blocs une fois quon connait le nombre de lignes et colonnes souhaitées
void displayBlocksInOptimizedPosition(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, int nbLines, int nbColumns, int sizeSideIm);



// menu stats
void createValidateInBlock(int, int, int, int);
void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock);
void createStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock);





/*
* Fonction : initChoicePerso
* Objectif : fonction de lancement du choix des perso
*/
void initChoicePerso();

/*
* Fonction : GenerateInfo
* Objectif : 
*/
void GenerateInfo(int idPerso, Element * txtinfo);

DataValidate * initDataValidate();

void ValiderDown(Element * valider, int i);

void ValiderUp(Element * valider, int i);

DataRetour * initDataRetour();

void RetourDown(Element * retour, int i);

void RetourUp(Element * retour, int i);

DataPerso * initDataPerso(int i);

void UnSelectPerso(Element * perso);

int WhoIsSelectedPerso(Element * valider);

void PersoDown(Element * perso, int i);

void PersoUp(Element * perso, int i);


#endif