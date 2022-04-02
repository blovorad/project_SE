#include "timer.h"

/**
 * \file timer.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utiles a la gestion des timers
 */

SDL_bool BL_init_timer(BL_Timer *timer){

	timer->previousTime = SDL_GetTicks();
	timer->currentTime = 0;
	timer->ms = 0;

	return SDL_TRUE;
}
SDL_bool BL_update_timer(BL_Timer *timer, const int fps){

	timer->currentTime = SDL_GetTicks();
	timer->ms = timer->currentTime - timer->previousTime;
	timer->previousTime = SDL_GetTicks();
	 
	if(timer->ms < fps){
	    	
	   	 return SDL_FALSE;
	}

	return SDL_TRUE;
}