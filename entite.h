#ifndef ENTITE_H
#define ENTITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"

/********************************************************/
/*  Enumeration des etats possibles d'un entite         */
/*  MORT = 0                                            */
/*  VIVANT = 1                                          */
/********************************************************/
typedef enum {
    MORT,
    VIVANT
} Etat_t;

typedef enum {
    SLIME,
    JOUEUR
} Type_t;

/************************************************************/
/*  Structure representant une entite                       */
/*  type :          type de l'entite                        */
/*                                                          */
/*  etat :          etat de l'entite (mort/vivant)          */
/*                                                          */
/*  spriteSheet :   pointeur sur la texture contenant les   */
/*                  frames de l'animation de l'entite       */
/*                                                          */
/*  frames :        pointeur sur le rectangle englobant     */
/*                  les frames de l'entite sur la texture   */
/*                                                          */
/*  nextFrame :     pointeur sur le rectangle englobant     */
/*                  la prochaine frame a etre affichee      */
/*                                                          */
/*  nbFrames :       nombre de frames dans une animation    */
/************************************************************/
typedef struct {
    Type_t          type;
    Etat_t          etat;
    SDL_Texture   * spriteSheet;
    SDL_Rect        frames,
                    nextFrame,
                    destination;
    int             nbFrames;
} Entite_t;


/************************************************************/
/*  Cree une entite                                         */
/*  ENTREES :                                               */
/*  renderer :      pointeur sur le renderer ou afficher    */
/*                  l'entite                                */
/*                                                          */
/*  type :          type de l'entite                        */
/*                                                          */
/*  x, y :          coordonnees de l'entite dans le jeu     */
/*                                                          */
/*  SORTIE : pointeur sur l'entite creee                    */
/************************************************************/
Entite_t * EntiteCreate(SDL_Renderer * renderer, Type_t type, int x, int y);


/************************************************************/
/*  Detruit une entite                                      */
/*  ENTREE :                                                */
/*  entite :        pointeur sur l'entite a detruire        */
/************************************************************/
void EntiteDestroy(Entite_t * entite);


/************************************************************/
/*  Mets a jour la prochaine frame de l'entite              */
/*  ENTREE :                                                */
/*  entite :        pointeur sur l'entite a mettre a jour   */
/************************************************************/
void frameSuivante(Entite_t * entite);


/************************************************************/
/*  Affiche une entite                                      */
/*  ENTREES :                                               */
/*  window :        pointeur sur la fenetre ou afficher     */
/*                  l'entite                                */
/*                                                          */
/*  renderer :      pointeur sur le renderer qui affichera  */
/*                  l'entite                                */
/*                                                          */
/*  entite :        pointeur sur l'entite a afficher        */
/************************************************************/
void EntiteDisplay(SDL_Renderer * const renderer, Entite_t * const entite);

#endif //ENTITE_H
