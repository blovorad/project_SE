#include "util.h"

/**
 * \file util.c
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief fichier source qui regroupe les fonctions utiles au projet
 */

int is_path_ok(char *path){
	
	int size = size_string(path);
	if(size < 7 || size > 255){
        printf("Nom de fichier de longueur insuffisante\n");
		return 0;
	}	
	char extension[6];
	extension[0] = path[size - 4];
	extension[1] = path[size - 3];
	extension[2] = path[size - 2];
	extension[3] = path[size - 1];
	extension[4] = path[size];
    extension[5] = '\0';

	
	if(strncmp(".csv", extension, 4) != 0){
		printf("Probleme avec l'extension du fichier, celle-ci doit etre .csv\n");
		return 0;
	}
	
	return 1;
}

int size_string(char *string){

	int size = 0;
	
	while(string[size] != '\0'){
		
		 size++;
	}
	
	return size;
}

int get_int_from_string(char *string){
	
	int number = 0;
	int i = 1;
	
	char car = string[0];
	while(car != '\0'){

		if(car >= '0' && car <= '9'){
		
			int char_number = car - '0';
			number = number * 10 + char_number;
		}
		car = string[i];
		i += 1;
	}
	
	return number;
}

char *get_name_from_int(int number){
	
	char *name = NULL;
	
	int unite = 1;
	while(number < 0){
		
		number = number / 10;
		unite += 1;
	}
	//sprintf(text, "%d", number)
	name = malloc(sizeof(char) * (unite + 2));
	if(name == NULL){
		
		fprintf(stderr, "Error malloc in get_name_from_int\n");
		return NULL;
	}
	
	sprintf(name, "%d", number);
	
	for(int i = (unite + 1); i > 0; i--){
		
		name[i] = name[i-1];
	}
	name[0] = 'P';
	
	return name;
}

char *get_string_from_algorithm(int code_algorithm){
	
	switch(code_algorithm){
		
		case FIFO : return "FIFO";
		case SJF : return "SJF";
		case ROUND_ROBIN : return "ROUND_ROBIN";
		default : return "NOT KNOW";
	}
}

FILE *open_file(char *path, char *mode){

    FILE *file = fopen(path, mode);
    if(file == NULL){

        perror("Error fopen file in open_fileConfig");
        exit(1);
    }

    return file;
}

void close_file(FILE *file){

    if (fclose(file)==EOF) {

        perror("Impossible to close file\n");
        exit(1);
    }
    file = NULL;
}
