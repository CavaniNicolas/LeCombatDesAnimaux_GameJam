
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

// struct du boutton "GO !" pour valider le choix du perso (data de lelement okButton de la struct StatsCharacter)
typedef struct okButton {
	int nbClick;

	int idCharaLeftPlayer;
	int idCharaRightPlayer;
}okButton_t;

// struct contenant les valeurs max possible des stats (lues dans un fichiers statsMax)
typedef struct StatsCharacterMax {
	int    hp;
	int    strength;
	double speed;
}StatsCharacterMax_t;

// struct pour les graphes pour afficher les stats des persos
typedef struct StatsGraphs {
	Element * hpBox;
	Element * strengthBox;
	Element * speedBox;

	Element * hp;
	Element * strength;
	Element * speed;
}StatsGraphs_t;

// struct des persos de la champ select
typedef struct StatsCharacter {
	int    idChara;
	int    hp;
	int    strength;
	double speed;

	Element * okButton;
	StatsGraphs_t * statsGraphs;
	StatsCharacterMax_t * statsMax;

	bool isSelected;
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


// actions a executer quand on clic sur un perso de la champ select
void onClickActionsChampSelect(Element * element, int i);

// affiche les stats des persos quand on clic dessus
void displayCharacterStats(Element * element);

// rempli la structure okButton avec l'id du perso choisi
void selectCharacter(Element * element);

// creer les blocks de stats pour les perso, qui seront a modifier lors d'un clic
StatsGraphs_t * initStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock);


// recupere les valeurs des stats des perso dans le fichier et rempli les structures StatsCharacter_t
StatsCharacter_t * getCharacterStatsInFile(FILE * file, int idChara);

// recupere les valeurs max des stats des perso et les stock dans une structure unique a tous les persos
StatsCharacterMax_t * getCharacterStatsMaxInFile();

// effectue des actions quand on clic sur "GO!" (valide les persos puis change de fenetre en liberant la memoire)
void charactersValidation(Element * okButton);


// menu stats
Element * createValidateInBlock(int, int, int, int);
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