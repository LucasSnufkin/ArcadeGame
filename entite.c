#include "entite.h"
#include <stdlib.h>


Entite_t * EntiteCreate(SDL_Renderer * renderer, Type_t type, int x, int y) {
    Entite_t * entite = NULL;
    SDL_Texture * spriteSheet = NULL;
    int nbFrames = 0;

    entite = (Entite_t *)malloc(sizeof(Entite_t));

    entite->type = type;
    entite->etat = VIVANT;
    switch(type) {
        case SLIME:
            spriteSheet = IMG_LoadTexture(renderer, "sources/ThreeBasicSlimes/GreenSlimeMove.png");
            entite->nextFrame = (SDL_Rect){0, 0, 16, 16};
            nbFrames = 8;
            break;
        case JOUEUR:
            spriteSheet = IMG_LoadTexture(renderer, "sources/Player/Character.png");
            entite->nextFrame = (SDL_Rect){0, 32, 16, 16};
            nbFrames = 4;
        default:
            break;
    }

    entite->frames.x = entite->frames.y = 0;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &(entite->frames.w), &(entite->frames.h));

    entite->destination = (SDL_Rect){x, y, entite->nextFrame.w*ZOOM, entite->nextFrame.h*ZOOM};

    entite->spriteSheet = spriteSheet;
    entite->nbFrames = nbFrames;

    return entite;
}


void EntiteDestroy(Entite_t * entite) {
    SDL_DestroyTexture(entite->spriteSheet);
    free(entite);
}


void frameSuivante(Entite_t * entite) {
    entite->nextFrame.x = (entite->nextFrame.x + entite->nextFrame.w) % entite->frames.w;
}


void EntiteDisplay(SDL_Renderer * const renderer, Entite_t * const entite) {
    if(entite->etat == VIVANT) {
        SDL_RenderCopy(renderer, entite->spriteSheet, &(entite->nextFrame), &(entite->destination));
        frameSuivante(entite);
    }
}