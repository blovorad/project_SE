#include "config.h"
/**
 * \file config.c
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier source pour la gestion du chargemet de la configuration du programme test d'ordonnacement
 */
 
int get_config(FILE *file, Simulation *simulation, Processus_array *array_processus){

    //recuperation du type d'algorithm utilisé
    simulation->code_algorithm = get_algorithm_code(file);
    simulation->quantum = 0;
    if(simulation->code_algorithm == ROUND_ROBIN){

        int quantum;
        fscanf(file, " quantum = %d\n", &quantum);
        simulation->quantum = quantum;
    }
    else{
        //si jamais pas quantum alors on lit le \n de la ligne de l'algorithm qui n'est pas lus
        fscanf(file, "\n");
    }

    int nbProcessus;
    fscanf(file, "Nombre de processus = %d\n", &nbProcessus);
    if(init_processus_array(nbProcessus, array_processus) == -1){

        close_fileConfig(file);
        return -1;
    }
    if(fill_processus_array(file, array_processus) == -1){

        close_fileConfig(file);
        return -1;
    }

    close_fileConfig(file);
    //tout s'est bien passer
    return 0;
}

int fill_processus_array(FILE *file, Processus_array *array_processus){

    fscanf(file, "Nom Arrivee <ES ou CPU>=duree\n");
    for(int i = 0; i < array_processus->nbProcessus; i++){

        int begin;
        int time_processus = 0;
        char car = 'a';
        int size = 0;
        long position = ftell(file);

        /*recuperation de la taille du nom du processus*/
        while(car != ' '){

            fscanf(file, "%c", &car);
            size += 1;
        }

        /*reset pour la lecture du mot*/
        fseek(file, position, SEEK_SET);
        char *name = malloc(sizeof(char) * size);
        if(name == NULL){

            fprintf(stderr, "Error malloc in get_algorithm_code\n");
            return -1;
        }
        /*lecture du mot*/
        fscanf(file, "%s %d ", name, &begin);
        init_processus(name, begin, &array_processus->processus[i]);
        car = 'a';
        while(car != '\n'){
        
        	int time;
        	int type;
		    fscanf(file, "%c", &car);
		    if(car != ' ' && car != '\n'){

		    	fseek(file, (ftell(file) - 1), SEEK_SET);
				if(car == 'C'){
					
					fscanf(file, "CPU=%d", &time);
					type = CPU;
				}
				else if(car == 'E'){
					
					fscanf(file, "ES=%d", &time);
					type = ES;
				}
				array_processus->processus[i].action_cycle = push_to_tail(time, type, array_processus->processus[i].action_cycle);
				time_processus += time;
			}
		}
		array_processus->processus[i].time_execution = time_processus;
    }

    qsort(array_processus->processus, array_processus->nbProcessus, sizeof(Processus), compare_begin_processus);
    for(int i = 0; i < array_processus->nbProcessus; i++){
		
        printf("processus %d : %s,%d,%d,%d\n",i, array_processus->processus[i].name, array_processus->processus[i].arrive_at, array_processus->processus[i].time_execution, array_processus->processus[i].time_pause);
        Action *action = array_processus->processus[i].action_cycle;
        while(action != NULL){
        	
        	if(action->type == CPU){
        		
        		printf("time action : %d CPU\n", action->time_execution);
        	}
        	else{
        		
        		printf("time action : %d ES\n", action->time_execution);
        	}
        	action = action->suivant;
        }
    }
    return 0;
}

int get_algorithm_code(FILE *file){

    fscanf(file, "Algorithme = ");
    long position = ftell(file);
    char car = 'a';
    int size = 0;

    /*recuperation de la taille du nom de l'algorithm d'ordonnancement*/
    while(car != '\n' && car != ' '){

        fscanf(file, "%c", &car);
        size += 1;
    }

    /*reset pour la lecture du mot*/
    fseek(file, position, SEEK_SET);
    char *algorithm_use = malloc(sizeof(char) * size);
    if(algorithm_use == NULL){

        fprintf(stderr, "Error malloc in get_algorithm_code\n");
        return -1;
    }
    /*lecture du mot*/
    fscanf(file, "%s", algorithm_use);

    /*recherche du bon code*/
    int code = select_algorithm(algorithm_use);

    free(algorithm_use);
    algorithm_use = NULL;

    return code;
}

int select_algorithm(char *code){

    if(strcmp(code, "FIFO") == 0){

        return FIFO;
    }
    else if(strcmp(code, "SJF") == 0){

        return SJF;
    }
    else if(strcmp(code, "SRJF") == 0){

        return SRJF;
    }
    else if(strcmp(code, "ROUND_ROBIN") == 0){

        return ROUND_ROBIN;
    }
    else{

        printf("Erreur, algorithm %s non reconnue chargement de l'algorithme FIFO\n", code);
        return FIFO;
    }
}

FILE *open_fileConfig(char *path, char *mode){

    FILE *file = fopen(path, mode);
    if(file == NULL){

        perror("Error fopen file in open_fileConfig");
        exit(1);
    }

    return file;
}

void close_fileConfig(FILE *file){

    if (fclose(file)==EOF) {

        perror("Impossible to close file\n");
        exit(1);
    }
    file = NULL;
}
