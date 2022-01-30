#include "processus.h"

/*Initialisation d'un tableau de processus*/
int init_processus_array(int nbProcessus, Processus_array *array_processus){

    array_processus->nbProcessus = nbProcessus;
    array_processus->processus = malloc(sizeof(Processus) * nbProcessus);
    if(array_processus->processus == NULL){

        fprintf(stderr, "Error malloc in init_processus_array\n");
        return -1;
    }

    return 0;
}

/*Initialisation d'un processus*/
void init_processus(char *name, int arrive_at, int length, Processus *processus){

    processus->name = name;
    processus->arrive_at = arrive_at;
    processus->length = length;
    processus->timePause = 0;
    processus->startWith = CPU;
    processus->action_cycle = NULL;
}

/*
fonction de tri pour qsort
comparaison entre les temps d'arriver de chaque processus
*/
int compare_begin_processus(const void *p1, const void *p2){

    const Processus *processus1 = p1;
    const Processus *processus2 = p2;

    return processus1->arrive_at >= processus2->arrive_at;
}

/*fonction de base pour la liste chainer action*/
Action *push_to_tail(int length, Cycle_type type, Action *action){
	
	Action *tmp = malloc(sizeof(struct cellule));
	if(tmp == NULL){
		
		fprintf(stderr, "Error malloc in push_to_tail\n");
		exit(1);
	}
	tmp->length = length;
	tmp->type = type;
	tmp->suivant = NULL;
	if(action == NULL){
	
		return tmp;
	}
	
	Action *tmp2 = action;
	
	while(tmp2->suivant != NULL){
		
		tmp2 = tmp2->suivant;
	}
	tmp2->suivant = tmp;
	
	return action;
}

Action *delete_head(Action *action){
	
	Action *tmp = action;
	
	action = tmp->suivant;
	free(tmp);
	tmp = NULL;
	
	return action;
}
