
#ifndef CHAMPSELECT_H
#define CHAMPSELECT_H
#include <stdbool.h>


enum PlanChampSelect {
	PlanBackgroundCS = 99,

	PlanBlock = 89,

	PlanChampSelect = 79,
	PlanStatsGraphsBackground = 71,
	PlanStatsGraphs = 70,

	PlanCharactersVersus = 59,

	PlanOkButton = 50,

};

// structure des 2 pointeurs sur les images afficher pour le Versus
typedef struct VersusImages {
	Element * leftChara;
	Element * rightChara;
}VersusImages_t;

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

	VersusImages_t * versusImages;
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

// affiche les blocs une fois quon connait le nombre de lignes et colonnes souhaitées
void displayBlocksInOptimizedPosition(int xBlock, int yBlock, int wBlock, int hBlock, int nbChara, int nbLines, int nbColumns, int sizeSideIm, int xGraph, int yGraph, int wGraph, int hGraph);


// actions a executer quand on clic sur un perso de la champ select
void onClickActionsChampSelect(Element * element, int i);

// affiche les stats des persos quand on clic dessus
void displayCharacterStats(Element * element);

// rempli la structure okButton avec l'id du perso choisi
void selectCharacter(Element * element);

// affiche le bon perso dans le versus
void displayCharacterVersus(VersusImages_t * versusImages, int idChara, int nbClick);

// creer les blocks de stats pour les perso, qui seront a modifier lors d'un clic
StatsGraphs_t * initStatsGraphs(int xBlock, int yBlock, int wBlock, int hBlock);

// init la structure des images du Versus
VersusImages_t * initVersusImages(int xBlock, int yBlock, int wBlock, int hBlock);


// recupere les valeurs des stats des perso dans le fichier et rempli les structures StatsCharacter_t
StatsCharacter_t * getCharacterStatsInFile(FILE * file, int idChara);

// recupere les valeurs max des stats des perso et les stock dans une structure unique a tous les persos
StatsCharacterMax_t * getCharacterStatsMaxInFile();

// effectue des actions quand on clic sur "GO!" (valide les persos puis change de fenetre en liberant la memoire)
void charactersValidation(Element * okButton);



// champ Grid
typedef struct charaGrid_t{
	int xInit;
	int wBlock;
}charaGrid_t;

// creer la grille de selection de characters, avec le fond qui change de couleur
void createCharacterGrid(int marge, int wCharBlock, int hBlock);
// fonction action, qui deplace le fond de la grille pour la faire changer de couleur
void changeGridColor(Element * charaGrid);


// menu stats
Element * createValidateInBlock(int, int, int, int);
void validateCharacterChoice(Element * element, int i);

void createStatsNames(int xBlock, int yBlock, int wBlock, int hBlock);


#endif
