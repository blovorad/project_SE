#include "starter.h"
#include "simulation.h"

int main(int argc, char *argv[]){

	Simulation_array simulation_array;
	if(start_simulations(argc, argv, &simulation_array) != 0){

		return 1;
	}

	return 0;
}