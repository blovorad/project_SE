#include "simulation.h"

/**
 * \file simulation.c
 * \author Gautier Levesque
 * \date 27/02/2022
 * \brief fichier source qui gere la simulation
 */
 
int start_simulation(Simulation_array *simulation_array){
 	
 	for(int i = 0; i < simulation_array->nbSimulations;i++){
 	
 		switch(simulation_array->simulations[i].code_algorithm){
 			
 			case FIFO:
 				break;
 			case SJF:
 				break;
 			case SRJF:
 				break;
 			case ROUND_ROBIN:
 				break;
 			default:
 				break;
 		}
 	}
 	
 	return 0;
}
