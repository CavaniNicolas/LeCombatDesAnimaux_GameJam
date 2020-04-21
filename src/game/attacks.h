/* -------------------------------------------------------------------------- */
/* Nom du fichier : attacks.h                                                 */
/* Objectifs : Déclarations des fonctions pour le combat                      */
/* Fonctions :                                                                */
/*  - launchCharacterAttack                                                   */
/* -------------------------------------------------------------------------- */

#ifndef ATTACKS_H
#define ATTACKS_H


/* -------------------------------------------------------------------------- */
/* launchCharacterAttack                                                      */
/*       Lance une attaque si la touche est appuyée et que le perso est       */
/*       autorisé à attaquer, lors d'une attaque les déplacements ne sont pas */
/*       possibles                                                            */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void launchCharacterAttack(Element * character);


#endif
