#include "salle.h"

void SalleDestroy(Salle_t * salle){
	SDL_DestroyTexture(salle->texture);
	for (int i=0; i<salle->nbEntites; i++){
		EntiteDestroy((salle->entites)[i]);
	}
	free(salle);
}

Salle_t* SalleCreate(SDL_Renderer * renderer, int id, int nbCellWidth, int nbCellHeight, SDL_Texture * texture, int population[NB_TYPE_POPULATION]){
	

	Salle_t* salle = (Salle_t*)malloc(sizeof(Salle_t));
	salle->id = id;

	salle->nbCellWidth = nbCellWidth;
	salle->nbCellHeight = nbCellHeight;

	salle->texture = texture;

	SDL_Rect source = {0};
	SDL_QueryTexture(salle->texture, NULL, NULL, &source.w, &source.h);
	salle->destination.w = source.w*ZOOM;
	salle->destination.h = source.h*ZOOM;
	salle->destination.x = (SCREEN_WIDTH-salle->destination.w)/2;
	salle->destination.y = (SCREEN_HEIGHT-salle->destination.h)/2;
	
	salle->spawn.x = salle->destination.x + salle->destination.w/2 - SIZE_TILE/2;
	salle->spawn.y = salle->destination.y + salle->destination.h - SIZE_TILE;
	salle->spawn.w = 0;
	salle->spawn.h = 0;

	salle->nbEntites = 0;
	int x, y;
	for (int i=0; i<NB_TYPE_POPULATION; i++){
		for (int j=0; j<population[i]; j++){
			x = salle->destination.x + 5*ZOOM + (rand() % (salle->destination.w - 10*ZOOM - SIZE_TILE));
			y = salle->destination.y + SIZE_TILE + (rand() % (salle->destination.h/2));
			(salle->entites)[salle->nbEntites]=EntiteCreate(renderer, i, x, y);
			salle->nbEntites++;
			if (salle->nbEntites>NB_MAX_ENTITES){
				fprintf(stderr, "Plus d'entités créées que de place disponibles !\n");
				exit(1);
			}
		}
	}
	salle->nbEntitesVivantes = salle->nbEntites;

	return salle;
}

void SalleDisplay(SDL_Renderer *renderer, Salle_t const * const salle){
	SDL_Rect source = {0};
	SDL_QueryTexture(salle->texture, NULL, NULL, &source.w, &source.h);
	SDL_RenderCopy(renderer, salle->texture, &source, &(salle->destination));

	for (int i=0 ; i<salle->nbEntites ; i++){
		if ((salle->entites)[i]->etat == VIVANT){
			EntiteDisplay(renderer, salle->entites[i]);
		}
	}
}

void SalleCharger(SDL_Renderer * renderer, Salle_t ***salles){
	*salles = (Salle_t**)malloc(NB_ROOM*sizeof(Salle_t*));
	SDL_Texture * texture;

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_4x5_Grise.png");
	int population0[NB_TYPE_POPULATION] = {0}; 
	(*salles)[0] = SalleCreate(renderer, 0, 4, 5, texture, population0);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_8x8_Rouge.png");
	int population1[NB_TYPE_POPULATION] = {2}; 
	(*salles)[1] = SalleCreate(renderer, 1, 8, 8, texture, population1);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_8x8_Bleu.png");
	int population2[NB_TYPE_POPULATION] = {2}; 
	(*salles)[2] = SalleCreate(renderer, 2, 8, 8, texture, population2);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_8x8_Jaune.png");
	int population3[NB_TYPE_POPULATION] = {2}; 
	(*salles)[3] = SalleCreate(renderer, 3, 8, 8, texture, population3);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_12x11_Rouge.png");
	int population4[NB_TYPE_POPULATION] = {4}; 
	(*salles)[4] = SalleCreate(renderer, 4, 12, 11, texture, population4);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_12x11_Bleu.png");
	int population5[NB_TYPE_POPULATION] = {4}; 
	(*salles)[5] = SalleCreate(renderer, 5, 12, 11, texture, population5);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_12x11_Jaune.png");
	int population6[NB_TYPE_POPULATION] = {4}; 
	(*salles)[6] = SalleCreate(renderer, 6, 12, 11, texture, population6);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_16x14_Rouge.png");
	int population7[NB_TYPE_POPULATION] = {7}; 
	(*salles)[7] = SalleCreate(renderer, 7, 16, 14, texture, population7);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_16x14_Bleu.png");
	int population8[NB_TYPE_POPULATION] = {7}; 
	(*salles)[8] = SalleCreate(renderer, 8, 16, 14, texture, population8);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_16x14_Jaune.png");
	int population9[NB_TYPE_POPULATION] = {7}; 
	(*salles)[9] = SalleCreate(renderer, 9, 16, 14, texture, population9);

	texture = IMG_LoadTexture(renderer, "sources/Salles/Salle_20x17_Rose.png");
	int population10[NB_TYPE_POPULATION] = {15}; 
	(*salles)[10] = SalleCreate(renderer, 10, 20, 17, texture, population10);
}

void SalleDestroyAll(Salle_t * salles[NB_ROOM]){
	for (int i =0; i<NB_ROOM; i++){
		SalleDestroy(salles[i]);
	}
	free(salles);
}
