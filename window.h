#ifndef __WINDOW__H__
#define __WINDOW__H__

#include "define.h"
#include "directory.h"

/**
 * \file window.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/define/structure utiles a la gestion de fenetre en SDL
 */

/**
 * \struct BL_Window window.h
 * \brief regroupe toutes les variables necessaires a la gestion des fenetres en SDL
 */
typedef struct{
	
	SDL_Window *screen; /*!< fenetre cree par la SDL */
	SDL_Renderer *renderer; /*!< renderer pour gerer l'affichage des textures et autres */
	SDL_bool fullscreen; /*!< si le fullscreen est active ou non */

	unsigned int width; /*!< largeur du screen */
	unsigned int height; /*!< hauteur du screen */

	float scaleX; /*!< le scale x active */
	float scaleY; /*!< le scale y active */

}BL_Window;

/**
 * \fn SDL_bool BL_creat_windowRenderer(char *title, BL_Window *window)
 * \author Gautier Levesque
 * \brief creaton de la fenetre et du renderer
 * \param title nom de la fenetre
 * \param window passage par adresse de la structure qui sera remplie par la fonction
 * \return booleen si la creation de la fenetre et du renderer a echoue, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_creat_windowRenderer(char *title, BL_Window *window);

/**
 * \fn SDL_bool BL_creat_configuration(void)
 * \author Gautier Levesque
 * \brief creaton du fichier configuration pour les valeurs necessaires a la creation de la fenetre s'il n'existe pas
 * \return booleen si la creation de la configuration a echoue, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_creat_configuration(void);

#endif