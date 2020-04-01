
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "../structure.h"
#include "character.h"


void initCharacter(int idPlayer, int idChara, Element ** character) {
	DataCharacter_t * d = initDataCharacter(idPlayer, idChara);
	double x = 0;
	double y = 0;
	char   filename[50];
	double groundLevel = HFEN-50-(d->height);

	if (!getCharactersFilename(idChara, filename)) {
		printf("Error fetching character's filename\n");
	} else {

		if (d != NULL) {

			if (idPlayer == PLAYER_L) {
				x = 100;
				y = groundLevel;
			} else { // PLAYER_R
				x = LFEN-100-(d->width);
				y = groundLevel;
			}

			(*character) = createImage(x, y, d->width, d->height, filename, FIGHT_SCREEN, 0);
			createCharacterAnimations(*character);

			if (idPlayer == PLAYER_R) {
				(*character)->flip = SANDAL2_FLIP_HOR;
			}

			(*character)->data = d;
		}
	}
}


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


DataCharacter_t * initDataCharacter(int idPlayer, int idChosen) {
	DataCharacter_t * d = malloc(sizeof(DataCharacter_t));

	if (d != NULL) {

		FILE * file = NULL;
		file = fopen("assets/stats/DataCharacters.txt", "r");

		if (file != NULL) {

			int idChara = -1;
			char line[6];

			d->idPlayer = idPlayer;

			d->left       = false;
			d->allowLeft  = false;
			d->right      = false;
			d->allowRight = false;
			d->jump       = false;
			d->allowJump  = true;
			d->crouch     = false;

			d->attack1 = false;
			d->attack2 = false;
			d->parry1  = false;
			d->parry2  = false;

			while (!feof(file) && idChara != idChosen) {
				fgets(line, 6, file);
				idChara = atoi(line);
			}
			d->idChara = idChara;

			fgets(line, 6, file);
			d->hp = atoi(line);

			fgets(line, 6, file);
			d->strength = atoi(line);

			fgets(line, 6, file);
			d->speed = atoi(line);

			fgets(line, 6, file);
			d->width = atoi(line);

			fgets(line, 6, file);
			d->height = atoi(line);

			fgets(line, 6, file);
			d->jumpForce = atoi(line);
			d->jumpForceTmp = d->jumpForce;

			fgets(line, 6, file);
			d->jumpLag = atoi(line);
		}

		fclose(file);
	}

	return d;
}


int getCharactersFilename(int idChara, char filename[50]) {
	int error = 1;
	DIR * rep = opendir("./assets/sprites");
	char filenameTmp[30] = "s_.png";

	if (rep != NULL) {
		struct dirent * ent = NULL;

		while ((ent = readdir(rep)) != NULL) {
			if (ent->d_name[1] - 48 == idChara) {
				strcpy(filenameTmp, ent->d_name);
			}
		}

		if (filenameTmp[1] == '_') {
			error = 0;
		}

		snprintf(filename, 50, "./assets/sprites/%s", filenameTmp);

		closedir(rep);
	} else {
		error = 0;
	}
	return error;
}


void moveCharacterOn(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	switch (k) {
		case 'q':
			if (d->idPlayer == PLAYER_L  && d->allowLeft == true) {
 				d->left = true;
			}
			break;

		case 'd':
			if (d->idPlayer == PLAYER_L && d->allowRight == true) {
				d->right = true;
			}
			break;

		case 's':
			if (d->idPlayer == PLAYER_L) {
				if (d->jump == false && d->allowJump == true) {
					d->jump = true;
				}
			}
			break;


		case 'j':
			if (d->idPlayer == PLAYER_R && d->allowLeft == true) {
 				d->left = true;
 			}
			break;

		case 'l':
			if (d->idPlayer == PLAYER_R  && d->allowRight == true) {
				d->right = true;
			}
			break;

		case 'k':
			if (d->idPlayer == PLAYER_R) {
				if (d->jump == false && d->allowJump == true) {
					d->jump = true;
				}
			}
			break;
	}
}

void moveCharacterOff(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	switch (k) {
		case 'q':
			if (d->idPlayer == PLAYER_L) {
 				d->left = false;
			}
			break;

		case 'd':
			if (d->idPlayer == PLAYER_L) {
				d->right = false;
			}
			break;


		case 'j':
			if (d->idPlayer == PLAYER_R) {
 				d->left = false;
 			}
			break;

		case 'l':
			if (d->idPlayer == PLAYER_R) {
				d->right = false;
			}
			break;
	}
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



void moveCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double speed = (d->speed)/8;

	if (d->left) {
		if ((character->x)-speed > 0)
			moveElement(character, -speed, 0);
	}

	if (d->right) {
		if ((character->x)-speed < LFEN-(d->width))
			moveElement(character, speed, 0);
	}
}


void jumpCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double groundLevel = HFEN-50-(d->height);
	// ajouter la gravite propre a un perso

	// si autorisation de sauter (au sol ou en l'air)
	// alors deplacer le perso
	if (d->jump == true) {

		if (character->y - d->jumpForceTmp + GRAVITY < groundLevel) {
			character->y -= (d->jumpForceTmp + GRAVITY);
			d->jumpForceTmp -= GRAVITY;
		}
	// sinon, d->jump==true mais on est plus en l'air
	// se positionner au niveau du sol
	// attendre un peu avant de resauter
		else {
			character->y = groundLevel;
			d->jump = false;
			d->jumpForceTmp = d->jumpForce;
			d->jumpLagTmp = SDL_GetTicks();
		}
	}

	// jumpLag
	if(d->allowJump == false && d->jump == false) {
		if ((int)SDL_GetTicks() - d->jumpLagTmp >= d->jumpLag) {
			d->allowJump = true;
			puts("jump again");
		}
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
