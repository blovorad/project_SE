#ifndef __MOUSE__H__
#define __MOUSE__H__

#include "define.h"

/**
 * \file mouse.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utiles a la gestion de la souris
 */

/**
 * \struct BL_Mouse mouse.h
 * \brief structure pour la gestion de la souris
 */
typedef struct {
	
	SDL_bool rightButton; /*!< etat du clic droit SDL_TRUE si appuye */
    SDL_bool leftButton; /*!< etat du clic gauche SDL_TRUE si appuye */
	SDL_bool oldRightButton; /*!< ancien etat du clic droit */
    SDL_bool oldLeftButton; /*!< ancien etat du clic gauche */
	SDL_Rect pos; /*!< position de la souris */
}BL_Mouse;

/**
 * \fn SDL_bool BL_init_mouse(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief initialisation de la structure BL_Mouse
 * \param mouse la souris a initialiser
 * \return boolean, SDL_TRUE si initialisation ok, SDL_FALSE sinon
 */
SDL_bool BL_init_mouse(BL_Mouse *mouse);

/**
 * \fn void BL_get_mouse_pos(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief modification du x et y de la structure BL_Mouse
 * \param mouse la souris
 */
void BL_get_mouse_pos(BL_Mouse *mouse);

/**
 * \fn void BL_actualise_right_button(BL_Mouse *mouse, int n)
 * \author Gautier Levesque
 * \brief modification de l'etat du clic droit de la souris
 * \param mouse la souris
 * \param n etat du clic, 1 si appuye, 2 si relache
 */
void BL_actualise_right_button(BL_Mouse *mouse, int n);

/**
 * \fn void BL_actualise_left_button(BL_Mouse *mouse, int n)
 * \author Gautier Levesque
 * \brief modification de l'etat du clic gauche de la souris
 * \param mouse la souris
 * \param n etat du clic, 1 si appuye, 2 si relache
 */
void BL_actualise_left_button(BL_Mouse *mouse, int n);

/**
 * \fn void BL_actualise_old_left_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief modification de l'ancien etat du clic gauche de la souris
 * \param mouse la souris
 */
void BL_actualise_old_left_button(BL_Mouse *mouse);

/**
 * \fn void BL_actualise_old_right_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief modification de l'ancien etat du clic droit de la souris
 * \param mouse la souris
 */
void BL_actualise_old_right_button(BL_Mouse *mouse);

/**
 * \fn SDL_bool BL_get_state_of_right_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de l'etat du clic droit de la souris
 * \param mouse la souris
 * \return etat du clic droit de la souris
 */
SDL_bool BL_get_state_of_right_button(BL_Mouse *mouse);

/**
 * \fn SDL_bool BL_get_state_of_old_right_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de l'ancien etat du clic droit de la souris
 * \param mouse la souris
 * \return ancien etat du clic droit de la souris
 */
SDL_bool BL_get_state_of_old_right_button(BL_Mouse *mouse);

/**
 * \fn SDL_bool BL_get_state_of_left_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de l'etat du clic gauche de la souris
 * \param mouse la souris
 * \return etat du clic gauche de la souris
 */
SDL_bool BL_get_state_of_left_button(BL_Mouse *mouse);

/**
 * \fn SDL_bool BL_get_state_of_old_left_button(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de l'ancien etat du clic gauche de la souris
 * \param mouse la souris
 * \return ancien etat du clic gauche de la souris
 */
SDL_bool BL_get_state_of_old_left_button(BL_Mouse *mouse);

/**
 * \fn int BL_get_mouse_x(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de la position x de la souris
 * \param mouse la souris
 * \return un entier qui represente la position x de la souris
 */
int BL_get_mouse_x(BL_Mouse *mouse);

/**
 * \fn int BL_get_mouse_y(BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief recuperation de la position y de la souris
 * \param mouse la souris
 * \return un entier qui represente la position y de la souris
 */
int BL_get_mouse_y(BL_Mouse *mouse);

#endif