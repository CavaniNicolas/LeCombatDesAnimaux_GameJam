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




/***************************** ECRAN_CHOIX_MAP ******************************/
/*
* Fonction : initChoiceMap
* Objectif : fonction de lancement du choix de la map
*/
void initChoiceMap(int indiceJoueur, int indiceJoueur2, Element * validerPerso);

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
