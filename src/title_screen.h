#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include <stdbool.h>


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
	bool allowClick;

	Element * curtainLeft;
}DataStart;

/*
* Fonction : Launcher
* Objectif : fonction de lancement du jeu
*/
void Launcher();

// Ouvre les rideaux (et les supprime si on les ouvre lors de la transition des menus)
void openCurtains(Element * curtainLeft);

// Ferme les rideaux pour debuter une transition de menu
void closeCurtains(Element * curtainLeft);


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

// change color when hovering on/off start button
void hoverOnStartButton(Element * start);
void hoverOffStartButton(Element * start);

#endif
