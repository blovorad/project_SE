#include "config.h"

int main(int argc, char *argv[]){

    if(argc > 1){

        Simulation simulation;
        Processus_array array_processus;
        printf("erreur : %d\n", get_config(open_fileConfig(argv[1], "r"), &simulation, &array_processus));

        free(array_processus.processus);
        array_processus.processus = NULL;
    }
    else {
        printf("argument manquant - se referer a la documentation\n");
    }
    
    return 0;
}
