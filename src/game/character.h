/* -------------------------------------------------------------------------- */
/* Nom du fichier : character.h                                               */
/* Objectifs : Déclarations des fonctions pour le personnage                  */
/* Fonctions :                                                                */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/*  -                                             */
/* -------------------------------------------------------------------------- */

#ifndef CARA_H
#define CARA_H
#include <stdbool.h>

/* -------------------------------------------------------------------------- */
/* struct HealthBar (typedef HealthBar_t)                                     */
/*       healthBar : pointeur sur la barre de vie                             */
/*       bubble1   : pointeur sur la bulle de victoire 1                      */
/*       bubble2   : pointeur sur la bulle de victoire 2                      */
/* -------------------------------------------------------------------------- */
typedef struct HealthBar {
	Element * healthBar;
	Element * bubble1;
	Element * bubble2;
}HealthBar_t;

/* -------------------------------------------------------------------------- */
/* struct KeyCodes (typedef KeyCodes_t)                                       */
/*       left, right, jump, attack1, attack2, parry                           */
/* -------------------------------------------------------------------------- */
typedef struct KeyCodes {
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode jump;
	SDL_Keycode attack1;
	SDL_Keycode attack2;
	SDL_Keycode parry;
}KeyCodes_t;

/* -------------------------------------------------------------------------- */
/* struct KeyPressed (typedef KeyPressed_t)                                   */
/*  - Booléens, true si la touche est appuyée false si elle est relachée      */
/*       left_P, right_P, jump_P, attack1_P, attack2_P, parry_P               */
/* -------------------------------------------------------------------------- */
typedef struct KeyPressed {
	bool left_P;
	bool right_P;
	bool jump_P;
	bool attack1_P;
	bool parry_P;
	bool attack2_P;
}KeyPressed_t;

/* -------------------------------------------------------------------------- */
/* struct DataCharacter (typedef DataCharacter_t)                             */
/*  - accessible depuis l'element character->data                             */
/*    regroupe toutes les données d'un personnage                             */
/* -------------------------------------------------------------------------- */
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


/* -------------------------------------------------------------------------- */
/* keyPressed                                                                 */
/*       Active les booléens de pression en fonction de la touche appuyée     */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*            k  (SDL_Keycode)      : touche clavier (pression utilisée)      */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void keyPressed(Element *, SDL_Keycode);


/* -------------------------------------------------------------------------- */
/* keyUnpressed                                                               */
/*       Desactive les booléens de pression en fonction de la touche relachée */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*            k  (SDL_Keycode)      : touche clavier (relachement utilisé)    */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void keyUnpressed(Element *, SDL_Keycode);


/* -------------------------------------------------------------------------- */
/* keyOnActions                                                               */
/*       Actions à effectuer en fonctions des touches qui sont appuyées       */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void keyOnActions(Element *);


/* -------------------------------------------------------------------------- */
/* keyOffActions                                                              */
/*       Actions à effectuer en fonctions des touches qui sont relachées      */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void keyOffActions(Element *);


/* -------------------------------------------------------------------------- */
/* actionCharacters                                                           */
/*       Actions à appliquer en permanence au personnage                      */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void actionCharacters(Element * character);


/* -------------------------------------------------------------------------- */
/* initCharacter                                                              */
/*       Initialise le personnage                                             */
/*                                                                            */
/* En entrée: idPlayer (int) : id du joueur choisissant son perso             */
/*                             (gauche ou droite)                             */
/*            idChara  (int) : id du perso selectionné dans le menu           */
/*            character (Element **) : personnage                             */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void initCharacter(int, int, Element **);



/* -------------------------------------------------------------------------- */
/* initDataCharacter                                                          */
/*                                                                            */
/*       Initialise les data d'un personnage depuis le fichier data           */
/*       "assets/DataCharacters.txt"                                          */
/*                                                                            */
/* En entrée: idPlayer (int) : id du joueur choisissant son perso            */
/*                             (gauche ou droite)                            */
/*            idChosen (int) : id du perso selectionné dans le menu          */
/*                                                                            */
/* En sortie: d (DataCharacter_t *) : Pointeur sur la structure Data du perso*/
/* -------------------------------------------------------------------------- */
DataCharacter_t * initDataCharacter(int, int);


/* -------------------------------------------------------------------------- */
/* initKeyCodes                                                               */
/*       Remplie la structure KeyCodes avec les touches claviers              */
/*       correspondantes au personnage du joueur idPlayer                     */
/*                                                                            */
/* En entrée: kd (KeyCodes_t *) : pointeur sur la structure KeyCodes          */
/*            idPlayer (int)    : id du joueur choisissant son perso          */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void initKeyCodes(KeyCodes_t * kd, int idPlayer);


/* -------------------------------------------------------------------------- */
/* initKeyPressed                                                             */
/*       Initialise les booleens de la structure KeyPressed à false           */
/*                                                                            */
/* En entrée: kp (KeyPressed_t *) : pointeur sur la structure KeyPressed      */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void initKeyPressed(KeyPressed_t * kp);


/* -------------------------------------------------------------------------- */
/* initHealthBar                                                              */
/*       Initialise les barres de vie, affichage (barres, bulles de victoire, */
/*       logo du perso), pointeur sur la structure                            */
/*                                                                            */
/* En entrée: hb (HealthBar_t *) : pointeur sur la structure HealthBar        */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void initHealthBar(HealthBar_t * hb, int idPlayer);


/* -------------------------------------------------------------------------- */
/* getCharactersFilename                                                      */
/*       Récupère le nom du fichier de l'image du perso choisie               */
/*                                                                            */
/* En entrée: idChara  (int)      : perso choisi                              */
/*            filename (char[40]) : nom du fichier de l'image du perso choisi */
/*                                                                            */
/* En sortie: int, 1 si pas d'erreurs, 0 sinon                                */
/* -------------------------------------------------------------------------- */
int getCharactersFilename(int, char[40]);


#endif
