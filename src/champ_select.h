
#ifndef CHAMPSELECT_H
#define CHAMPSELECT_H
#include <stdbool.h>


/*********************** CHAMP_SELECT ******************************/

enum PlanChampSelect {
	PlanBackgroundCS = 99,

	PlanBlock = 89,

	PlanChampSelect = 79,
	PlanStatsGraphsBackground = 71,
	PlanStatsGraphs = 70,


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


typedef struct StatsCharacterMax {
	int    hp;
	int    strength;
	double speed;
}StatsCharacterMax_t;

typedef struct StatsGraphs {
	Element * hpBox;
	Element * strengthBox;
	Element * speedBox;

	Element * hp;
	Element * strength;
	Element * speed;
}StatsGraphs_t;

typedef struct StatsCharacter {
	int    idChara;
	int    hp;
	int    strength;
	double speed;

	StatsGraphs_t * statsGraphs;
	StatsCharacterMax_t * statsMax;

	bool isClicked;
	//bool isSelected;
}StatsCharacter_t;


void ChampSelect();

void generateAllDisplays();

// verifie si il y a suffisament d'assets dans le repertoire pour creer les perso de la champSelect
int checkIfnbCharaIsCorrect(int nbChara);

// affiche les cases pour la champ select et les rends clickable
void createFieldsChampSelectInBlock(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm, int xGraph, int yGraph, int wGraph, int hGraph);

//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer et autorise de contraindre un des deux parametres
void setOptimizedLinesAndColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm);

// varCte, varAdapting : nombre de lignes ou de colonnes, l'une est fixe et détermine la valeur de l'autre
void setSecondVariable(int varCte, int * varAdapting, int * sizeSideIm, int nbChara, float fillPercent, int wBlock, int hBlock);

//calcul le nombre optimal de lignes et colonnes en fct du nombre total delements a placer
void optimizeNumberOfLinesColumns(int wBlock, int hBlock, int nbChara, float fillPercent, int * nbLines, int * nbColumns, int * sizeSideIm);

// affiche les blocs une fois quon connait le nombre de lignes et colonnes souhaitées
void displayBlocksInOptimizedPosition(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, int nbLines, int nbColumns, int sizeSideIm, int xGraph, int yGraph, int wGraph, int hGraph);


// passe la valeur de isClicked a true quand on clic sur lelement
void isClickedSetOn(Element * element, int idChara);

// affiche les stats des persos quand on clic dessus
void displayCharacterStats(Element * element);

// creer les blocks de stats pour les perso, qui seront a modifier lors d'un clic
StatsGraphs_t * initStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock);


// recupere les valeurs des stats des perso dans le fichier et rempli les structures StatsCharacter_t
StatsCharacter_t * getCharacterStatsInFile(FILE * file, int idChara);

// recupere les valeurs max des stats des perso et les stock dans une structure unique a tous les persos
StatsCharacterMax_t * getCharacterStatsMaxInFile();


// menu stats
void createValidateInBlock(int, int, int, int);
void validateCharacterChoice(Element * element, int i);

void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock);





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