#ifndef __COLOR__H__
#define __COLOR__H__

#include "define.h"

/**
 * \file color.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utile a la gestion des couleurs
 */

/**
 * \fn SDL_Color BL_get_vert(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur verte
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_vert(int alpha);

/**
 * \fn SDL_Color BL_get_vert_foncer(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur verte foncer
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_vert_foncer(int alpha);

/**
 * \fn SDL_Color BL_get_gris(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur grise
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_gris(int alpha);

/**
 * \fn SDL_Color BL_get_rouge(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur rouge
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_rouge(int alpha);

/**
 * \fn SDL_Color BL_get_bleu(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur bleue
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_bleu(int alpha);

/**
 * \fn SDL_Color BL_get_blanc(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur blanche
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_blanc(int alpha);

/**
 * \fn SDL_Color BL_get_noir(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur noire
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_noir(int alpha);

/**
 * \fn SDL_Color BL_get_marron(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur marron
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_marron(int alpha);

/**
 * \fn SDL_Color BL_get_jaune(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur jaune
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_jaune(int alpha);

/**
 * \fn SDL_Color BL_get_ocre(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur ocre
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_ocre(int alpha);

/**
 * \fn SDL_Color BL_get_orange(int alpha)
 * \author Gautier Levesque
 * \brief renvoie la couleur orange
 * \param alpha canal alpha pour la transparence
 * \return SDL_Color la couleur
 */
SDL_Color BL_get_orange(int alpha);

#endif