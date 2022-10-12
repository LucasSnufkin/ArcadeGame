#ifndef MANAGER_H
#define MANAGER_H

#include "config.h"
#include "entite.h"
#include "salle.h"

typedef enum {
    AUCUNE,
    HAUT,
    BAS,
    GAUCHE,
    DROITE
} Direction_t;

int ManagerProchaineSalle(int typeSalle);

int ManagerDeplacementJoueur(Entite_t * joueur, Salle_t * salle, Direction_t direction, int * salleCourante);

void ManagerKillEnemies(Entite_t * joueur, Salle_t * salle);

void ManagerVictoire(SDL_Renderer * renderer, SDL_bool * game_over);

#endif //MANAGER_H
