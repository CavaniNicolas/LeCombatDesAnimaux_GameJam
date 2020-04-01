

#ifndef ANIM_H
#define ANIM_H
#include <stdbool.h>
#include "character.h"

enum Animations {
	standing = 0,
	moving = 1,
	jumping = 2
};
// set Animation with sprites to the element
void createCharacterAnimations(Element * character);

void charactersAnimation(Element * character);

// retourne le numero de la sprite affichée actuellement
int getCurrentSprite(Element * character);

#endif
