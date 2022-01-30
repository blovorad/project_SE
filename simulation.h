#ifndef __SIMULATION__H__
#define __SIMULATION__H__

typedef enum{
	
	FIFO,
	SJF,
	SRJF,
	ROUND_ROBIN
}Algorithm;

typedef struct{

    Algorithm code_algorithm;
    int quantum;
    double average_time_attempt;
    double average_time_restitution;
    double average_time_respond;
    double average_pourcentage_CPU;
}Simulation;

#endif
