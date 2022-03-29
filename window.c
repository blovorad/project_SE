#include "window.h"

/**
 * \file window.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe l'implementation des fonctions utile a la gestion de fenetre en SDL
 */

SDL_bool BL_creat_windowRenderer(char *title, BL_Window *window){

	if(BL_search_file_in_Directory("./source/fichier", "config.CONFIG") == SDL_FALSE){

		if(BL_creat_configuration() == SDL_FALSE){

			return SDL_FALSE;
		}
	}

	FILE *fichier = fopen("./source/fichier/config.CONFIG", "rb");

	if(fichier == NULL){

		fprintf(stderr, "fopen; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	if(fread(&window->width, sizeof(unsigned int), 1, fichier) < 1){

		fprintf(stderr, "fread; %s\n", strerror(errno));
		return SDL_FALSE;
	}
	if(fread(&window->height, sizeof(unsigned int), 1, fichier) < 1){

		fprintf(stderr, "fread; %s\n", strerror(errno));
		return SDL_FALSE;
	}
	if(fread(&window->fullscreen, sizeof(SDL_bool), 1, fichier) < 1){

		fprintf(stderr, "fread; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	fclose(fichier);
	fichier = NULL;

	if(window->fullscreen){

		window->screen = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->width, window->height, SDL_WINDOW_FULLSCREEN);
	}
	else{

		window->screen = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->width, window->height, 0);
	}

	if(window->screen == NULL){

		return SDL_FALSE;
	}

	window->renderer = SDL_CreateRenderer(window->screen, -1, 0);

	if(window->renderer == NULL){

		return SDL_FALSE;
	}

	return SDL_TRUE;
}

SDL_bool BL_creat_configuration(void){

	FILE *fichier = fopen("./source/fichier/config.CONFIG", "wb");

	if(fichier == NULL){

		fprintf(stderr, "fopen; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	int width = BASE_SCREENWIDTH;
	int height = BASE_SCREENHEIGHT;
	SDL_bool fullscreen = 0;

	if(fwrite(&width, sizeof(int), 1, fichier) < 1){

		fprintf(stderr, "fwrite; %s\n", strerror(errno));
		return SDL_FALSE;
	}
	if(fwrite(&height, sizeof(int), 1, fichier) < 1){

		fprintf(stderr, "fwrite; %s\n", strerror(errno));
		return SDL_FALSE;
	}
	if(fwrite(&fullscreen, sizeof(SDL_bool), 1, fichier) < 1){

		fprintf(stderr, "fwrite; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	fclose(fichier);
	fichier = NULL;

	return SDL_TRUE;
}