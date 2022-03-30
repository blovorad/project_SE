#include "color.h"

/**
 * \file color.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utiles a la gestion des couleurs
 */

SDL_Color BL_get_blanc(int alpha){

	SDL_Color blanc = {255,255,255,alpha};
	return blanc;
}

SDL_Color BL_get_rouge(int alpha){

	SDL_Color rouge = {255,0,0,alpha};
	return rouge;
}

SDL_Color BL_get_bleu(int alpha){

	SDL_Color bleu = {0,0,255,alpha};
	return bleu;
}

SDL_Color BL_get_vert(int alpha){

	SDL_Color vert = {0,255,0,alpha};
	return vert;
}

SDL_Color BL_get_vert_fonce(int alpha){

	SDL_Color vert = {0,100,0,alpha};
	return vert;
}

SDL_Color BL_get_gris(int alpha){

	SDL_Color gris = {100,100,100,alpha};
	return gris;
}

SDL_Color BL_get_jaune(int alpha){

	SDL_Color jaune = {255, 255, 0, alpha};
	return jaune;
}

SDL_Color BL_get_noir(int alpha){

	SDL_Color noir = {0,0,0,alpha};
	return noir;
}

SDL_Color BL_get_marron(int alpha){

	SDL_Color marron = {100,41,0,alpha};
	return marron;
}

SDL_Color BL_get_ocre(int alpha){

	SDL_Color ocre = {217, 208, 126, alpha};
	return ocre;
}

SDL_Color BL_get_orange(int alpha){
	
	SDL_Color orange = {255, 127, 0, alpha};
	return orange;
}