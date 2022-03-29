#ifndef __TEXTURE__H__
#define __TEXTURE__H__

#include "define.h"

#include <dirent.h>
#include <sys/types.h>

#include "color.h"

/**
 * \file texture.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utile a la gestion des textures
 */

/**
 * \struct BL_Graphics texture.h
 * \brief variable pour la sauvegarde des textures crees
 */
typedef struct{

	int nbTexture; /*!< nombre de texture */
	SDL_Texture **textures; /*!< tableau des textures */
	
}BL_Graphics;

/**
 * \fn SDL_bool BL_init_texture(SDL_Renderer *renderer, BL_Graphics *graphics)
 * \author Gautier Levesque
 * \brief creation de toute les textures, elle parcourt le dossier graphics
 * \param renderer necessaire pour creer une texture
 * \param graphics la structure qui sera remplis a la suite de la creation de toute les textures
 * \return boolean si l'initialisation a reussit ou non, SDL_TRUE si oui, SDL_FALSE sinon
 */
SDL_bool BL_init_texture(SDL_Renderer *renderer, BL_Graphics *graphics);

/**
 * \fn SDL_bool BL_create_texture(SDL_Renderer *renderer, char *chemin, SDL_Rect *rect, SDL_Texture **textureDst)
 * \author Gautier Levesque
 * \brief creation d'une texture
 * \param renderer necessaire pour creer une texture
 * \param chemin le chemin vers l'image a charger en texture
 * \param rect si on veut qu'une partie de l'image en question
 * \param textureDst la texture remplis a la fin de la creation
 * \return boolean si la creation a reussit ou non, SDL_TRUE si oui, SDL_FALSE sinon
 */
SDL_bool BL_create_texture(SDL_Renderer *renderer, char *chemin, SDL_Rect *rect, SDL_Texture **textureDst);

/**
 * \fn SDL_bool BL_create_texture_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color bg, char *text, SDL_Rect *rect, SDL_Texture **textureDst)
 * \author Gautier Levesque
 * \brief creation d'une texture pour un texte
 * \param renderer necessaire pour creer une texture
 * \param font la font utiliser pour creer le texte
 * \param bg la couleur du fond du texte
 * \param text le texte qui doit etre changer en texture
 * \param rect si on veut qu'une partis du texte
 * \param textureDst la texture remplis a la fin de la creation
 * \return boolean si la creation a reussit ou non, SDL_TRUE si oui, SDL_FALSE sinon
 */
SDL_bool BL_create_texture_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color bg, char *text, SDL_Rect *rect, SDL_Texture **textureDst);

/**
 * \fn SDL_Texture *BL_texture_get_index(BL_Graphics graphics, int index)
 * \author Gautier Levesque
 * \brief recupere une texture dans le tableau de graphics
 * \param graphics la structure qui contient toutes les textures
 * \param index l'index dans le tableau de la texture
 * \return SDL_Texture la texture du tableau de texture
 */ 
SDL_Texture *BL_texture_get_index(BL_Graphics graphics, int index);

/**
 * \fn void BL_clean_texture(BL_Graphics *graphics)
 * \author Gautier Levesque
 * \brief detruit toute les textures creer precedement
 * \param graphics la structure qui contient toutes les textures
 */ 
void BL_clean_texture(BL_Graphics *graphics);
	
#endif