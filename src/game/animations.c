
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

	addAnimationElement(character, attacking1);
	for(i=0; i<8; i++)
		if(addSpriteAnimationElement(character, attacking1, 60 + 500*i, 1550, 340, 380, 10, i))
			printf("Error adding sprite %d to animation %d\n", i, attacking1);
	setWaySpriteAnimationElement(character, attacking1, 1);

	addAnimationElement(character, parrying);
	for(i=0; i<8; i++)
		if(addSpriteAnimationElement(character, parrying, 60 + 500*i, 2050, 340, 380, 10, i))
			printf("Error adding sprite %d to animation %d\n", i, parrying);
	setWaySpriteAnimationElement(character, parrying, 1);


	/* setting the behavior when an animation end */
	setEndSpriteElement(character, endAnimationActions);
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

	} else if (d->attack1) {
		setAnimationElement(character, attacking1);

		if (d->allowAttacks == true) {
			setSpriteAnimationElement(character, 0); /*commence tj lanimation par la premiere sprite*/
			d->allowAttacks = false; /*debut du saut, on ne peut plus resauter tant quon a pas atteri et attendu la fin du lag*/
		}

	} else if (d->parry) {
		setAnimationElement(character, parrying);

		if (d->allowAttacks == true) {
			setSpriteAnimationElement(character, 0); /*commence tj lanimation par la premiere sprite*/
			d->allowAttacks = false; /*debut du saut, on ne peut plus resauter tant quon a pas atteri et attendu la fin du lag*/
		}

	} else {
		setAnimationElement(character, standing);
	}
}


void endAnimationActions(Element * character, int code) {
	DataCharacter_t * d = character->data;

	if (code == attacking1 || code == parrying || code == attacking2) {
		setAnimationElement(character, standing);

		// il est re possible de se deplacer
		d->allowJump = true;
		d->allowLeft = true;
		d->allowRight = true;

		// il est possible de reeffectuer un movement
		d->allowAttacks = true;

		// le mouvement est finit
		d->attacks = false;
		d->attack1 = false;
		d->parry = false;
		d->attack2 = false;
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
