#ifndef __UTIL__H__
#define __UTIL__H__

/**
 * \file util.h
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief fichier entete qui regroupe les fonctions utiles au projet
 */

#include <string.h>

#include "simulation.h"

/**
 * \fn int is_path_ok(char *path)
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief regarder si la chaine de caractere est bien un chemin qui donne sur un .csv, si l'extension est bien .csv
 * \param path chemin du fichier a verifier
 * \return booleen 1 si ok et 0 si erreur
 */
int is_path_ok(char *path);

/**
 * \fn int size_string(char *string)
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief compter le nombre de caracteres dans une chaine, sans compter le '/0'
 * \param string chaine de caracteres
 * \return entier qui represente la taille de la chaine de caracteres
 */
int size_string(char *string);

/**
 * \fn int get_int_from_string(char *string)
 * \author Gautier Levesque
 * \date 22/02/2022
 * \brief tirer un nombre d'apres une chaine de caracteres
 * \param string chaine de caracteres
 * \return entier qui represente le nombre
 */
int get_int_from_string(char *string);

/**
 * \fn char *get_name_from_int(int number)
 * \author Gautier Levesque
 * \date 22/02/2022
 * \brief permet de donner un nom au processus en fonction de son numero
 * \param number a transformer en chaine de caracteres
 * \return chaine de caracteres
 */
char *get_name_from_int(int number);

/**
 * \fn char *get_string_from_algorithm(int code_algorithm)
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief retourner la chaine de caractere correspondant a l'algorithme utilise
 * \param code_algorithm en int
 * \return nom de l'algorithme
 */
char *get_string_from_algorithm(int code_algorithm);

/**
 * \fn FILE *open_file(char *path, char *mode)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief primitive d'ouverture de fichier
 * \param path chaine de caracteres qui represente le chemin d'acces au fichier
 * \param mode chaine de caracteres qui represente le mode d'ouverture du fichier
 * \return le pointeur du fichier ouvert
 */
FILE *open_file(char *path, char *mode);

/**
 * \fn void close_file(FILE *file)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief primitive qui ferme un fichier precedemment ouvert
 * \param file fichier a fermer
 */
void close_file(FILE *file);

#endif
