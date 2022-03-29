#include "directory.h"

/**
 * \file directory.c
 * \author Gautier Levesque
 * \brief fichier source pour la recherche de fichier dans des repertoires
 */

SDL_bool BL_search_file_in_Directory(char *pathDirectory, char *fileName){

    DIR *directory = opendir(pathDirectory);
	if(directory == NULL){

		fprintf(stderr, "opendir; %s\n", strerror(errno));
		return SDL_FALSE;
	}

	SDL_bool foundFile = SDL_FALSE;
	struct dirent *currentFile = readdir(directory);

	while(foundFile == SDL_FALSE && currentFile != NULL){

		if(strcmp(fileName, currentFile->d_name) == 0){

			foundFile = SDL_TRUE;
		}

		currentFile = readdir(directory);
	}

	closedir(directory);
	directory = NULL;

    return foundFile;
}