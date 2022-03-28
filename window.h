#ifndef __WINDOW__H__
#define __WINDOW__H__

#include "define.h"
#include "directory.h"

/**
 * \file window.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/define/structure utile a la gestion de fenetre en SDL
 */

/**
 * \struct BL_Window window.h
 * \brief regroupe toute les variables necessaire a la gestion des fenetres en SDL
 */
typedef struct{
	
	SDL_Window *screen; /*!< fenetre creer par la SDL */
	SDL_Renderer *renderer; /*!< renderer pour gerer l'affichage des texture et autres */
	SDL_bool fullscreen; /*!< si le fullscreen est activer ou non */

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
 * \param window passage par adresse de la structure qui sera remplis par la fonction
 * \return boolean si la creation de la fenetre et du renderer ont echouer, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_creat_windowRenderer(char *title, BL_Window *window);

/**
 * \fn SDL_bool BL_creat_configuration(void)
 * \author Gautier Levesque
 * \brief creaton du fichier configuration pour les valeurs necessaire a la creation de la fenetre si il n'existe pas
 * \return boolean si la creation de la configuration a echouer, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_creat_configuration(void);

#endif