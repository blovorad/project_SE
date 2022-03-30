#ifndef __UPDATE__H__
#define __UPDATE__H__

#include "define.h"

#include "input.h"
#include "gui.h"
#include "mouse.h"
#include "window.h"
#include "graphe.h"
#include "simulation.h"

/**
 * \file update.h
 * \author Gautier Levesque
 * \brief fichier entete qui regroupe les fonctions/define/structure utiles a la gestion de l'actualisation des elements
 */

/**
 * \fn SDL_bool BL_update(BL_Window window, double deltaTime, BL_Input *input, BL_Mouse *mouse, BL_Panel *panel, BL_Histogramme *histogramme, Simulation_array simulation_array)
 * \author Gautier Levesque
 * \brief actualisation des elements donnes en parametres
 * \param window necessaire pour gerer certaines actualisations ou il faudra recreer des textures
 * \param deltaTime valeur necessaire pour gerer le temps dans la SDL
 * \param input gestion des appuis clavier ainsi que des clics souris
 * \param mouse gestion de la position de la souris, et des clics souris
 * \param panel le panel a actualiser
 * \param histogramme l'histogramme a actualiser
 * \param simulation_array necessaire pour l'actualisation de l'histogramme
 * \return booleen si l'actualisation a echoue ou non, SDL_FALSE si echec, SDL_TRUE sinon
 */
SDL_bool BL_update(BL_Window window, double deltaTime, BL_Input *input, BL_Mouse *mouse, BL_Panel *panel, BL_Histogramme *histogramme, Simulation_array simulation_array);

#endif