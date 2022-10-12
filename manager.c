#include "manager.h"

int markov[NB_ROOM][NB_ROOM] = {
    {0, 33, 33, 33, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 12, 12, 16, 16, 16, 8, 8, 8, 4},
    {0, 12, 0, 12, 16, 16, 16, 8, 8, 8, 4},
    {0, 12, 12, 0, 16, 16, 16, 8, 8, 8, 4},
    {0, 7, 7, 7, 0, 6, 6, 17, 17, 17, 16},
    {0, 7, 7, 7, 6, 0, 6, 17, 17, 17, 16},
    {0, 7, 7, 7, 6, 6, 0, 17, 17, 17, 16},
    {0, 7, 7, 7, 10, 10, 10, 0, 15, 15, 19},
    {0, 7, 7, 7, 10, 10, 10, 15, 0, 15, 19},
    {0, 7, 7, 7, 10, 10, 10, 15, 15, 0, 19},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int ManagerProchaineSalle(int typeSalle) {
    int alpha = (rand() % 100) +1;
    int cumul = 0;
    int prochaineSalle;

    for(int i = 0; i < NB_ROOM; i++) {
        cumul += markov[typeSalle][i];
        if(alpha <= cumul) {
            prochaineSalle = i;
            break;
        }
    }
    return prochaineSalle;
}


int ManagerDeplacementJoueur(Entite_t * joueur, Salle_t * salle, Direction_t direction, int * salleCourante) {
    int xMax, yMax, xMin, yMin;
    int xPorte = salle->destination.x + (salle->destination.w/2) - (11*ZOOM);
    int aChangeDeSalle = 0;

    if((xPorte <= joueur->destination.x) && (joueur->destination.x <= xPorte+22*ZOOM - joueur->destination.w)) {
        yMin = salle->destination.y;
        yMax = salle->destination.y + salle->destination.h - SIZE_TILE;
    }
    else {
        yMin = salle->destination.y + SIZE_TILE;
        yMax = salle->destination.y + salle->destination.h - 2*SIZE_TILE;
    }

    if((salle->destination.y + SIZE_TILE <= joueur->destination.y) && (joueur->destination.y <= salle->destination.y + salle->destination.h - 2*SIZE_TILE)) {
        xMin = salle->destination.x + 5*ZOOM;
        xMax = salle->destination.x + salle->destination.w - 5*ZOOM - SIZE_TILE;
    }
    else {
        xMin = xPorte;
        xMax = xPorte + 22*ZOOM - SIZE_TILE;
    }

    switch(direction) {
        case HAUT:
            joueur->destination.y = (joueur->destination.y - PLAYER_SPEED <= yMin)?yMin:joueur->destination.y - PLAYER_SPEED;
            joueur->nextFrame.y = (joueur->frames.h)/2;
            if(joueur->destination.y <= salle->destination.y && (salle->nbEntitesVivantes == 0)) {
                *salleCourante = ManagerProchaineSalle(*salleCourante);
                aChangeDeSalle = 1;
            }
            break;
        case BAS:
            joueur->destination.y = (joueur->destination.y + PLAYER_SPEED >= yMax)?yMax:joueur->destination.y + PLAYER_SPEED;
            joueur->nextFrame.y = 0;
            break;
        case GAUCHE:
            joueur->destination.x = (joueur->destination.x - PLAYER_SPEED <= xMin)?xMin:joueur->destination.x - PLAYER_SPEED;
            joueur->nextFrame.y = 3*(joueur->frames.h)/4;
            break;
        case DROITE:
            joueur->destination.x = (joueur->destination.x + PLAYER_SPEED >= xMax)?xMax:joueur->destination.x + PLAYER_SPEED;
            joueur->nextFrame.y = (joueur->frames.h)/4;
            break;
        default:
            joueur->nextFrame.x = 0;
            break;
    }

    ManagerKillEnemies(joueur, salle);

    return aChangeDeSalle;
}


void ManagerKillEnemies(Entite_t * joueur, Salle_t * salle) {
    SDL_Rect intersect;
    for(int i = 0; i < salle->nbEntites; i++) {
        if((salle->entites)[i]->etat && SDL_IntersectRect(&(joueur->destination), &((salle->entites)[i]->destination), &intersect)) {
            (salle->entites)[i]->etat = MORT;
            salle->nbEntitesVivantes--;
        }
    }
}


void ManagerVictoire(SDL_Renderer * renderer, SDL_bool * game_over) {
    SDL_Texture * texture = IMG_LoadTexture(renderer, "sources/VictoryScreen/Pikatchoum.png");
    SDL_Rect dimTextures;
    SDL_Rect destination;

    SDL_QueryTexture(texture, NULL, NULL, &dimTextures.w, &dimTextures.h);

    destination.w = dimTextures.w * ZOOM;
    destination.h = dimTextures.h * ZOOM;
    destination.x = SCREEN_WIDTH - destination.w;
    destination.y = SCREEN_HEIGHT - destination.h;

    SDL_RenderCopy(renderer, texture, NULL, &destination);
    SDL_DestroyTexture(texture);

    *game_over = SDL_TRUE;
}
