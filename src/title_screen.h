#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include <stdbool.h>

/******************** ECRAN_TITRE ***********************************/

enum PlanMenuStart {
	PlanBackgroundTS = 5,
	PlanTextBack = 4,
	PlanTextMain = 3,

	PlanCurtains = 1,
};

typedef struct DataCurtain {
	bool isClosed;
	bool isMaxOpen;
	bool isFinished;
} DataCurtain_t;

typedef struct DataStart {
	bool isClicked;

	Element * curtainLeft;
	Element * curtainRight;
}DataStart;

/*
* Fonction : Launcher
* Objectif : fonction de lancement du jeu
*/
void Launcher();

/*
* Fonction : moveCurtainLeft
* Objectif : déplace le rideau 1 (celui de gauche)
*/
void moveLeftCurtainLeft(Element * r1);

/*
* Fonction : moveCurtainRight
* Objectif : déplace le rideau 2 (celui de droite)
*/
void moveRightCurtainRight(Element * r2);

/*
* Fonction : zoomInTitle
* Objectif : aggrandit le titre
*/
void zoomInTitle(Element * titre);

/*
* Fonction : initStartButton
* Objectif : Init le bouton Start
*/
Element * initStartButton();

/*
* Fonction : initDataStart
* Objectif : initialise la data du bouton start
*/
DataStart * initDataStart();

/*
* Fonction : StartDown
* Objectif : surligne le texte "start" en vert une fois le bouton pressé
*/
void StartDown(Element * start, int i);

/*
* Fonction : StartUp
* Objectif : lance le jeu une fois le bouton start relaché
*/
void StartUp(Element * start, int i);


// transition rideaux, recentre les rideaux puis les reéloigne en affichant le deuxieme menu
void moveLeftCurtainRight(Element * curtainLeft);
void moveRightCurtainLeft(Element * curtainLeft);


#endif
