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