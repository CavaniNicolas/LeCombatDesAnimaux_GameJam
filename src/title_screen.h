#ifndef TITLESCREEN_H
#define TITLESCREEN_H

/******************** ECRAN_TITRE ***********************************/

enum PlanMenuStart {
	PlanBackground = 5,
	PlanTextBack = 4,
	PlanTextMain = 3,
	PlanTextFront = 2,
	PlanCurtains = 1,
};

/*
* Fonction : Launcher
* Objectif : fonction de lancement du jeu
*/
void Launcher();

/*
* Fonction : moveCurtainLeft
* Objectif : déplace le rideau 1 (celui de gauche)
*/
void moveCurtainLeft(Element * r1);

/*
* Fonction : moveCurtainRight
* Objectif : déplace le rideau 2 (celui de droite)
*/
void moveCurtainRight(Element * r2);

/*
* Fonction : zoomInTitle
* Objectif : aggrandit le titre
*/
void zoomInTitle(Element * titre);

/*
* Fonction : displayStartButton
* Objectif : Affiche le bouton Start
*/
void displayStartButton();

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

#endif
