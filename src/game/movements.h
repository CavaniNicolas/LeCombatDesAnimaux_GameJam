

#ifndef MOVEM_H
#define MOVEM_H

/* -------------------------------------------------------------------------------- */
/* moveCharacterOn   Active les booléens autorisant le déplacement                  */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void moveCharacterOn(Element *);


/* -------------------------------------------------------------------------------- */
/* moveCharacterOff   Desactive les booléens autorisant le déplacement              */
/*                                                                                  */
/* En entrée:  character : Element *, personnage                                    */
/*                                                                                  */
/* En sortie:  void                                                                 */
/* -------------------------------------------------------------------------------- */
void moveCharacterOff(Element *);


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
