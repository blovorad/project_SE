#ifndef __PROCESSUS__H__
#define __PROCESSUS__H__

/**
 * \file processus.h
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fichier entete qui gere les processus
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * \enum Cycle_type
 * \brief Constantes si Action est CPU ou entree/sortie
 */
typedef enum{
	
	CPU, /*!< Action cycle CPU */
	ES /*!< Action cycle Entree/Sortie */
}Cycle_type;
 
/**
 * \struct cellule processus.h
 * \brief liste chainee qui represente une action d'un processus
 */
struct cellule{

	int time_execution; /*!< temps d'execution de l'action */
	Cycle_type type; /*!< si CPU ou ES */
	struct cellule *suivant; /*!< adresse suivante de la prochaine action */
};

/**  
 * \typedef de la struct cellule en Action pour une comprehension et une utilisation plus claire 
 */
typedef struct cellule Action;
 
/**
 * \struct Processus processus.h
 * \brief structure d'un processus ainsi que toutes ses actions, et les resultats de la simulation pour ce processus
 */
typedef struct{

    char *name; /*!< nom du processus */
    int arrive_at; /*!< quand arrive le processus */
    int time_execution; /*!< temps d'execution du processus */
    int time_pause; /*!< temps de debut de la pause courante*/
    int time_attempt; /*!< temps d'attente du processus*/
    int time_to_restue; /*!< temps pour que le processus se termine*/ 
    int time_to_answer; /*!< temps de reponse du processus*/
    Action *action_cycle; /*!< liste de ses actions */
}Processus;

/**
 * \struct Processus_array processus.h
 * \brief gerer un tableau de processus, permet de savoir qui arrive a quel moment en fonction de l'indice dans le tableau
 */
typedef struct{

    int nbProcessus; /*!< nombre de processus */
    Processus *processus; /*!< tableau des processus */
}Processus_array;

/**
 * \fn int init_processus_array(int nbProcessus, Processus_array *array_processus)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief initialisation de tableau de processus
 * \param nbProcessus nombre de processus
 * \param array_processus tableau de processus
 * \return entier 0 si ok, -1 sinon
 */
int init_processus_array(int nbProcessus, Processus_array *array_processus);

/**
 * \fn void init_processus(char *name, int arrive_at, Processus *processus)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief initialise un processus
 * \param name nom du processus
 * \param arrive_at temps auquel arrive le processus
 * \param processus le processus(son adresse) qui est rempli
 */
void init_processus(char *name, int arrive_at, Processus *processus);

/**
 * \fn int compare_begin_processus(const void *p1, const void *p2)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief fonction de comparaison utilisee par qsort qui compare les temps de chaque action
 * \param p1 ici on envoie une action
 * \param p2 ici on envoie une action
 * \return entier si p1.temps > p2.temps
 */
int compare_begin_processus(const void *p1, const void *p2);

/**
 * \fn Action *push_to_tail(int time_execution, Cycle_type type, Action *action)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief insertion en queue dans la liste chainee d'actions
 * \param time_execution temps d'execution (type int) de l'action
 * \param type type d'action, CPU ou ES
 * \param action liste chainee ou faire l'insertion
 * \return la liste chainee avec changement en queue
 */
Action *push_to_tail(int time_execution, Cycle_type type, Action *action);

/**
 * \fn Action *delete_head(Action *action)
 * \author Gautier Levesque
 * \date 29/01/2022
 * \brief detruit la tete de la liste chainee d'actions
 * \param action liste chainee ou l'on doit supprimer la tete
 * \return la liste chainee avec changement de tete
 */
Action *delete_head(Action *action);

#endif
