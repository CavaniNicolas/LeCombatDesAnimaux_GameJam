
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "structure.h"
#include "character.h"


void initCharacter(int idPlayer, int idPerso, Element ** character) {
	DataCharacter_t * d = initDataCharacter(idPlayer, idPerso);
	double x = 0;
	double y = 0;
	char filename[50];
	double groundLevel = HFEN-50-(d->height);

	if (!getCharactersFilename(idPerso, filename)) {
		printf("Error fetching character's filename\n");
	} else {

		if (d != NULL) {

			if (idPlayer == JOUEUR_G) {
				x = 100;
				y = groundLevel;
			} else { // JOUEUR_D
				x = LFEN-100-(d->width);
				y = groundLevel;
			}

			(*character) = createImage(x, y, d->width, d->height, filename, ECRAN_FIGHT, 0);

			if (idPlayer == JOUEUR_D) {
				(*character)->flip = SANDAL2_FLIP_HOR;
			}

			(*character)->data = d;
		}
	}
}


DataCharacter_t * initDataCharacter(int idPlayer, int idChosen) {
	DataCharacter_t * d = malloc(sizeof(DataCharacter_t));

	if (d != NULL) {

		FILE * file = NULL;
		file = fopen("assets/stats/DataCharacters.txt", "r");

		if (file != NULL) {

			int idPerso = -1;
			char ligne[6];

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

			while (!feof(file) && idPerso != idChosen) {
				fgets(ligne, 6, file);
				idPerso = atoi(ligne);
			}
			d->idPerso = idPerso;

			fgets(ligne, 6, file);
			d->hp = atoi(ligne);

			fgets(ligne, 6, file);
			d->strength = atoi(ligne);

			fgets(ligne, 6, file);
			d->speed = atoi(ligne);

			fgets(ligne, 6, file);
			d->width = atoi(ligne);

			fgets(ligne, 6, file);
			d->height = atoi(ligne);

			fgets(ligne, 6, file);
			d->jumpForce = atoi(ligne);
			d->jumpForceTmp = d->jumpForce;

			fgets(ligne, 6, file);
			d->jumpLag = atoi(ligne);
		}

		fclose(file);
	}

	return d;
}


int getCharactersFilename(int idPerso, char filename[50]) {
	int error = 1;
	DIR * rep = opendir("./assets/characters");
	char filenameTmp[30] = "c_.png";

	if (rep != NULL) {
		struct dirent * ent = NULL;

		while ((ent = readdir(rep)) != NULL) {
			if (ent->d_name[1] - 48 == idPerso) {
				strcpy(filenameTmp, ent->d_name);
			}
		}

		if (filenameTmp[1] == '_') {
			error = 0;
		}

		snprintf(filename, 50, "./assets/characters/%s", filenameTmp);

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
			if (d->idPlayer == JOUEUR_G  && d->allowLeft == true) {
 				d->left = true;
			}
			break;

		case 'd':
			if (d->idPlayer == JOUEUR_G && d->allowRight == true) {
				d->right = true;
			}
			break;

		case 's':
			if (d->idPlayer == JOUEUR_G) {
				if (d->jump == false && d->allowJump == true) {
					d->jump = true;
				}
			}
			break;


		case 'j':
			if (d->idPlayer == JOUEUR_D && d->allowLeft == true) {
 				d->left = true;
 			}
			break;

		case 'l':
			if (d->idPlayer == JOUEUR_D  && d->allowRight == true) {
				d->right = true;
			}
			break;

		case 'k':
			if (d->idPlayer == JOUEUR_D) {
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
			if (d->idPlayer == JOUEUR_G) {
 				d->left = false;
			}
			break;

		case 'd':
			if (d->idPlayer == JOUEUR_G) {
				d->right = false;
			}
			break;


		case 'j':
			if (d->idPlayer == JOUEUR_D) {
 				d->left = false;
 			}
			break;

		case 'l':
			if (d->idPlayer == JOUEUR_D) {
				d->right = false;
			}
			break;
	}
}


void moveCharacter(Element * character) {
	DataCharacter_t * d = character->data;

	double speed = (d->speed)/8;
	double groundLevel = HFEN-50-(d->height);

	if (d->left) {
		if ((character->x)-speed > 0)
			moveElement(character, -speed, 0);
	}

	if (d->right) {
		if ((character->x)-speed < LFEN-(d->width))
			moveElement(character, speed, 0);
	}

	// si on appuye sur sauter et que on est en l'air
	// alors deplacer le perso
	if (d->jump == true) {
		if (character->y - d->jumpForceTmp + GRAVITY < groundLevel) {
			character->y -= (d->jumpForceTmp + GRAVITY);
			d->jumpForceTmp -= GRAVITY;
		}
	// sinon, on appuye sur sauter mais on est plus en l'air
	// se positionner au niveau du sol
	// attendre un peu avant de resauter
		else {
			character->y = groundLevel;
			d->jump = false;
			d->jumpForceTmp = d->jumpForce;
			d->allowJump = false;
			d->jumpLagTmp = SDL_GetTicks();
		}
	}

	// jumpLag
	if(d->allowJump == false)
	{
		if ((int)SDL_GetTicks() - d->jumpLagTmp > d->jumpLag) {
			d->allowJump = true;
			puts("jump again");
		}
	}

}
