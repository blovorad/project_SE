#ifndef __STARTER__H__
#define __STARTER__H__

#include <time.h>
#include <string.h>

#include "simulation.h"
#include "util.h"
#include "resultat.h"
#include "config.h"

/**
 * \file starter.h
 * \author Gautier Levesque
 * \date 02/03/2022
 * \brief fichier entete qui gere le lancement de la simulation
 */

/**
 * \fn int start_simulations(int argc, char *argv[], Simulation_array *simulation_array)
 * \author Gautier Levesque
 * \date 27/02/2022
 * \brief lancer les simulations
 * \param argc nombre d'arguments ligne de commande
 * \param argv les arguments ligne de commande
 * \param simulation_array tableau contenant tout les algorithmes d'ordonnacement a lancer
 * \return entier 0 si ok, autre si erreur
 */
int start_simulations(int argc, char *argv[], Simulation_array *simulation_array);

/**
 * \fn void print_help(void)
 * \author Gautier Levesque
 * \date 27/02/2022
 * \brief affiche l'aide console
 */
void print_help(void);

/**
 * \fn int launch_an_algoritm(Simulation_array *simulation_array)
 * \author Gautier Levesque
 * \date 27/02/2022
 * \brief lancer une simulation
 * \param simulation_array tableau contenant tout les algorithmes d'ordonnacement a lancer
 * \return entier 0 si ok, -1 si erreur
 */
int launch_an_algoritm(Simulation_array *simulation_array);

#endif