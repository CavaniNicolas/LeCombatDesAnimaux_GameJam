#ifndef MENU_H
#define MENU_H

/*
* Projet Game Jam : Le combat des animaux
* Auteur : Théo Boucher, Nicolas Cavani
* menu
*
* Le menu contient plusieurs display
* Premièrement l'écran titre
*  fonctions : Launcher
*/

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

#endif
