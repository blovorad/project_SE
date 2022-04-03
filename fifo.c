#include "fifo.h"

/**
 * \file fifo.c
 * \author Mehdi ABERKANE
 * \date 25/03/2022
 * \brief fichier source qui implemente l'algorithme d'ordonnancement Fifo
 */


/**
 * \var fifo_simulation
 * \brief Rassemble toutes les variables globales necessaires pour l'algorithme Fifo
 */
FIFO_simulation fifo_simulation;


int fifo(Simulation *simulation) {
    //Initialisation des structures
    int nbProcessus = simulation->processus_array.nbProcessus;

    fifo_simulation.threads.nb_threads = nbProcessus;
    fifo_simulation.threads.fifo_threads = (FIFO_Thread*) malloc(sizeof(FIFO_Thread) * fifo_simulation.threads.nb_threads);
    if(fifo_simulation.threads.fifo_threads == NULL){
        perror("Malloc fifo_threads failed");
        exit(-1);
    }

    //Creation du mutex
    sem_init(&fifo_simulation.mutex_CPU, 0, 1);


    //Initialisation du booleens du first cycle
    for (int i = 0; i < fifo_simulation.threads.nb_threads; i++) {
        fifo_simulation.threads.fifo_threads[i].first_cycle = 0;
    }

    fifo_simulation.shared_simulation.processus_array = simulation->processus_array;
    fifo_simulation.shared_simulation.code_algorithm = simulation->code_algorithm;
    fifo_simulation.shared_simulation.average_time_attempt = simulation->average_time_attempt;
    fifo_simulation.shared_simulation.average_time_restitution = simulation->average_time_restitution;
    fifo_simulation.shared_simulation.average_time_respond = simulation->average_time_respond;
    fifo_simulation.shared_simulation.average_pourcentage_CPU = simulation->average_pourcentage_CPU;
    fifo_simulation.effective_occupation_time_cpu = 0;

    /** Debut de la simulation **/
	//Instant de debut de la simulation
    fifo_simulation.start_time = time(NULL);

    for (int i = 0; i < fifo_simulation.threads.nb_threads; i++) {
        pthread_create(&fifo_simulation.threads.fifo_threads[i].thread, 0, launch_fifo, 0);
    }

    for (int i = 0; i < fifo_simulation.threads.nb_threads; i++) {
        pthread_join(fifo_simulation.threads.fifo_threads[i].thread, 0);
    }

    //Instant de fin de simulation
    time_t end_time = time(NULL);
    //printf("Fin de la simulation...\n");

    /** Fin de la simulation **/


    /** Calcul des statistiques **/
	//printf("Calcul des statistiques...\n");
    for (int i = 0; i < nbProcessus; i++) {

        simulation->processus_array.processus[i].time_to_restue = fifo_simulation.shared_simulation.processus_array.processus[i].time_to_restue;
        //Temps de reponse individuel
        simulation->processus_array.processus[i].time_to_answer = fifo_simulation.shared_simulation.processus_array.processus[i].time_to_answer;
        //Temps d'attente individuel
        simulation->processus_array.processus[i].time_attempt = fifo_simulation.shared_simulation.processus_array.processus[i].time_attempt;
        //Calcul du temps total d'attente (a diviser par le nombre de processus pour obtenir le temps moyen)
        fifo_simulation.shared_simulation.average_time_attempt += (double) fifo_simulation.shared_simulation.processus_array.processus[i].time_attempt;
        //Calcul du temps total de reponse (a diviser par le nombre de processus pour obtenir le temps moyen)
        fifo_simulation.shared_simulation.average_time_respond += (double) fifo_simulation.shared_simulation.processus_array.processus[i].time_to_answer;
        //Calcul du temps total de restitution (a diviser par le nombre de processus pour obtenir le temps moyen)
        fifo_simulation.shared_simulation.average_time_restitution += (double) fifo_simulation.shared_simulation.processus_array.processus[i].time_to_restue;
    }

    //Temps moyen d'attente
    simulation->average_time_attempt = fifo_simulation.shared_simulation.average_time_attempt / (double) nbProcessus;

    //Temps moyen de restitution 
    simulation->average_time_restitution = fifo_simulation.shared_simulation.average_time_restitution / (double) nbProcessus;

    //Temps moyen de reponse
    simulation->average_time_respond = fifo_simulation.shared_simulation.average_time_respond/ (double) nbProcessus;
	//Pourcentage moyen d'occupation de la CPU
    simulation->average_pourcentage_CPU =  (fifo_simulation.effective_occupation_time_cpu / (double) difftime(end_time, fifo_simulation.start_time)) * (double) 100;

    //Temps de restitution total
    simulation->time_restitution = (double)difftime(end_time, fifo_simulation.start_time);

    sem_destroy(&fifo_simulation.mutex_CPU);

    free(fifo_simulation.threads.fifo_threads);

    return 0;

}


void* launch_fifo(void* return_value) {
    int i = 0;
    for (int j = 0; j < fifo_simulation.threads.nb_threads; j++) {
        if (pthread_self() == fifo_simulation.threads.fifo_threads[j].thread) {
            // Recuperation du Thread courant, pour connaitre l'indice du processus correspondant
            i = j;
        }
    }
    //Stockage du processus correspondnat au thread courant 
    Processus *processus = &fifo_simulation.shared_simulation.processus_array.processus[i];
	//Execution du processus 
   
   if(processus->arrived_at > 0){
   		
   		sleep(processus->arrived_at);
   }
	
	time_t current_time = time(NULL);
	
    //Tant que le processus possède des cycles a effectuer
    while(processus->action_cycle != NULL){

        //Si le cycle à effectuer est une Entree/sortie
        if(processus->action_cycle->type == ES){
            //Attente d'une duree egale aux temps d'execution du cycle ES
            sleep(processus->action_cycle->time_execution);

            //Passage a l'action suivante en supprimant la tete de la liste des cycles a effectuer
            processus->action_cycle = delete_head(processus->action_cycle);
        }
        //Si le cycle à effectuer est un CPU
        else {
            //Sauvegarde de l'instant au debut du temps d'attente
            time_t start_waiting = time(NULL);
            //Decrementation du mutex dès qu'il est disponible
            sem_wait(&fifo_simulation.mutex_CPU);

            //Stockage de la diffence de temps avant et après acces au mutex
            int waitting_time =(int) difftime(time(NULL), start_waiting);
			//Si le cycle à effectuer est le premier du processus
            if(fifo_simulation.threads.fifo_threads[i].first_cycle ==0){
                //Stockage de la difference de temps entre la demande et l'obtention des premiers resultats 
                processus->time_to_answer = waitting_time;
                //Modification de la variable first_cycle du thread courant, pour signaler qu'un cycle à dejà été effectué 
                fifo_simulation.threads.fifo_threads[i].first_cycle =1;
            }

            //Incrementation du temps d'attente, grâce à la différence calculer precedement (int waitting_time)
            processus->time_attempt = processus->time_attempt + waitting_time;

            //Sauvegarde de l'instant au debut du temps d'occupation
            time_t start_occupation_cpu = time(NULL);

            //Stockage du temps d'execution du CPU
            int time_exec = (int) processus->action_cycle->time_execution;

               //Attente du temps d'execution
            sleep(time_exec);

            //Incrementation du temps d'occuation de la CPU , avec le temps d'execution du cycle CPU
            fifo_simulation.effective_occupation_time_cpu = fifo_simulation.effective_occupation_time_cpu +  (int) difftime(time(NULL), start_occupation_cpu);
			//Supprsession de l'action effectue 
            processus->action_cycle = delete_head(processus->action_cycle);

            //Liberation de la CPU
            sem_post(&fifo_simulation.mutex_CPU);
        }
    }
    processus->time_to_restue = (int) difftime(time(NULL), current_time);
    //processus->time_to_answer = 0; //Temps de reponse considere comme negligeable a l'echelle de la simulation

    return return_value;
}
