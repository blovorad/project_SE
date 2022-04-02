#include "resultat.h"

/**
 * \file resultat.c
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief fichier source qui s'occupe la generation des resultats des simulations
 */
 
int generate_result_simulation(char *path, Simulation_array simulation_array){
	
	FILE *file = open_file(path, "a");
	fprintf(file, "\n\n\nRESULTAT DE LA SIMULATION\n\n\n"); 
	fprintf(file, "Average_time_restitution;");
	fprintf(file, "Average_time_attempt;");
	fprintf(file, "Average_time_respond;");
	fprintf(file, "Average_pourcentage_CPU;");
	fprintf(file, "Algorithm\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){
		
		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		
		fprintf(file, "%d;", (int)simulation_array.simulations[i].average_time_restitution);
		fprintf(file, "%d;", (int)simulation_array.simulations[i].average_time_attempt);
		fprintf(file, "%d;", (int)simulation_array.simulations[i].average_time_respond);
		fprintf(file, "%d;", (int)simulation_array.simulations[i].average_pourcentage_CPU);
		fprintf(file, "%s\n", string);
	}
	
	
	close_file(file);
	return 0;
}

void print_resultat_console_simulation(Simulation_array simulation_array){
	
	printf("******************************************************************\n");
	printf("Affichage des resultats des simulations\n\n");
	
	printf("Average_time_restitution;");
	printf("Average_time_attempt;");
	printf("Average_time_respond;");
	printf("Average_pourcentage_CPU;");
	printf("Algorithm\n\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){
		
		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		
		printf("%d;", (int)simulation_array.simulations[i].average_time_restitution);
		printf("%d;", (int)simulation_array.simulations[i].average_time_attempt);
		printf("%d;", (int)simulation_array.simulations[i].average_time_respond);
		printf("%d;", (int)simulation_array.simulations[i].average_pourcentage_CPU);
		printf("%s\n", string);
	}
	
}

int generate_result_processus(char *path, Simulation_array simulation_array){
	
	FILE *file = open_file(path, "w");
	fprintf(file, "RESULTAT DES PROCESSUS\n\n");
	
	fprintf(file, "Processus;");
	fprintf(file, "Time_to_restue;");
	fprintf(file, "Time_attempt;");
	fprintf(file, "Time_to_respond;");
	fprintf(file, "Algorithm\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){
		
		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		for(int j = 0; j < simulation_array.simulations[i].processus_array.nbProcessus; j++){

			fprintf(file, "%s;", simulation_array.simulations[i].processus_array.processus[j].name);
			fprintf(file, "%d;", simulation_array.simulations[i].processus_array.processus[j].time_to_restue);
			fprintf(file, "%d;", simulation_array.simulations[i].processus_array.processus[j].time_attempt);
			fprintf(file, "%d;", simulation_array.simulations[i].processus_array.processus[j].time_to_answer);
			fprintf(file, "%s\n", string);
		}
		fprintf(file, "\n");
	}
	
	close_file(file);
	return 0;
}

void print_resultat_console_processus(Simulation_array simulation_array){
	
	printf("\n\n\nAffichage des resultats des processus\n\n");
	
	printf("Processus;");
	printf("Time_to_restue;");
	printf("Time_attempt;");
	printf("Time_to_respond;");
	printf("Algorithm\n\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){

		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		for(int j = 0; j < simulation_array.simulations[i].processus_array.nbProcessus; j++){

		
					/*printf("temps restu : %d\n",simulation_array.simulations[i].processus_array.processus[j].time_to_restue);
					printf("temps time_to_answer : %d\n",simulation_array.simulations[i].processus_array.processus[j].time_to_answer);
					printf("temps time_attempt : %d\n",simulation_array.simulations[i].processus_array.processus[j].time_attempt); */
				
			printf("%s;", simulation_array.simulations[i].processus_array.processus[j].name);
			printf("%d;", simulation_array.simulations[i].processus_array.processus[j].time_to_restue);
			printf("%d;", simulation_array.simulations[i].processus_array.processus[j].time_attempt);
			printf("%d;", simulation_array.simulations[i].processus_array.processus[j].time_to_answer);
			printf("%s\n", string);
		}
		printf("\n");
	}
	
	printf("******************************************************************\n");
}
