#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef enum player {
	JOUEUR_D = 0,
	JOUEUR_G = 1
}player;

typedef struct DataCaracter {
	int id;
	int hp;
	bool left;
	bool right;
	bool jump;
	bool attack1;
	bool attack2;
	bool parry1;
	bool parry2;

}DataCaracter_t;

void initDataCaracter(int, Element *);
void initCaracter(int, Element *);

#endif