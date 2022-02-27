#ifndef __RESULTAT__H__
#define __RESULTAT__H__

/**
 * \file resultat.h
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief fichier entete qui s'occupe la generation des resultats des simulations
 */

#include "simulation.h"
#include "processus.h"
#include "util.h"

/**
 * \fn int generate_result_processus(char *path, Simulation_array simulation_array)
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief ecrit les resultats des processus dans un fichier .csv
 * \param path chemin ou ecrire les resultats
 * \param simulation_array tableau de toutes les simulations
 * \return entier 0 si ok, -1 sinon
 */
int generate_result_processus(char *path, Simulation_array simulation_array);

/**
 * \fn void print_resultat_console_processus(Simulation_array simulation_array)
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief afficher les resultats de la simulation dans la console
 * \param simulation_array contient un tableau des simulations
 */
void print_resultat_console_processus(Simulation_array simulation_array);

#endif
