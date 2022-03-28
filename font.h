#ifndef __FONT__H__
#define __FONT__H__

#include "define.h"

/**
 * \file font.h
 * \author Gautier Levesque
 * \brief fichier entete qui contient les structures/fonctions/defines pour la gestion des font
 */

/**
 * \fn SDL_bool BL_init_font(TTF_Font **font, const char *chemin, int size)
 * \author Gautier Levesque
 * \brief chargement de la font
 * \param font la font a charger
 * \param chemin le chemin vers la font
 * \param size la taille de la font
 * \return boolean, SDL_TRUE si initialisation ok, SDL_FALSE sinon
 */
SDL_bool BL_init_font(TTF_Font **font, const char *chemin, int size);

/**
 * \fn void BL_clean_font(TTF_Font **font)
 * \author Gautier Levesque
 * \brief destruction de la font charger precedement
 * \param font la font a detruire
 */
void BL_clean_font(TTF_Font **font);

#endif