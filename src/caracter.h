#ifndef CARA_H
#define CARA_H

typedef enum player {
	JOUEUR_D = 0,
	JOUEUR_G = 1
}player;

typedef struct DataCaracter {
	int id;
	int hp;
	int left;
	int right;
	int jump;
	int attack1;
	int attack2;
	int parry1;
	int parry2;

	Element * caracter;
}DataCaracter_t;

DataCaracter_t * initDataCaracter(int, Element *);
Element * initCaracter(int, Element *);

#endif