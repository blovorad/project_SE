#ifndef __DIRECTORY__H__
#define __DIRECTORY__H__

/**
 * \file directory.h
 * \author Gautier Levesque
 * \brief fichier entete pour la recherche de fichier dans des repertoires
 */

#include "define.h"

#include "dirent.h"
#include "sys/types.h"

/**
 * \fn SDL_bool BL_search_file_in_Directory(char *pathDirectory, char *fileName)
 * \author Gautier Levesque
 * \brief chercher un fichier dans un repertoire
 * \param pathDirectory chemin du repertoire
 * \param fileName nom du fichier a trouver
 * \return booleen si le fichier existe
 */
SDL_bool BL_search_file_in_Directory(char *pathDirectory, char *fileName);

#endif