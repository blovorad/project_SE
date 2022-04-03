#ifndef FIFOH
#define FIFOH

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
 * \file fifo.h
 * \author Mehdi ABERKANE
 * \date 25/03/2022
 * \brief fichier entete associe a l'algorithme d'ordonnancement Fifo
 */


/**
 * \struct FIFO_Thread fifo.h
 * \brief Structure pour gerer les threads durant l'algorithme Fifo
 */
typedef struct {
    int first_cycle; /*!< booleen signalant si le premier cycle du processus a été effectué */
     pthread_t thread; /*!< thread representant le processus */
} FIFO_Thread;

/**
 * \struct FIFO_Threads_array fifo.h
 * \brief Tableau de FIFO_Thread
 */
typedef struct {
     int nb_threads; /*!< nombre de thread */
     FIFO_Thread *fifo_threads; /*!< le tableau de thread */
 } FIFO_Threads_array; 
 
 
/**
 * \struct FIFO_simulation fifo.h
 * \brief Rassemble toutes les variables globales necessaires pour l'algorithme Fifo
 */
typedef struct{
    Simulation shared_simulation; /*!< variable partagee pour la simulation */
    time_t start_time; /*!< instant de debut de l'algorithme */
     sem_t mutex_CPU; /*!< mutex pour restreindre l'acces a la CPU */
    double effective_occupation_time_cpu; /*!< temps effectif d'occupation de la CPU au cours de l'execution de l'algorithme */
    FIFO_Threads_array threads; /*!< tableau des threads */
} FIFO_simulation;


/**
 * \fn int fifo(Simulation *simulation)
 * \author Mehdi ABERKANE
 * \date 23/03/2022
 * \brief Simulation effectuee avec l'algorithme Fifo 
 * \param simulation simulation ayant pour algorithme d'ordonnancement Fifo
 * \return 0 en temps normal, -1 en cas d'erreur
 */
int fifo(Simulation *simulation);

/**
 * \fn void* launch_fifo(void* return_value)
 * \author Mehdi ABERKANE
 * \date 29/03/2022
 * \brief Fonction de simulation de l'algorithme Fifo
 * \return void*
 */
void* launch_fifo(void* return_value);

#endif
