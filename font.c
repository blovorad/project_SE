#include "font.h"

/**
 * \file font.c
 * \author Gautier Levesque
 * \brief fichier source qui contient les fonctions pour la gestion des polices de caracteres
 */

SDL_bool BL_init_font(TTF_Font **font, const char *chemin, int size){

	*font = TTF_OpenFont(chemin, size);

	if(*font == NULL){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

void BL_clean_font(TTF_Font **font){

	if(*font != NULL){
		
		TTF_CloseFont(*font);
		*font = NULL;
	}	
}