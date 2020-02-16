
#include <SANDAL2/SANDAL2.h>
#include <stdlib.h>
#include "structure.h"
#include "character.h"


DataCharacter_t * initDataCharacter(int idPlayer, int idChosen) {
	DataCharacter_t * d = malloc(sizeof(DataCharacter_t));

	if (d != NULL) {

		FILE * file = NULL;
		file = fopen("assets/DataCharacters.txt", "r");

		if (file != NULL) {

			int idPerso = -1;
			char ligne[6];

			d->idPlayer = idPlayer;

			d->limit   = false;
			d->left    = false;
			d->right   = false;
			d->jump    = false;
			d->crouch  = false;

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


void initCharacter(int idPlayer, int idPerso, Element ** character) {
	DataCharacter_t * d = initDataCharacter(idPlayer, idPerso);

	if (d != NULL) {
		switch (idPlayer) {
			case JOUEUR_G:
				(*character) = createImage(100, HFEN-50-(d->height), d->width, d->height, "assets/kingKrool.png", 0, PlanCharacter);
			break;

			case JOUEUR_D:
				(*character) = createImage(LFEN-100-(d->width), HFEN-50-(d->height), d->width, d->height, "assets/donkeyKong.png", 0, PlanCharacter);
				(*character)->flip = SANDAL2_FLIP_HOR;
			break;

				default:
			break;
		}
		(*character)->data = d;
	}
}


void moveCharacterOn(Element * character, SDL_Keycode k) {
	DataCharacter_t * d = character->data;
	switch (k) {
		case 'q':
			if (d->idPlayer == JOUEUR_G) {
 				d->left = true;
			}
			break;

		case 'd':
			if (d->idPlayer == JOUEUR_G && d->limit == false) {
				d->right = true;
			}
			break;

		case 's':
			if (d->idPlayer == JOUEUR_G) {
				if (d->jump == false) {
					d->jump = true;
				}
			}
			break;


		case 'j':
			if (d->idPlayer == JOUEUR_D && d->limit == false) {
 				d->left = true;
 			}
			break;

		case 'l':
			if (d->idPlayer == JOUEUR_D) {
				d->right = true;
			}
			break;

		case 'k':
			if (d->idPlayer == JOUEUR_D) {
				if (d->jump == false) {
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
		if (character->y - d->jumpForceTmp + GRAVITY < HFEN-50-(d->height)) {
			character->y -= (d->jumpForceTmp + GRAVITY);
			d->jumpForceTmp -= GRAVITY;
		}
	// sinon, on appuye sur sauter mais on est plus en l'air
	// se positionner au niveau du sol
	// attendre un peu avant de resauter
		else {
			character->y = HFEN-50-(d->height);

			// si on a finit dattendre :
			if (d->jumpLagTmp == 0) {
				jumpLag(character);

				d->jump = false;
				d->jumpForceTmp = d->jumpForce;
				puts("jump again");
			}
		}
	}

}


void jumpLag(Element * character) {
	DataCharacter_t * d = character->data;

	if (d->jumpLagTmp == 0) {
		d->jumpLagTmp = SDL_GetTicks();
	}
	else if ((int)SDL_GetTicks() - d->jumpLagTmp > d->jumpLag) {
		d->jump = false;
		d->jumpLagTmp = 0;
	}
}