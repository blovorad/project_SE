#include "resultat.h"

/**
 * \file resultat.c
 * \author Gautier Levesque
 * \date 16/02/2022
 * \brief fichier source qui s'occupe la generation des resultats des simulations
 */

int generate_result_processus(char *path, Simulation_array simulation_array){
	
	FILE *file = fopen(path, "w");
	if(file == NULL){
		
		perror("fopen failed");
		return 1;
	}
	
	fprintf(file, "Processus,");
	fprintf(file, "Time_to_restue,");
	fprintf(file, "Time_attempt,");
	fprintf(file, "Time_to_answer,");
	fprintf(file, "Algorithm\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){
		
		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		for(int j = 0; j < simulation_array.simulations[i].processus_array.nbProcessus; j++){

			fprintf(file, "%s,", simulation_array.simulations[i].processus_array.processus[j].name);
			fprintf(file, "%d,", simulation_array.simulations[i].processus_array.processus[j].time_to_restue);
			fprintf(file, "%d,", simulation_array.simulations[i].processus_array.processus[j].time_attempt);
			fprintf(file, "%d,", simulation_array.simulations[i].processus_array.processus[j].time_to_answer);
			fprintf(file, "%s\n", string);
		}
		fprintf(file, "\n");
	}
	
	fclose(file);
	return 0;
}

void print_resultat_console_processus(Simulation_array simulation_array){
	
	printf("******************************************************************\n");
	printf("******************************************************************\n");
	printf("Affichage des resultats des simulations commencer\n\n\n");
	
	printf("Processus,");
	printf("Time_to_restue,");
	printf("Time_attempt,");
	printf("Time_to_answer,");
	printf("Algorithm\n\n");
	
	for(int i = 0; i < simulation_array.nbSimulations; i++){

		char *string = get_string_from_algorithm(simulation_array.simulations[i].code_algorithm);
		for(int j = 0; j < simulation_array.simulations[i].processus_array.nbProcessus; j++){
		
			printf("%s,", simulation_array.simulations[i].processus_array.processus[j].name);
			printf("%d,", simulation_array.simulations[i].processus_array.processus[j].time_to_restue);
			printf("%d,", simulation_array.simulations[i].processus_array.processus[j].time_attempt);
			printf("%d,", simulation_array.simulations[i].processus_array.processus[j].time_to_answer);
			printf("%s\n", string);
		}
		printf("\n");
	}
	
	printf("\n\nAffichage des resultats terminer\n");
	printf("******************************************************************\n");
	printf("******************************************************************\n");
}
