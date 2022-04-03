#ifndef __SJF__H__
#define __SJF__H__

#include "simulation.h"
#include "processus.h"

#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

/**
 * \file sjf.h
 * \author Gautier Levesque
 * \date 18/03/2022
 * \brief fichier entete qui gere l'algorithme SJF
 */
 
/**
 * \struct SJF_Thread sjf.h
 * \brief Structure pour gerer les threads pour l'algorithme SJF
 */
typedef struct{
 	
 	int arrive; /*!< si le thread est bien lance, c'est-a-dire que le temps d'arrivee du processus est bien atteint et donc qu'il peut entrer en action */
 	int first_cycle; /*!< si le cycle CPU a ete execute au moins une fois */
 	sem_t mutex_cpu; /*!< mutex du thread pour les cycles CPU */
 	pthread_t thread; /*!< le thread en question */
 }SJF_Thread;
 
/**
 * \struct SJF_Thread_array sjf.h
 * \brief Tableau de thread SJF
 */
typedef struct{
 	
 	int nb_thread; /*!< nombre de threads */
 	SJF_Thread *threads; /*!< le tableau de threads */
 }SJF_Thread_array; 
 
 
/**
 * \struct SJF_needs sjf.h
 * \brief toutes les variables globales necessaires pour l'algorithme
 */
typedef struct{
 	
	Simulation simulation_shared; /*!< variable partagee pour la simulation */
	time_t start_time; /*!< temps de debut de l'algorithme */
	double time_cpu; /*!< temps total de tous les cycles CPU reunis */
	int first_cpu; /*!< Si on a deja un cycle CPU qui a ete execute */
	SJF_Thread_array thread_array; /*!< tableau des threads */
}SJF_needs;

/**
 * \fn void sjf(Simulation *simulation)
 * \author Gautier Levesque
 * \date 18/03/2022
 * \brief lancer la simulation SJF
 * \param simulation une simulation contenant toutes ses actions a effectuer, sera remplie avec les resultats de la simulation
 */
void sjf(Simulation *simulation);

/**
 * \fn void select_next_cpu(void)
 * \author Gautier Levesque
 * \date 25/03/2022
 * \brief cherche le prochain cycle CPU a executer
 */
void select_next_cpu(void);

/**
 * \fn void *launch_sjf(void *nothing)
 * \author Gautier Levesque
 * \date 18/03/2022
 * \brief lancer un processus de SJF, fonction qu'on envoie pour les threads
 * \param nothing variable obligatoire pour les threads
 */
void *launch_sjf(void *nothing);

#endif
