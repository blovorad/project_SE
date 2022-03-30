#ifndef __INPUT__H__
#define __INPUT__H__

#include "define.h"

/**
 * \file input.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/defines/structures utiles a la gestion des touches du clavier
 */

/**
 * \struct BL_Input input.h
 * \brief structure pour la gestion des touches du clavier, SDL_TRUE si appuye
 */
typedef struct {

	SDL_bool a; /*!< etat du a sur le clavier */
	SDL_bool z; /*!< etat du z sur le clavier */
	SDL_bool e; /*!< etat du e sur le clavier */
	SDL_bool r; /*!< etat du r sur le clavier */
	SDL_bool t; /*!< etat du t sur le clavier */
	SDL_bool y; /*!< etat du y sur le clavier */
	SDL_bool u; /*!< etat du u sur le clavier */
	SDL_bool i; /*!< etat du i sur le clavier */
	SDL_bool o; /*!< etat du o sur le clavier */
	SDL_bool p; /*!< etat du p sur le clavier */
	SDL_bool q; /*!< etat du q sur le clavier */
	SDL_bool s; /*!< etat du s sur le clavier */
	SDL_bool d; /*!< etat du d sur le clavier */
	SDL_bool f; /*!< etat du f sur le clavier */
	SDL_bool g; /*!< etat du g sur le clavier */
	SDL_bool h; /*!< etat du h sur le clavier */
	SDL_bool j; /*!< etat du j sur le clavier */
	SDL_bool k; /*!< etat du k sur le clavier */
	SDL_bool l; /*!< etat du l sur le clavier */
	SDL_bool m; /*!< etat du m sur le clavier */
	SDL_bool w; /*!< etat du w sur le clavier */
	SDL_bool x; /*!< etat du x sur le clavier */
	SDL_bool c; /*!< etat du c sur le clavier */
	SDL_bool v; /*!< etat du v sur le clavier */
	SDL_bool b; /*!< etat du b sur le clavier */
	SDL_bool n; /*!< etat du n sur le clavier */
	SDL_bool space; /*!< etat de la touche Espace sur le clavier */
	SDL_bool up; /*!< etat de la fleche numerique haut sur le clavier */
	SDL_bool down; /*!< etat de la fleche numerique bas sur le clavier */
	SDL_bool left; /*!< etat de la fleche numerique gauche sur le clavier */
	SDL_bool right; /*!< etat de la fleche numerique droit sur le clavier */
	SDL_bool escape; /*!< etat de la touche Echap sur le clavier */

}BL_Input;


/**
 * \fn SDL_bool BL_init_input(BL_Input *input)
 * \author Gautier Levesque
 * \brief initialisation de la structure BL_Input
 * \param input la structure input a initialiser
 * \return booleen, SDL_TRUE si initialisation ok, SDL_FALSE sinon
 */
SDL_bool BL_init_input(BL_Input *input);

#include "mouse.h"

/**
 * \fn SDL_bool BL_get_input_keyboard(BL_Input *input, BL_Mouse *mouse)
 * \author Gautier Levesque
 * \brief actualisation de l'etat des touches du clavier et du clic de la souris
 * \param input la structure input a actualiser pour les touches du clavier
 * \param mouse la structure mouse a actualiser pour les clics souris
 * \return booleen, SDL_FALSE si la touche pour quitter le programme de maniere brusque est pressee, SDL_TRUE sinon
 */
SDL_bool BL_get_input_keyboard(BL_Input *input, BL_Mouse *mouse);

#endif