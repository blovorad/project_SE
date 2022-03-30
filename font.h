#ifndef __FONT__H__
#define __FONT__H__

#include "define.h"

/**
 * \file font.h
 * \author Gautier Levesque
 * \brief fichier entete qui contient les structures/fonctions/defines pour la gestion des polices de caractere
 */

/**
 * \fn SDL_bool BL_init_font(TTF_Font **font, const char *chemin, int size)
 * \author Gautier Levesque
 * \brief chargement de la police
 * \param font la police a charger
 * \param chemin le chemin vers la police
 * \param size la taille de la police
 * \return boolean, SDL_TRUE si initialisation ok, SDL_FALSE sinon
 */
SDL_bool BL_init_font(TTF_Font **font, const char *chemin, int size);

/**
 * \fn void BL_clean_font(TTF_Font **font)
 * \author Gautier Levesque
 * \brief destruction de la police chargee precedemment
 * \param font la police a detruire
 */
void BL_clean_font(TTF_Font **font);

#endif