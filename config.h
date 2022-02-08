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
 * \fn int get_config(FILE *file, Simulation *simulation, Processus_array *array_processus)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief charge la configuration du test de l'ordonnancement
 * \param file fichier de configuration ouvert
 * \param simulation structure remplis par la fonction, notament le quantum de temps
 * \param array_processus tableau qui va être créer qui contient tout les processus du test
 * \return code erreur 0 si ok, -1 sinon
 */
int get_config(FILE *file, Simulation *simulation, Processus_array *array_processus);

/**
 * \fn int fill_processus_array(FILE *file, Processus_array *array_processus)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief lit chaque processus et le remplis de maniere a bien remplir le tableau puis ensuite elle les tri par ordre croissant d'arriver
 * \param file fichier de configuration ouvert
 * \param array_processus tableau qui va être remplis avec toute les informations des processus du test
 * \return un code d'erreur ou 0 si tout va bien
 */
int fill_processus_array(FILE *file, Processus_array *array_processus);

/**
 * \fn int select_algorithm(char *code)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief selection de l'algorithm d'ordonanncement par comparaison de chaine de caractère
 * \param code chaine de caractere decrivant l'algorithme d'ordonnancement
 * \return le code de l'algorithm
 */
int select_algorithm(char *code);

/**
 * \fn FILE *open_fileConfig(char *path, char *mode)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief primitive d'ouverture de fichier
 * \param path chaine de caractere qui represente le chemin d'accès du fichier
 * \param mode chaine de caractere qui represente le mode d'ouverture du fichier
 * \return le pointeur du fichier ouvert
 */
FILE *open_fileConfig(char *path, char *mode);

/**
 * \fn void close_fileConfig(FILE *file)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief primitive qui ferme un fichier precedement ouvert
 * \param file fichier a fermer
 */
void close_fileConfig(FILE *file);

#endif
