/* -------------------------------------------------------------------------- */
/* Nom du fichier : animations.h                                              */
/* Objectifs : Déclarations des fonctions pour les animations                 */
/* Fonctions :                                                                */
/*  - createCharacterAnimations                                               */
/*  - charactersAnimation                                                     */
/*  - endAnimationActions                                                     */
/*  - getCurrentSprite                                                        */
/* -------------------------------------------------------------------------- */

#ifndef ANIM_H
#define ANIM_H


/* -------------------------------------------------------------------------- */
/* enum Animations                                                            */
/*       Enumeration des codes des animations                                 */
/* -------------------------------------------------------------------------- */
enum Animations {
	standing = 0,
	moving = 1,
	jumping = 2,
	attacking1 = 3,
	parrying = 4,
	attacking2 = 5,
	dying_reviving = 6
};


/* -------------------------------------------------------------------------- */
/* createCharacterAnimations                                                  */
/*       Creer les différentes animations du personnage                       */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void createCharacterAnimations(Element * character);


/* -------------------------------------------------------------------------- */
/* charactersAnimation                                                        */
/*       Lance la bonne animation à l'écran en fonction des actions           */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void charactersAnimation(Element * character);


/* -------------------------------------------------------------------------- */
/* endAnimationActions                                                        */
/*       Actions à effectuer lorsqu'une animation se termine                  */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*            code (int)            : code de l'animation qui se termine      */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void endAnimationActions(Element * character, int code);


/* -------------------------------------------------------------------------- */
/* getCurrentSprite                                                           */
/*       Retourne le numero de la sprite affichée actuellement                */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
int getCurrentSprite(Element * character);


#endif
