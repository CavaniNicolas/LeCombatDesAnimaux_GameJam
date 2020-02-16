/*#include "musicV2.h"

ZIK * initZIK(char * nomFic)
{
  ZIK * mus = NULL;
  FILE * f = fopen(nomFic,"r");
  int i = 0;
  int nbl = 0;

  if(f)
  {
    nbl = count_nb_line(f);
    if(nbl)
    {
      mus = malloc(sizeof(ZIK));
      if(mus)
      {
        mus->song = malloc(nbl*sizeof(char *));
        if(mus->song)
        {
          mus->musique = NULL;
          mus->nb_musique = count_nb_line(f);
          mus->id_musique_courante = -1;
          for(i = 0; i < mus->nb_musique; i ++)
          {
            read_line(f,mus->song+i);
          }
        }
      }
    }
    fclose(f);
  }

  return mus;
}

void read_line(FILE * f, char ** s)
{
  char stock[255];
  int n = 0;

  if(f)
  {
    if(fgets(stock,255,f) == NULL) puts("Error fgets");
    n = strlen(stock);
    stock[n-1] = '\0';
    *s = malloc(sizeof(char)*n);
    for (int i = 0; i < n; i ++)
    {
      s[0][i] = stock[i];
    }
    s[0][n] = '\0';
  }
}

int count_nb_line(FILE * f)
{
  int i = 0;

  if(f)
  {
    while (feof(f) == 0)
    {
      if (fgetc(f) == '\n')
      {
         i++;
      }
    }
    fseek(f,0,SEEK_SET);
  }

  return i;
}

void go_music(ZIK * m, int i)
{
  if (m->id_musique_courante != i && -1 <= i && i < m->nb_musique)
  {
    if (i == -1)
    {
      Mix_FreeMusic(m->musique);
      m->musique = NULL;
      m->id_musique_courante = -1;
    }
    else
    {
      m->musique = Mix_LoadMUS(m->song[i]);
      Mix_PlayMusic(m->musique,-1);
      m->id_musique_courante = i;
    }
  }
}
*/