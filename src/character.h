#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef struct DataCharacter {
	int    idPerso;
	int    hp;
	int    strength;
	double speed;

	int    width;
	int    height;
	int    jumpForce;
	int    jumpForceTmp;

	int    idPlayer;

	bool   left;
	bool   right;
	bool   jump;
	bool   crouch;

	bool   attack1;
	bool   attack2;
	bool   parry1;
	bool   parry2;

}DataCharacter_t;

DataCharacter_t * initDataCharacter(int, int);
void initCharacter(int, int, Element *);


void moveCharacterOn(Element *, SDL_Keycode);
void moveCharacterOff(Element *, SDL_Keycode);
void moveCharacter(Element *);


#endif