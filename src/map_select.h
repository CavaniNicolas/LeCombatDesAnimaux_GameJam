
#ifndef MAPSELECT_H
#define MAPSELECT_H

enum PlanMapSelect {
	PlanMapUp = 5,
	PlanMapDown = 4
};

typedef struct DataValidate2 {
	int verif;
	int indiceJoueur;
	int indiceJoueur2;
}DataValidate2;

typedef struct DataRetour {
	int verif;
}DataRetour;


typedef struct DataMap {
	int id;
	int verif;
	int isSelected;
}DataMap;


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
