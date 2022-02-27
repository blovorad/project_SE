#ifndef __CONFIG__H__
#define __CONFIG__H__

/**
 * \file config.h
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier entete pour la gestion du chargemet de la configuration du programme
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation.h"
#include "processus.h"
#include "util.h"

/**
 * \fn int get_algorithm_code(FILE *file)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief lire le type d'algorithm d'ordonnancement utilise pour cette configuration
 * \param file fichier de configuration ouvert
 * \return entier qui represente le type d'algorithm ou -1 si erreur
 */
int get_algorithm_code(FILE *file);

/**
 * \fn int get_config_commandLine(char *argv[], Simulation_array *simulation_array)
 * \author Gautier Levesque
 * \date 21/02/2022
 * \brief charge la configuration du test de l'ordonnancement depuis la ligne de commande
 * \param argv tableau des mots
 * \param simulation_array structure remplis par la fonction, notament le quantum de temps et la liste des processus
 * \return entier 0 si ok, -1 sinon
 */
int get_config_commandLine(char *argv[], Simulation_array *simulation_array);

/**
 * \fn int get_config_file(FILE *file, Simulation_array *simulation_array)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief charge la configuration du test de l'ordonnancement depuis un fichier configuration
 * \param file fichier de configuration ouvert
 * \param simulation_array structure remplis par la fonction, notament le quantum de temps et la liste des processus
 * \return entier 0 si ok, -1 sinon
 */
int get_config_file(FILE *file, Simulation_array *simulation_array);

/**
 * \fn int fill_processus_array(FILE *file, Processus_array *processus_array)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief lit chaque processus et le remplis de maniere a bien remplir le tableau puis ensuite elle les tri par ordre croissant d'arriver
 * \param file fichier de configuration ouvert
 * \param processus_array tableau qui va être remplis avec toute les informations des processus du test
 * \return entier 0 si ok, -1 sinon
 */
int fill_processus_array(FILE *file, Processus_array *processus_array);

/**
 * \fn Algorithm select_algorithm(char *nom_algorithm)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief selection de l'algorithm d'ordonanncement par comparaison de chaine de caractère
 * \param nom_algorithm chaine de caractere decrivant l'algorithme d'ordonnancement
 * \return le code de l'algorithm
 */
Algorithm select_algorithm(char *nom_algorithm);

#endif
