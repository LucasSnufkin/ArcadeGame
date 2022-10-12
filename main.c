#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "salle.h"
#include "manager.h"
#define FREE freeMemory(window, renderer)


void freeMemory(SDL_Window * window, SDL_Renderer * renderer){
	if (renderer != NULL){
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (window != NULL){
		SDL_DestroyWindow(window);
		window = NULL;
	}
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;


//===================== INIT ====================

	srand(time(0));

	/* Initialisation de la SDL  + gestion de l'échec possible */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("Fenetre", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		SDL_Log("Error : SDL window creation - %s\n", SDL_GetError()); // échec de la création de la fenêtre
		FREE;
		SDL_Quit();                              // On referme la SDL       
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
		SDL_Log("Error : SDL renderer creation - %s\n", SDL_GetError());  // échec de la création du renderer
		FREE;
    	SDL_Quit();
    }

	IMG_Init(IMG_INIT_PNG);
	Salle_t ** salles;
	SalleCharger(renderer, &salles);
	int salleCourante = 0;
	Entite_t * joueur = EntiteCreate(renderer, JOUEUR, salles[salleCourante]->spawn.x, salles[salleCourante]->spawn.y);

//==================== BOUCLE ====================


	/* Normalement, on devrait ici remplir les fenêtres... */
	SDL_bool program_on = SDL_TRUE;
	SDL_bool game_over = SDL_FALSE;
	SDL_Event event;
	Direction_t direction;


	while (program_on){               
		direction = AUCUNE;            
		while (SDL_PollEvent(&event)){                 
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						program_on = SDL_FALSE;
						break;
					case SDLK_UP:
					case SDLK_z:
						direction = HAUT;
						break;
					case SDLK_DOWN:
					case SDLK_s:
						direction = BAS;
						break;
					case SDLK_LEFT:
					case SDLK_q:
						direction = GAUCHE;
						break;
					case SDLK_RIGHT:
					case SDLK_d:
						direction = DROITE;
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT :                        
				program_on = SDL_FALSE;                 
				break;
			default:                                  
				break;
			}
		}

		if(!game_over) {
			if(ManagerDeplacementJoueur(joueur, salles[salleCourante], direction, &salleCourante)) {
				joueur->destination.x = salles[salleCourante]->spawn.x;
				joueur->destination.y = salles[salleCourante]->spawn.y;
				for(int i = 0; i < salles[salleCourante]->nbEntites; i++) {
					(salles[salleCourante]->entites)[i]->etat = VIVANT;
				}
				salles[salleCourante]->nbEntitesVivantes = salles[salleCourante]->nbEntites;
			}
			SDL_RenderClear(renderer);
			SalleDisplay(renderer, salles[salleCourante]);
			EntiteDisplay(renderer, joueur);
			if(salleCourante == 10 && salles[salleCourante]->nbEntitesVivantes == 0)
				ManagerVictoire(renderer, &game_over);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(80);
	}
	
//==================== FIN ====================


	/* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
	SalleDestroyAll(salles);
	EntiteDestroy(joueur);
	IMG_Quit();
	FREE;
	SDL_Quit();                                // la SDL

	return 0;
}

