#include "sjf.h"

/**
 * \file sjf.c
 * \author Gautier Levesque
 * \date 18/03/2022
 * \brief fichier source qui gere l'algorithme SJF
 */
 
/**
 * \var sjf_needs
 * \brief tous les besoins specifiques en terme de variables globales de l'algorithme SJF sont stockes dans cette variable
 */
SJF_needs sjf_needs;

void sjf(Simulation *simulation){
		
	int nb_processus = simulation->processus_array.nbProcessus;
	
	sjf_needs.thread_array.nb_thread = nb_processus;
	sjf_needs.thread_array.threads = malloc(sizeof(SJF_Thread) * sjf_needs.thread_array.nb_thread);
	if(sjf_needs.thread_array.threads == NULL){
	
		perror("malloc failed");
		exit(1);
	}
	
	sjf_needs.start_time = time(NULL);
	
	for(int i = 0; i < sjf_needs.thread_array.nb_thread; i++){
		
		sem_init(&sjf_needs.thread_array.threads[i].mutex_cpu, 0, 0);
		sjf_needs.thread_array.threads[i].arrive = 0;
	}
	sjf_needs.first_cpu = 0;
	
	sjf_needs.simulation_shared.processus_array = simulation->processus_array;
	sjf_needs.simulation_shared.quantum = simulation->quantum;
	sjf_needs.simulation_shared.code_algorithm = simulation->code_algorithm;
	sjf_needs.simulation_shared.average_time_attempt = 0;
	sjf_needs.simulation_shared.average_time_restitution = 0;
	sjf_needs.simulation_shared.average_time_respond = 0;
	sjf_needs.simulation_shared.average_pourcentage_CPU = 0;
	
	for(int i = 0; i < sjf_needs.thread_array.nb_thread; i++){
		
		pthread_create(&sjf_needs.thread_array.threads[i].thread, 0, launch_sjf, 0);
	}
	
	for(int i = 0; i < sjf_needs.thread_array.nb_thread; i++){
		
		pthread_join(sjf_needs.thread_array.threads[i].thread,0);
	}

	time_t end_time = time(NULL);
	
	for(int i = 0; i < nb_processus; i++){
		
		simulation->processus_array.processus[i].time_to_restue = sjf_needs.simulation_shared.processus_array.processus[i].time_to_restue;
		simulation->processus_array.processus[i].time_to_answer = sjf_needs.simulation_shared.processus_array.processus[i].time_to_answer;
		simulation->processus_array.processus[i].time_attempt = sjf_needs.simulation_shared.processus_array.processus[i].time_attempt;
		sjf_needs.simulation_shared.average_time_attempt += (double)sjf_needs.simulation_shared.processus_array.processus[i].time_attempt;
		sjf_needs.simulation_shared.average_time_respond += (double)sjf_needs.simulation_shared.processus_array.processus[i].time_to_answer;
		sjf_needs.simulation_shared.average_time_restitution += (double)sjf_needs.simulation_shared.processus_array.processus[i].time_to_restue;
	}
	simulation->average_time_attempt = sjf_needs.simulation_shared.average_time_attempt / (double)nb_processus;
	simulation->average_time_restitution = sjf_needs.simulation_shared.average_time_restitution / (double)nb_processus;
	simulation->average_time_respond = sjf_needs.simulation_shared.average_time_respond / (double)nb_processus;
	simulation->average_pourcentage_CPU =  (sjf_needs.time_cpu / (double)difftime(end_time, sjf_needs.start_time)) * (double)100;
	simulation->time_restitution = (double)difftime(end_time, sjf_needs.start_time);
	
	for(int i = 0; i < sjf_needs.thread_array.nb_thread; i++){
		
		sem_destroy(&sjf_needs.thread_array.threads[i].mutex_cpu);
	}
	free(sjf_needs.thread_array.threads);
}

void select_next_cpu(void){
	
	int indice = 0;
	int time_execution = -1;
	int profondeur = 0;
	int nb_null = 0;
	int i = 0;
	
	while(time_execution == -1 && i < sjf_needs.thread_array.nb_thread && nb_null < sjf_needs.thread_array.nb_thread){
	
		Action *action_cycle = sjf_needs.simulation_shared.processus_array.processus[i].action_cycle;
		int j = 0;
		while(action_cycle != NULL && j < profondeur){
			
			action_cycle = action_cycle->suivant;
			j += 1;
		}
		
		if(action_cycle != NULL && action_cycle->type == CPU && sjf_needs.thread_array.threads[i].arrive == 1){

			time_execution = action_cycle->time_execution;
			indice = i;
		}
		else if(action_cycle == NULL){
			
			nb_null += 1;
		}
		i++;
		
		if(sjf_needs.thread_array.nb_thread == i){
			
			i = 0;
			profondeur += 1;
		}
	}
	
	if(time_execution > -1){
	
		for(i = 0; i < sjf_needs.thread_array.nb_thread; i++){
			
			Action *action_cycle = sjf_needs.simulation_shared.processus_array.processus[i].action_cycle;
			int j = 0;
			
			while(action_cycle != NULL && j < profondeur){
				
				action_cycle = action_cycle->suivant;
				j += 1;
			}
			if(action_cycle != NULL && action_cycle->type == CPU && sjf_needs.thread_array.threads[i].arrive == 1){
				
				if(action_cycle->time_execution < time_execution){
				
					indice = i;
				}
			}
		}
		sem_post(&sjf_needs.thread_array.threads[indice].mutex_cpu);
	}
}

void *launch_sjf(void *nothing){
	
	int i = 0;
	
	for(int j = 0; j < sjf_needs.thread_array.nb_thread; j++){
		
		if(pthread_self() == sjf_needs.thread_array.threads[j].thread){
		
			i = j;
		}
	}
	Processus *processus = &sjf_needs.simulation_shared.processus_array.processus[i];
	if(processus->arrive_at > 0){
	
		sleep(processus->arrive_at);
	}

	time_t start_time_processus = time(NULL);
	
	//on signale que le thread est arrive
	sjf_needs.thread_array.threads[i].arrive = 1;

	//debut reel de l'algorithme
	while(processus->action_cycle != NULL){

		if(processus->action_cycle->type == ES){
		
			sleep(processus->action_cycle->time_execution);
			
			//recuperation action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
		}
		else{
			
			time_t new_time = time(NULL);
			
			//si debut de l'algorithme et donc qu'aucun cycle cpu n'a ete choisi
			if(sjf_needs.first_cpu == 0){
				
				sjf_needs.first_cpu = 1;
				select_next_cpu();
			}
			sem_wait(&sjf_needs.thread_array.threads[i].mutex_cpu);
			
			//si on n'a pas encore eu acces a la CPU alors calcul du temps de reponse
			if(sjf_needs.thread_array.threads[i].first_cycle == 0){
				
				processus->time_to_answer = (int)difftime(time(NULL), start_time_processus);
				sjf_needs.thread_array.threads[i].first_cycle = 1;
			}
			else{
				//calcul du temps d'attente
				processus->time_attempt += (int)difftime(time(NULL), new_time);
			}
			sleep(processus->action_cycle->time_execution);
			sjf_needs.time_cpu += (int)processus->action_cycle->time_execution;
			
			//recuperation action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
			
			//on choisit le prochain cycle cpu a envoyer
			select_next_cpu();
		}
	}
	
	processus->time_to_restue = (int)difftime(time(NULL), start_time_processus);
	
	return nothing;
}






