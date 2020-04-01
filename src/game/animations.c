
#include <SANDAL2/SANDAL2.h>
#include <stdio.h>
#include "animations.h"


void createCharacterAnimations(Element * character) {
	int i=0;
	addAnimationElement(character, standing);

	for(i=0; i<5; i++)
		if(addSpriteAnimationElement(character, standing, 60 + 500*i, 40, 340, 380, 10, i))
			printf("Error adding sprite %d to animation %d\n", i, standing);

	setWaySpriteAnimationElement(character, standing, 1); 

	addAnimationElement(character, moving);
	for(i=0; i<8; i++)
		if(addSpriteAnimationElement(character, moving, 60 + 500*i, 540, 340, 380, 6, i))
			printf("Error adding sprite %d to animation %d\n", i, moving);
	setWaySpriteAnimationElement(character, moving, 1);

	addAnimationElement(character, jumping);
	for(i=0; i<8; i++)
		if(addSpriteAnimationElement(character, jumping, 60 + 500*i, 1050, 340, 380, 3, i))
			printf("Error adding sprite %d to animation %d\n", i, jumping);
	setWaySpriteAnimationElement(character, jumping, 1);
}


void charactersAnimation(Element * character) {
	DataCharacter_t * d = character->data;

	if (d->jump) {
		setAnimationElement(character, jumping);
		if (d->allowJump == true) {
			setSpriteAnimationElement(character, 0); /*commence tj lanimation par la premiere sprite*/
			d->allowJump = false; /*debut du saut, on ne peut plus resauter tant quon a pas atteri et attendu la fin du lag*/
		}

	} else if (d->left || d->right) {
		setAnimationElement(character, moving);

	} else {
		setAnimationElement(character, standing);
	}
}


// retourne le numero de la sprite affichée actuellement
int getCurrentSprite(Element * character) {
	int code = 0;

	if (character->animation != NULL && character->animation->current != NULL && character->animation->current->current != NULL) {
		code = character->animation->current->current->code;
	}
	return code;
}
