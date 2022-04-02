#ifndef __TIMER__H__
#define __TIMER__H__

#include "define.h"

/**
 * \file timer.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/define/structure utile a la gestion des timers
 */

/**
 * \struct BL_Timer timer.h
 * \brief structure pour la gestion du temps de la SDL
 */
typedef struct {

	int previousTime; /*!< temps precedent */
	int currentTime; /*!< temps courant */
	double ms; /*!< temps a ne pas depasser, en gros on fait currentTime - previousTime > ms, selon comment on veut reagir */

}BL_Timer;

/**
 * \fn SDL_bool BL_init_timer(BL_Timer *timer)
 * \author Gautier Levesque
 * \brief creation d'un timer
 * \param timer le timer a creer
 * \return boolean si l'initialisation du timer a echouer ou non, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_init_timer(BL_Timer *timer);

/**
 * \fn SDL_bool BL_update_timer(BL_Timer *timer, const int fps)
 * \author Gautier Levesque
 * \brief actualisation du timer, en gros on regarde le nouveau temps
 * \param timer le timer a actualiser/verifier
 * \param fps la valeur a ne pas depasser
 * \return boolean si la difference de l'ancien temps - nouveau temps est > a fps alors il renvoie SDL_FALSE pour qu'on fasse un arret car le programme va trop vite
 */
SDL_bool BL_update_timer(BL_Timer *timer, const int fps);

#endif
