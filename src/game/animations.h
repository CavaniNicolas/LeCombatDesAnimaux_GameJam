

#ifndef ANIM_H
#define ANIM_H
#include <stdbool.h>
#include "character.h"

enum Animations {
	standing = 0,
	moving = 1,
	jumping = 2,
	attacking1 = 3,
	parrying = 4,
	attacking2 = 5
};
// set Animation with sprites to the element
void createCharacterAnimations(Element * character);

void charactersAnimation(Element * character);


// setting the behavior when an animation end
void endAnimationActions(Element * character, int code);


// retourne le numero de la sprite affichée actuellement
int getCurrentSprite(Element * character);

#endif
