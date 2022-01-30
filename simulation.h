#ifndef __SIMULATION__H__
#define __SIMULATION__H__

#define FIFO 0
#define SJF 1
#define SRJF 2
#define ROUND_ROBIN 3
typedef struct{

    int code_algorithm;
    int quantum;
}Simulation;

#endif