#ifndef SALLE_H
#define SALLE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "entite.h"


typedef struct{
	int id;
	int nbCellWidth;
	int nbCellHeight;
	Entite_t* entites[NB_MAX_ENTITES];
	int nbEntites;
	int nbEntitesVivantes;
	SDL_Texture * texture;
	SDL_Rect spawn;
	SDL_Rect destination;
} Salle_t;


void SalleDestroy(Salle_t * salle);

Salle_t* SalleCreate(SDL_Renderer * renderer, int id, int nbCellWidth, int nbCellHeight, SDL_Texture * texture, int population[NB_TYPE_POPULATION]);

void SalleDisplay(SDL_Renderer *renderer, Salle_t const * const salle);

void SalleCharger(SDL_Renderer * renderer, Salle_t ***salles);

void SalleDestroyAll(Salle_t *salles[NB_ROOM]);

#endif //SALLE_H
