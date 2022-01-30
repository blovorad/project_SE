#ifndef __CONFIG__H__
#define __CONFIG__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulation.h"
#include "processus.h"

int get_algorithm_code(FILE *file);
int get_config(FILE *file, Simulation *simulation, Processus_array *array_processus);
int fill_processus_array(FILE *file, Processus_array *array_processus);
int select_algorithm(char *code);

FILE *open_fileConfig(char *path, char *mode);
void close_fileConfig(FILE *file);

#endif