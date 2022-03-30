#ifndef __ROUNDROBIN__H__
#define __ROUNDROBIN__H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#include "simulation.h"
#include "util.h"
#include "resultat.h"
#include "config.h"

/**
 * \file round_robin.h
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier entete associe a l'algorithme d'ordonnancement Round-Robin
 */


/**
 * \struct RR_Thread round_robin.h
 * \brief Structure pour gerer les threads durant l'algorithme Round-Robin
 */
typedef struct {
 	int arrived; /*!< booleen signalant si le processus est arrive (1) ou pas (0) */
 	pthread_t thread; /*!< thread representant le processus */
} RR_Thread;

/**
 * \struct RR_Threads_array round_robin.h
 * \brief Tableau de RR_Thread
 */
typedef struct {
 	int nb_threads; /*!< nombre de thread */
 	RR_Thread* rr_threads; /*!< le tableau de thread */
 } RR_Threads_array; 
 
 
/**
 * \struct RR_simulation round_robin.h
 * \brief Rassemble toutes les variables globales necessaires pour l'algorithme Round-Robin
 */
typedef struct{
	Simulation shared_simulation; /*!< variable partagee pour la simulation */
	time_t start_time; /*!< instant de debut de l'algorithme */
 	sem_t mutex_CPU; /*!< mutex pour restreindre l'acces a la CPU */
	double effective_occupation_time_cpu; /*!< temps effectif d'occupation de la CPU au cours de l'execution de l'algorithme */
	RR_Threads_array threads; /*!< tableau des threads */
} RR_simulation;


/**
 * \fn int round_robin(Simulation *simulation)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Simulation effectuee avec l'algorithme Round-Robin (ou tourniquet)
 * \param simulation simulation ayant pour algorithme d'ordonnancement Round-Robin
 * \return 0 en temps normal, -1 en cas d'erreur
 */
int round_robin(Simulation *simulation);

/**
 * \fn void* launch_round_robin(void* return_value)
 * \author Ouliana Anikienko
 * \date 29/03/2022
 * \brief Fonction de simulation de l'algorithme Round-Robin
 * \return void*
 */
void* launch_round_robin(void* return_value);

#endif