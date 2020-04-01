
#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef struct DataCharacter {
	int    idChara;
	int    hp;
	int    strength;
	double speed;
	int    jumpLag;

	int    width;
	int    height;
	int    jumpForce;
	int    jumpForceTmp;
	int    jumpLagTmp;

	int    idPlayer;

	bool   left;
	bool   allowLeft;
	bool   right;
	bool   allowRight;
	bool   jump;
	bool   allowJump;
	bool   crouch;

	bool   attack1;
	bool   attack2;
	bool   parry1;
	bool   parry2;

}DataCharacter_t;


void initFight(int idCharacterG, int idCharacterD, int idMap);

void keyOnActions(Element *, SDL_Keycode);
void keyOffActions(Element *, SDL_Keycode);
void actionCharacters(Element * character);


/* -------------------------------------------------------------------------------- */
/* initCharacter      Initialise le personnage                                      */
/*                                                                                  */
/* En entrée:  idPlayer : int, id du joueur choisissant son perso (gauche ou droite)*/
/*             idChara  : int, id du perso selectionné dans le menu                 */
/*             character: Element ** , personnage                                   */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void initCharacter(int, int, Element **);



/* -------------------------------------------------------------------------------- */
/* initDataCharacter   Initialise les data d'un personnage depuis le fichier data   */
/*                     "assets/DataCharacters.txt"                                  */
/*                                                                                  */
/* En entrée:  idPlayer : int, id du joueur choisissant son perso (gauche ou droite)*/
/*             idChosen : int, id du perso selectionné dans le menu                 */
/*                                                                                  */
/* En sortie:  DataCharacter_t * :   Pointeur sur la structure Data du perso        */
/* -------------------------------------------------------------------------------- */
DataCharacter_t * initDataCharacter(int, int);


/* -------------------------------------------------------------------------------- */
/* getCharactersFilename   Récupère le nom du fichier de l'image du perso choisie   */
/*                                                                                  */
/* En entrée:  idChara  : int, perso choisi                                         */
/*             filename : char[40], nom du fichier de l'image du perso choisi       */
/*                                                                                  */
/* En sortie:  int, 1 si pas d'erreurs, 0 sinon                                     */
/* -------------------------------------------------------------------------------- */
int getCharactersFilename(int, char[40]);


#endif
