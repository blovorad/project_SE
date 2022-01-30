#ifndef __PROCESSUS__H__
#define __PROCESSUS__H__

#include <stdio.h>
#include <stdlib.h>

typedef enum{
	
	CPU,
	ES
}Cycle_type;


typedef struct cellule{

	int length;
	int type;
	struct cellule *suivant;
}Action;

typedef struct{

    char *name;
    int arrive_at;
    int length;
    int timePause;
    Cycle_type startWith;
    Action *action_cycle;
}Processus;

typedef struct{

    int nbProcessus;
    Processus *processus;
}Processus_array;

int init_processus_array(int nbProcessus, Processus_array *array_processus);
void init_processus(char *name, int arrive_at, int length, Processus *processus);
int compare_begin_processus(const void *p1, const void *p2);

Action *push_to_tail(int length, Cycle_type type, Action *action);
Action *delete_head(Action *action);

#endif
