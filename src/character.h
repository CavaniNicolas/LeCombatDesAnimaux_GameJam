#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef struct DataCharacter {
	int id;
	int hp;
	int strength;
	int speed;

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