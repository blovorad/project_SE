#include "config.h"
/**
 * \file config.c
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier source pour la gestion du chargemet de la configuration du programme test d'ordonnacement
 */
 
int get_config_commandLine(char *argv[], Simulation_array *simulation_array){
 	
 	int nb_algorithm = 3;// FIFO, SJF, ROUND_ROBIN
 	int quantum = rand() % 10 + 5;
 	
 	simulation_array->nbSimulations = nb_algorithm;
 	simulation_array->simulations = malloc(sizeof(Simulation) * simulation_array->nbSimulations);
   	if(simulation_array->simulations == NULL){
   	
   		fprintf(stderr, "Error malloc in get_config\n");
        return -1;
   	}
   	
   	//recuperation du nombre de processus et du nombre de cycle CPU, on les interfacera avec des cycles ES
   	int nb_processus = get_int_from_string(argv[2]);
   	int nb_CPU = get_int_from_string(argv[3]);

   	if(nb_CPU < 1 && nb_processus < 1){
   		
   		return -1;
   	}
   	
   	for(int i = 0; i < nb_algorithm; i++){

   		if(i == ROUND_ROBIN){
   			
   			simulation_array->simulations[i].quantum = quantum;
   		}
   		else{
   			
   			simulation_array->simulations[i].quantum = 0;
   		}
   		
   		simulation_array->simulations[i].code_algorithm = i;
   		simulation_array->simulations[i].processus_array.nbProcessus = nb_processus;
   		simulation_array->simulations[i].processus_array.processus = malloc(sizeof(Processus) * nb_processus);
   		if(simulation_array->simulations[i].processus_array.processus == NULL){
   			
   			fprintf(stderr, "Error malloc int get_config\n");
   			return -1;
   		}
   		
   		int nb_action = nb_CPU * 2 - 1;
   		//initialisation de chaque processus
   		for(int j = 0; j < nb_processus; j++){
   			
   			char *name = get_name_from_int(j);
   			int arrive_at = (rand() % (nb_processus * 2)) + 2;
   			init_processus(name, arrive_at, &simulation_array->simulations[i].processus_array.processus[j]);
	   		//initialisation de chaque action du processus
	   		for(int k = 0; k < nb_action; k++){
	   			
	   			if(j % 2 == 0){
	   			
	   				simulation_array->simulations[i].processus_array.processus[j].action_cycle = push_to_tail(rand() % 30 + 3, CPU, simulation_array->simulations[i].processus_array.processus[j].action_cycle);
	   			}
	   			else{
	   			
	   				simulation_array->simulations[i].processus_array.processus[j].action_cycle = push_to_tail(rand() % 30 + 3, ES, simulation_array->simulations[i].processus_array.processus[j].action_cycle);
	   			}
	   		}
   		}
   	}
   	
 	return 0;
}	

int get_config_file(FILE *file, Simulation_array *simulation_array){
	
	/*
	recuperation du nombre de simulation 
	une simulation = un algo a utiliser
	*/
    fscanf(file, "Nombre d'algorithme = %d\n", &simulation_array->nbSimulations);
   	simulation_array->simulations = malloc(sizeof(Simulation) * simulation_array->nbSimulations);
   	if(simulation_array->simulations == NULL){
   	
   		fprintf(stderr, "Error malloc in get_config\n");
        return -1;
   	}
   	
   	//boucle pour recuperer le code de l'algorithme de chaque simulation
   	for(int i = 0; i < simulation_array->nbSimulations; i++){
   	
	   	//recuperation du type d'algorithm utilisé
		simulation_array->simulations[i].code_algorithm = get_algorithm_code(file);
		simulation_array->simulations[i].quantum = 0;
		
		if(simulation_array->simulations[i].code_algorithm == ROUND_ROBIN){

		    int quantum;
		    fscanf(file, " quantum = %d\n", &quantum);
		    simulation_array->simulations[i].quantum = quantum;
		}
		else{
		    //si jamais pas quantum alors on lit le \n de la ligne de l'algorithme qui n'est pas lus
		    fscanf(file, "\n");
		}
	}
	
	//remplissage du tableau des processus de chaque simulation
	for(int i = 0; i < simulation_array->nbSimulations; i++){
		
		int position = ftell(file);
		int nbProcessus;
		fscanf(file, "Nombre de processus = %d\n", &nbProcessus);
		//initialisation du tableau de processus avec juste sa taille
		if(init_processus_array(nbProcessus, &simulation_array->simulations[i].processus_array) == -1){

		    close_file(file);
		    return -1;
		}
		//remplissage du tableau de processus
		if(fill_processus_array(file, &simulation_array->simulations[i].processus_array) == -1){

		    close_file(file);
		    return -1;
		}
		fseek(file, position, SEEK_SET);
	}

    close_file(file);
    //tout s'est bien passer
    return 0;
}

int fill_processus_array(FILE *file, Processus_array *processus_array){

    fscanf(file, "Nom Arrivee <ES ou CPU>=duree\n");
    //recuperation des informations de chaque processus de la simulation
    for(int i = 0; i < processus_array->nbProcessus; i++){

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
        init_processus(name, begin, &processus_array->processus[i]);
        car = 'a';//initialisation par defaut
        
        //recuperation de chaque Action du processus
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
				processus_array->processus[i].action_cycle = push_to_tail(time, type, processus_array->processus[i].action_cycle);
				time_processus += time;
			}
		}
		processus_array->processus[i].time_execution = time_processus;
    }
    
	//tri des processus par ordre d'arriver dans la simulation
    qsort(processus_array->processus, processus_array->nbProcessus, sizeof(Processus), compare_begin_processus);
    
    /*
    for(int i = 0; i < processus_array->nbProcessus; i++){
		
        printf("processus %d : %s,%d,%d,%d\n",i, processus_array->processus[i].name, processus_array->processus[i].arrive_at, processus_array->processus[i].time_execution, processus_array->processus[i].time_pause);
        Action *action = processus_array->processus[i].action_cycle;
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
    */
    
    return 0;
}

int get_algorithm_code(FILE *file){

    fscanf(file, "Algorithme = ");
    long position = ftell(file);
    char car = 'a';
    int size = 0;

    /*recuperation de la taille du nom de l'algorithme d'ordonnancement*/
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

Algorithm select_algorithm(char *nom_algorithm){

    if(strcmp(nom_algorithm, "FIFO") == 0){

        return FIFO;
    }
    else if(strcmp(nom_algorithm, "SJF") == 0){

        return SJF;
    }
    else if(strcmp(nom_algorithm, "SRJF") == 0){

        return SRJF;
    }
    else if(strcmp(nom_algorithm, "ROUND_ROBIN") == 0){

        return ROUND_ROBIN;
    }
    else{

        printf("Erreur, algorithm %s non reconnue chargement de l'algorithme FIFO\n", nom_algorithm);
        return FIFO;
    }
}
