#include "init.h"

/**
 * \file init.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utiles a l'initialisation de la SDL et de tous les composants necessaires au fonctionnement du programme
 */

SDL_bool BL_init(BL_Window *window, BL_Graphics *graphics, BL_Input *input, BL_Mouse *mouse){

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){

		return SDL_FALSE;
	}

	if(BL_creat_windowRenderer("Systeme exploitation projet, Medhi Ouliana et Gautier", window) == SDL_FALSE){

		return SDL_FALSE;
	}

	//ON ACTIVE LA TRANSPARENCE
	if(SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND) != 0){

		SDL_Log("IMPOSSIBLE D'ACTIVER LA TRANSPARENCE :%s", SDL_GetError());
		return SDL_FALSE;
	}

	//ON INITIALISE LA LIBRAIRIE D'ECRITURE
	if(TTF_Init() != 0){

		SDL_Log("IMPOSSIBLE DE CHARGER TTF :%s", TTF_GetError());
		return SDL_FALSE;
	}

	if(BL_init_texture(window->renderer, graphics) == SDL_FALSE){

		return SDL_FALSE;
	}

	if(BL_init_input(input) == SDL_FALSE){

		return SDL_FALSE;
	}
	if(BL_init_mouse(mouse) == SDL_FALSE){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

void BL_clean(BL_Window *window, BL_Graphics *graphics, BL_Histogramme *histogramme){

	SDL_Log("ERROR : %s\n", SDL_GetError());

	BL_clean_texture(graphics);

	if(window->renderer != NULL){

		SDL_DestroyRenderer(window->renderer);
		window->renderer = NULL;
	}
	if(window->screen != NULL){

		SDL_DestroyWindow(window->screen);
		window->screen = NULL;
	}

	TTF_Quit();
	SDL_Quit();
}