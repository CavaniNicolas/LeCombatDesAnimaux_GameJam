
#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

typedef struct HealthBar {
	Element * healthBar;
	Element * bubble1;
	Element * bubble2;
}HealthBar_t;


typedef struct KeyCodes {
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode jump;
	SDL_Keycode attack1;
	SDL_Keycode attack2;
	SDL_Keycode parry;
}KeyCodes_t;

typedef struct KeyPressed {
	bool left_P;
	bool right_P;
	bool jump_P;
	bool attack1_P;
	bool parry_P;
	bool attack2_P;
}KeyPressed_t;

typedef struct DataCharacter {
	int    idChara;
	int    width;
	int    height;

	int    hpCte;
	int    strengthCte;
	double speedCte;
	int    jumpForceCte;
	int    jumpLagCte;

	int    hp;
	int    speed;
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

	bool   attacks;
	bool   allowAttacks;

	bool   attack1;
	bool   attack2;
	bool   parry;

	KeyPressed_t * keyPressed;

	HealthBar_t * healthBar;
	int winNum;

	KeyCodes_t * keyCodes;
}DataCharacter_t;

/* ------------------------------------------------------------------------- */
/* keyPressed                                                                */
/*       Active les booléens de pression en fonction de la touche appuyée    */
/*                                                                           */
/* En entrée:  character : Element *, personnage                             */
/*             k         : SDL_Keycode, touche clavier (pression utilisée)   */
/*                                                                           */
/* En sortie:  void                                                          */
/* ------------------------------------------------------------------------- */
void keyPressed(Element *, SDL_Keycode);

/* -------------------------------------------------------------------------------- */
/* keyUnpressed Desactive les booléens de pression en fonction de la touche relachée*/
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*             k         : SDL_Keycode, touche clavier (relachement utilisé)        */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void keyUnpressed(Element *, SDL_Keycode);


void keyOnActions(Element *);
void keyOffActions(Element *);
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


//associe les touches claviers au bon personnage
void initKeyCodes(KeyCodes_t * kd, int idPlayer);

//init les KeyPressed a false
void initKeyPressed(KeyPressed_t * kp);

// affiche les barres de vie initiales
void initHealthBar(HealthBar_t * hb, int idPlayer);


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
