#include "round_robin.h"

/**
 * \file round_robin.c
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier source qui implemente l'algorithme d'ordonnancement round-robin
 */


/**
 * \var rr_simulation
 * \brief Rassemble toutes les variables globales necessaires pour l'algorithme Round-Robin
 */
RR_simulation rr_simulation;


int round_robin(Simulation *simulation) {

    //Initialisation des structures
	int nbProcessus = simulation->processus_array.nbProcessus;
	
	rr_simulation.threads.nb_threads = nbProcessus;
	rr_simulation.threads.rr_threads = (RR_Thread*) malloc(sizeof(RR_Thread) * rr_simulation.threads.nb_threads);
	if(rr_simulation.threads.rr_threads == NULL){
		perror("Malloc rr_threads failed");
		exit(-1);
	}

    //Creation des mutex
	for (int i = 0; i < rr_simulation.threads.nb_threads; i++) {
		sem_init(&rr_simulation.threads.rr_threads[i].mutex_CPU, 0, 0);
		rr_simulation.threads.rr_threads[i].arrived = 0;
	}
	
    //Parametrage de la simulation Round-Robin a partir de celle fournie en parametre
	rr_simulation.shared_simulation.processus_array = simulation->processus_array;
	rr_simulation.shared_simulation.quantum = simulation->quantum;
	rr_simulation.shared_simulation.code_algorithm = simulation->code_algorithm;
	rr_simulation.shared_simulation.average_time_attempt = simulation->average_time_attempt;
	rr_simulation.shared_simulation.average_time_restitution = simulation->average_time_restitution;
	rr_simulation.shared_simulation.average_time_respond = simulation->average_time_respond;
	rr_simulation.shared_simulation.average_pourcentage_CPU = simulation->average_pourcentage_CPU;
    rr_simulation.effective_occupation_time_cpu = 0;
	

    /******* Debut de la simulation ***********/

    //Instant de debut de la simulation
	rr_simulation.start_time = time(NULL);

	for (int i = 0; i < rr_simulation.threads.nb_threads; i++) {
		pthread_create(&rr_simulation.threads.rr_threads[i].thread, 0, launch_round_robin, 0);
	}
	
	for (int i = 0; i < rr_simulation.threads.nb_threads; i++) {
		pthread_join(rr_simulation.threads.rr_threads[i].thread, 0);
	}

    //Instant de fin de simulation
	time_t end_time = time(NULL);

    /******* Fin de la simulation ***********/


    /******* Calcul des statistiques ***********/

	for (int i = 0; i < nbProcessus; i++) {
        //Sauvegarde des donnees obtenues pour chaque processus
        //Temps de restitution individuel
		simulation->processus_array.processus[i].time_to_restue = rr_simulation.shared_simulation.processus_array.processus[i].time_to_restue;
        //Temps de reponse individuel
		simulation->processus_array.processus[i].time_to_answer = rr_simulation.shared_simulation.processus_array.processus[i].time_to_answer;
        //Temps d'attente individuel
		simulation->processus_array.processus[i].time_attempt = rr_simulation.shared_simulation.processus_array.processus[i].time_attempt;

        //Calcul du temps total d'attente (a diviser par le nombre de processus pour obtenir le temps moyen)
		rr_simulation.shared_simulation.average_time_attempt += (double) rr_simulation.shared_simulation.processus_array.processus[i].time_attempt;

        //Calcul du temps total de restitution (a diviser par le nombre de processus pour obtenir le temps moyen)
		rr_simulation.shared_simulation.average_time_restitution += (double) rr_simulation.shared_simulation.processus_array.processus[i].time_to_restue;
	}

    //Temps moyen d'attente
	simulation->average_time_attempt = rr_simulation.shared_simulation.average_time_attempt / (double) nbProcessus;

    //Temps moyen de restitution 
	simulation->average_time_restitution = rr_simulation.shared_simulation.average_time_restitution / (double) nbProcessus;

    //Temps moyen de reponse
	simulation->average_time_respond = 0; //Considere comme negligeable a l'echelle de la simulation

    //Pourcentage moyen d'occupation de la CPU
	simulation->average_pourcentage_CPU =  (rr_simulation.effective_occupation_time_cpu / (double) difftime(end_time, rr_simulation.start_time)) * (double) 100;
    
    //Temps de restitution total
	simulation->time_restitution = (double)difftime(end_time, rr_simulation.start_time);
	
    //Destruction des mutex
	for (int i = 0; i < rr_simulation.threads.nb_threads; i++) {
		sem_destroy(&rr_simulation.threads.rr_threads[i].mutex_CPU);
	}
    
    //Liberation de la memoire occupee par le tableau de threads
	free(rr_simulation.threads.rr_threads);
    
    return 0;

}


void* launch_round_robin(void* return_value) {
	
    //Indice du thread courant
	int i = 0;
	
	for (int j = 0; j < rr_simulation.threads.nb_threads; j++) {
		//Identification du thread courant
		if (pthread_self() == rr_simulation.threads.rr_threads[j].thread) {
			i = j;
		}
	}

    //Recuperation du processus a executer par le thread courant
	Processus *processus = &rr_simulation.shared_simulation.processus_array.processus[i];

    //Execution du processus 

    //Mesure du temps pour demarrer le processus au moment de son arrivee
	time_t current_time = time(NULL);
	while ((int) difftime(current_time, rr_simulation.start_time) < processus->arrive_at) {
		current_time = time(NULL);
	}
 
    //Recuperation du temps de debut du processus
	time_t start_time_processus = time(NULL);
	
    //Marquage du processus comme arrive dans le thread parent
	rr_simulation.threads.rr_threads[i].arrived = 1;
	
	//Algorithme d'ordonnancement Round-Robin proprement dit
	while(processus->action_cycle != NULL){
		
        //Entree/sortie
		if(processus->action_cycle->type == ES){
            //Simulation de l'entree/sortie en endormant le thread parent
			sleep(processus->action_cycle->time_execution);
			
			//Passage a l'action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
		}
        //Cycle CPU
		else if (processus->action_cycle->type == CPU) {
			
            time_t start_waiting = time(NULL);
			
            //Demande l'acces a la CPU
			sem_wait(&rr_simulation.threads.rr_threads[i].mutex_CPU);
			
            time_t end_waiting = time(NULL);

            //Calcul du temps d'attente du processus
            processus[i].time_attempt += (int) difftime(end_waiting, start_waiting);


            //Occupation de la CPU

            //Instant de debut d'occupation
            time_t start_occupation_cpu = time(NULL);
           
            if (processus->action_cycle->time_execution < rr_simulation.shared_simulation.quantum) {
                sleep(processus->action_cycle->time_execution);
            }
            else {
                sleep(rr_simulation.shared_simulation.quantum);
            }
 
            //Instant de fin d'occupation
            time_t end_occupation_cpu = time(NULL);

            //Calcul du temps d'occupation effectif
            rr_simulation.effective_occupation_time_cpu += difftime(end_occupation_cpu, start_occupation_cpu);
			
			//Passage à l'action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
			
			//Liberation de la CPU
		    sem_post(&rr_simulation.threads.rr_threads[i].mutex_CPU);
		}
	}
	
	processus->time_to_restue = (int) difftime(time(NULL), start_time_processus);
	processus->time_to_answer = 0; //Temps de reponse considere comme negligeable a l'echelle de la simulation
	
	return return_value;
}
