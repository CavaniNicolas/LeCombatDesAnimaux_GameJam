#ifndef MENU_H
#define MENU_H

/*
* Projet Game Jam : Le combat des animaux
* Auteur : Théo Boucher, Nicolas Cavani
* menu
*
* Le menu contient plusieurs display
* Premièrement l'écran titre
*  fonctions : Launcher, depRideau1, depRideau2, aggrandissement, initDataStart, StartDown, StartUp
*/

/******************** ECRAN_TITRE ***********************************/
/*
* Fonction : Launcher
* Objectif : fonction de lancement du jeu
*/
void Launcher();

/*
* Fonction : depRideau1
* Objectif : déplace le rideau 1 (celui de gauche)
*/
void depRideau1(Element * r1);

/*
* Fonction : depRideau2
* Objectif : déplace le rideau 2 (celui de droite)
*/
void depRideau2(Element * r2);

/*
* Fonction : aggrandissement
* Objectif : aggrandit le titre
*/
void aggrandissement(Element * titre);

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

/***************************** ECRAN_CHOIX_PERSO ******************************/
/*
* Fonction : initChoicePerso
* Objectif : fonction de lancement du choix des perso
*/
void initChoicePerso(int indiceJoueur, Element * valider);

void GenerateInfo(int idPerso, Element * txtinfo);

DataValidate * initDataValidate(int indiceJoueur);

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

/***************************** ECRAN_CHOIX_MAP ******************************/
/*
* Fonction : initChoiceMap
* Objectif : fonction de lancement du choix de la map
*/
void initChoiceMap(int indiceJoueur, int indiceJoueur2);

void RetourDown2(Element * retour, int i);

void RetourUp2(Element * retour, int i);

DataValidate2 * initDataValidate2(int indiceJoueur, int indiceJoueur2);

void ValiderDown2(Element * valider, int i);

void ValiderUp2(Element * valider, int i);

DataMap * initDataMap(int i);

void UnSelectMap(Element * map);

int WhoIsSelectedMap(Element * valider);

void MapDown(Element * map, int i);

void MapUp(Element * map, int i);

#endif
