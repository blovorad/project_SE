#ifndef __GEOMETRIE__H__
#define __GEOMETRIE__H__

#include "define.h"

/**
 * \file geometrie.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les structures utiles a la gestion de la geometrie
 */

/**
 * \struct BL_Cercle geometrie.h
 * \brief variable pour la gestion de cercles
 */
typedef struct{

	int cx; /*!< position x du centre du cercle */
	int cy; /*!< position y du centre du cercle */
	int rayon; /*!< rayon du cercle */

	SDL_Color couleur; /*!< couleur du cercle */

}BL_Cercle;

#endif