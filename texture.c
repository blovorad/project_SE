#include "texture.h"

/**
 * \file texture.c
 * \author Gautier Levesque
 * \brief fichier source qui regroupe les fonctions utile a la gestion des textures
 */

SDL_bool BL_init_texture(SDL_Renderer *renderer, BL_Graphics *graphics){

	//on ouvre le directory
	DIR *directory = opendir("./source/graphics");
	if(directory == NULL){

		fprintf(stderr, "opendir; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	struct dirent *currentFile = readdir(directory);
	currentFile = readdir(directory);
	currentFile = readdir(directory);

	char cheminDirectory[200][256];
	int i = 0;
	SDL_bool noError = SDL_TRUE;

	//lecture et memorisation de chaque chemin d'une image qui est un png
	while(currentFile != NULL && noError == SDL_TRUE){

		char chemin[256] = {"./source/graphics/"};

		strcat(chemin, currentFile->d_name);
		SDL_RWops *img = SDL_RWFromFile(chemin, "rb");
		if(img == NULL){

			noError = SDL_FALSE;
		}

		if(IMG_isPNG(img) == 1){

			strcpy(cheminDirectory[i], chemin);
			i++;
		}

		currentFile = readdir(directory);
	}

	closedir(directory);
	directory = NULL;

	//allocation memoire et chargement de chaque texture trouver 1 par 1
	if(noError == SDL_TRUE){

		graphics->nbTexture = i;
		graphics->textures = NULL;
		if(i > 0){

			graphics->textures = malloc(sizeof(SDL_Texture*) * graphics->nbTexture);
			if(graphics->textures == NULL){

				fprintf(stderr, "malloc; %s\n", strerror(errno));
				return SDL_FALSE;
			}
			while(noError == SDL_TRUE && i < graphics->nbTexture){

				if(BL_create_texture(renderer, cheminDirectory[i], NULL, &graphics->textures[i]) == SDL_FALSE){

					noError = SDL_FALSE;
				}
				i++;
			}
		}
	}

	return noError;
}

SDL_bool BL_create_texture(SDL_Renderer *renderer, char *chemin, SDL_Rect *rect, SDL_Texture **textureDst){

	//Variable obligatoire pour créer une texture
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(chemin);

	//Controle si l'image a bien été charger dans la surface
	if(surface == NULL)	{

		SDL_Log("IMPOSSIBLE DE LOAD LA TEXTURE DANS LA SURFACE :%s", SDL_GetError());
		return SDL_FALSE;
	}
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	//fonction qui retourne la texture si elle est créer
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	//plus besoin de la surface, FREE OBLIGATOIRE
	SDL_FreeSurface(surface);
	surface = NULL;

	//On regarde si pas d'erreur
	if(texture == NULL){

		SDL_Log("IMPOSSIBLE DE CREATE TEXTURE POUR LA SURFACE :%s", SDL_GetError());
		return SDL_FALSE;
	}

	//Si on lui a passer un rect, alors on donne ses dimensions, sinon ça veut dire qu'on s'en fout
	if(rect != NULL){

		if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) != 0){

			SDL_Log("IMPOSSIBLE DE PRENDRE DIMENSION TEXTURE :%s", SDL_GetError());
			return SDL_FALSE;
		}
	}

	*textureDst = texture;
	//return de non erreur, et on ajoute dans le pointeur la nouvelle texture
	return SDL_TRUE;
}

SDL_bool BL_create_texture_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color bg, char *text, SDL_Rect *rect, SDL_Texture **textureDst){

	//Variable obligatoire pour créer une texture
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = TTF_RenderUTF8_Shaded(font, text, bg, BL_get_blanc(255));
	//Controle si l'image a bien été charger dans la surface
	if(surface == NULL)	{

		SDL_Log("IMPOSSIBLE DE LOAD LA TEXTURE TEXTE DANS LA SURFACE :%s", TTF_GetError());
		return SDL_FALSE;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
	//fonction qui retourne la texture si elle est créer
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	//plus besoin de la surface, FREE OBLIGATOIRE
	SDL_FreeSurface(surface);
	surface = NULL;

	//On regarde si pas d'erreur
	if(texture == NULL){

		SDL_Log("IMPOSSIBLE DE CREATE TEXTURE POUR LA SURFACE :%s", SDL_GetError());
		return SDL_FALSE;
	}

	//Si on lui a passer un rect, alors on donne ses dimensions, sinon ça veut dire qu'on s'en fout
	if(rect != NULL){

		if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) != 0){

			SDL_Log("IMPOSSIBLE DE PRENDRE DIMENSION TEXTURE :%s", SDL_GetError());
			return SDL_FALSE;
		}
	}

	*textureDst = texture;
	//return de non erreur, et on ajoute dans le pointeur la nouvelle texture
	return SDL_TRUE;
}

SDL_Texture *BL_texture_get_index(BL_Graphics graphics, int index){

	if(index > -1 && index < graphics.nbTexture){

		return graphics.textures[index];
	}

	return NULL;
}

void BL_clean_texture(BL_Graphics *graphics){

	SDL_Log("CLEAN TEXTURE EN COURS\n");
	if(graphics->textures != NULL){
		for(int i = 0; i < graphics->nbTexture; i++){

			if(graphics->textures[i] != NULL){

				SDL_DestroyTexture(graphics->textures[i]);
				graphics->textures[i] = NULL;
			}
		}

		free(graphics->textures);
		graphics->textures = NULL;
	}
	SDL_Log("CLEAN TEXTURE TERMINER\n");
}