#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef struct DataCharacter {
	int    idPerso;
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


/* -------------------------------------------------------------------------------- */
/* initCharacter      Initialise le personnage                                      */
/*                                                                                  */
/* En entrée:  idPlayer : int, id du joueur choisissant son perso (gauche ou droite)*/
/*             idPerso  : int, id du perso selectionné dans le menu                 */
/*             character: Element ** , personnage                                   */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void initCharacter(int, int, Element **);


/////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////


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
/* En entrée:  idPerso  : int, perso choisi                                         */
/*             filename : char[40], nom du fichier de l'image du perso choisi       */
/*                                                                                  */
/* En sortie:  int, 1 si pas d'erreurs, 0 sinon                                     */
/* -------------------------------------------------------------------------------- */
int getCharactersFilename(int, char[40]);


/* -------------------------------------------------------------------------------- */
/* moveCharacterOn   Active les booléens autorisant le déplacement                  */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*             k         : SDL_Keycode, touche clavier (pression utilisée)          */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void moveCharacterOn(Element *, SDL_Keycode);


/* -------------------------------------------------------------------------------- */
/* moveCharacterOff   Desactive les booléens autorisant le déplacement              */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*             k         : SDL_Keycode, touche clavier (relachement utilisé)        */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void moveCharacterOff(Element *, SDL_Keycode);


/* -------------------------------------------------------------------------------- */
/* moveCharacter     Déplace le personnage en fonction des booléens d'autorisation  */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void moveCharacter(Element *);


/* -------------------------------------------------------------------------------- */
/* jumpCharacter   Fait sauter le personnage en fonction du booléen d'autorisation  */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void jumpCharacter(Element * character);

#endif