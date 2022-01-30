#include "config.h"

int main(int argc, char *argv[]){

    if(argc > 1){

        Simulation simulation;
        Processus_array array_processus;
        printf("erreur : %d", get_config(open_fileConfig(argv[1], "r"), &simulation, &array_processus));

        free(array_processus.processus);
        array_processus.processus = NULL;
    }
    
    return 0;
}