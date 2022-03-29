#ifndef __INIT__H__
#define __INIT__H__

#include "define.h"

#include "window.h"
#include "texture.h"
#include "mouse.h"
#include "input.h"
#include "graphe.h"

/**
 * \file init.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utile a l'initialisation de la SDL et de tous les composants necessaires au fonctionnement du programme
 */

/**
 * \fn SDL_bool BL_init(BL_Window *window, BL_Graphics *graphics, BL_Input *input, BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief initialisation de la SDL, SDL_TTF, et des composants
 * \param window la fenetre et le renderer a creer
 * \param graphics initialisation du tableau de textures
 * \param input initialisation de la structure pour les touches du clavier
 * \param mouse initialisation de la structure pour la gestion de la souris
 * \return boolean, SDL_TRUE si initialisation ok, SDL_FALSE sinon
 */
SDL_bool BL_init(BL_Window *window, BL_Graphics *graphics, BL_Input *input, BL_Mouse *mouse);

/**
 * \fn void BL_clean(BL_Window *window, BL_Graphics *graphics, BL_Histogramme *histogramme)
 * \author Gautier Levesque
 * \brief nettoyage de toutes les ressources allouer dynamiquement par la SDL et pour le programme
 * \param window window et renderer a detruire
 * \param graphics le tableau de textures a detruire
 * \param histogramme les textes de l'histogramme sont a detruire
 */
void BL_clean(BL_Window *window, BL_Graphics *graphics, BL_Histogramme *histogramme);

#endif