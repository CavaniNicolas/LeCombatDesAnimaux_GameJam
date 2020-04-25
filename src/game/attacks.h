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


/* -------------------------------------------------------------------------- */
/* isCharacterInRange                                                         */
/*       Modifie le booléen inRange si les deux personnages sont à porté      */
/*       pour s'attaquer                                                      */
/*                                                                            */
/* En entrée: character (Element *) : personnage                              */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void isCharacterInRange(Element * character);


/* -------------------------------------------------------------------------- */
/* damageOpponent                                                             */
/*       Inflige des dégats à l'adversaire si une attaque à porté est lancée  */
/*                                                                            */
/* En entrée: characterAttacking (Element *) : personnage qui attaque         */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void damageOpponent(Element * characterAttacking);


/* -------------------------------------------------------------------------- */
/* showHealthBar                                                              */
/*       Redimmensionne la barre de PV après s'être pris un coup              */
/*                                                                            */
/* En entrée: characterHurt (Element *) : personnage qui est bléssé           */
/*                                                                            */
/* En sortie: void                                                            */
/* -------------------------------------------------------------------------- */
void showHealthBar(Element * characterHurt);

void adaptHealthBar(Element * character);

#endif
