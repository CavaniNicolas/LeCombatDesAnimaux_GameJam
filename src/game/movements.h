

#ifndef MOVEM_H
#define MOVEM_H

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


void collisionCharacters(Element *);

#endif
