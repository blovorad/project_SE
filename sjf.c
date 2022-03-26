#include "sjf.h"

/**
 * \file sjf.c
 * \author Gautier Levesque
 * \date 18/03/2022
 * \brief fichier source qui gere l'algorithme SJF
 */
 
/**
 * \var sjf_needs
 * \brief tout les besoins specifiques en terme de variable global de l'algorithme SJF sont stocke dans cette variable
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
	sjf_needs.simulation_shared.average_time_attempt = simulation->average_time_attempt;
	sjf_needs.simulation_shared.average_time_restitution = simulation->average_time_restitution;
	sjf_needs.simulation_shared.average_time_respond = simulation->average_time_respond;
	sjf_needs.simulation_shared.average_pourcentage_CPU = simulation->average_pourcentage_CPU;
	
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
		sjf_needs.simulation_shared.average_time_restitution += (double)sjf_needs.simulation_shared.processus_array.processus[i].time_to_restue;
	}
	simulation->average_time_attempt = sjf_needs.simulation_shared.average_time_attempt / (double)nb_processus;
	simulation->average_time_restitution = sjf_needs.simulation_shared.average_time_restitution / (double)nb_processus;
	simulation->average_time_respond = 0;
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
	int i = 0;
	
	while(time_execution == -1 && i < sjf_needs.thread_array.nb_thread){

		if(sjf_needs.simulation_shared.processus_array.processus[i].action_cycle != NULL && sjf_needs.simulation_shared.processus_array.processus[i].action_cycle->type == CPU && sjf_needs.thread_array.threads[i].arrive == 1){

			time_execution = sjf_needs.simulation_shared.processus_array.processus[i].action_cycle->time_execution;
			indice = i;
		}
		i++;
	}
	
	if(time_execution > -1){
	
		for(i = 0; i < sjf_needs.thread_array.nb_thread; i++){
			
			if(sjf_needs.simulation_shared.processus_array.processus[i].action_cycle != NULL && sjf_needs.simulation_shared.processus_array.processus[i].action_cycle->type == CPU && sjf_needs.thread_array.threads[i].arrive == 1){
				
				if(sjf_needs.simulation_shared.processus_array.processus[i].action_cycle->time_execution < time_execution){
				
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
	time_t new_time = time(NULL);
	while((int)difftime(new_time, sjf_needs.start_time) < processus->arrive_at){
		
		new_time = time(NULL);
	}
	time_t start_time_processus = time(NULL);
	
	//on signal que le thread est arriver
	sjf_needs.thread_array.threads[i].arrive = 1;
	
	//debut reel de l'algorithme
	while(processus->action_cycle != NULL){
		
		if(processus->action_cycle->type == ES){
		
			sleep(processus->action_cycle->time_execution);
			
			//recuperation action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
		}
		else{
			
			new_time = time(NULL);
			
			//si debut de l'algorithme et donc qu'aucun cycle cpu n'a ete choisit
			if(sjf_needs.first_cpu == 0){
				
				sjf_needs.first_cpu = 1;
				select_next_cpu();
			}
			
			sem_wait(&sjf_needs.thread_array.threads[i].mutex_cpu);
				
			//calcul du temps d'attente
			processus->time_attempt += (int)difftime(time(NULL), new_time);
				
			sleep(processus->action_cycle->time_execution);
			sjf_needs.time_cpu += (double)processus->action_cycle->time_execution;
			
			//recuperation action suivante
			processus->action_cycle = delete_head(processus->action_cycle);
			
			//on choisis le prochain cycle cpu a envoyer
			select_next_cpu();
		}
	}
	
	processus->time_to_restue = (int)difftime(time(NULL), start_time_processus);
	processus->time_to_answer = 0;
	
	return nothing;
}






