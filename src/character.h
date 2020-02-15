#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef enum player {
	JOUEUR_D = 0,
	JOUEUR_G = 1
}player;

typedef struct DataCharacter {
	int id;
	int hp;
	int strength;

	bool left;
	bool right;
	bool jump;
	bool crouch;
	
	bool attack1;
	bool attack2;
	bool parry1;
	bool parry2;

}DataCharacter_t;

void initDataCharacter(int, Element *);
void initCharacter(int, Element *);

#endif