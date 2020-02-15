#ifndef __MUSICV2_H__
#define __MUSICV2_H__

#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  Mix_Music * musique;
  char ** song;
  int id_musique_courante;
  int nb_musique;
}ZIK;

ZIK * initZIK(char * nomFic);
void read_line(FILE * f, char ** s);
int count_nb_line(FILE * f);
void go_music(ZIK * m, int i);

#endif
