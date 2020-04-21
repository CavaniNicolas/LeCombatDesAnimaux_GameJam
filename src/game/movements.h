/* -------------------------------------------------------------------------- */
/* Nom du fichier : movements.h                                               */
/* Objectifs : Déclarations des fonctions pour les déplacements               */
/* Fonctions :                                                                */
/*  - moveCharacterOn                                                         */
/*  - moveCharacterOff                                                        */
/*  - moveCharacter                                                           */
/*  - jumpCharacter                                                           */
/*  - collisionCharacters                                                     */
/* -------------------------------------------------------------------------- */

#ifndef MOVEM_H
#define MOVEM_H

/* -------------------------------------------------------------------------- */
/* moveCharacterOn                                                            */
/*       Active les booléens autorisant le déplacement                        */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void moveCharacterOn(Element *);


/* -------------------------------------------------------------------------- */
/* moveCharacterOff                                                           */
/*       Desactive les booléens autorisant le déplacement                     */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void moveCharacterOff(Element *);


/* -------------------------------------------------------------------------- */
/* moveCharacter                                                              */
/*       Déplace le personnage en fonction des booléens d'autorisation        */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void moveCharacter(Element *);


/* -------------------------------------------------------------------------- */
/* jumpCharacter                                                              */
/*       Fait sauter le personnage en fonction du booléen d'autorisation      */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void jumpCharacter(Element * character);


/* -------------------------------------------------------------------------- */
/* collisionCharacters                                                        */
/*       Gère les collisions entre les deux personnages pour qu'ils ne se     */
/*       traversent pas                                                       */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void collisionCharacters(Element *);

#endif
