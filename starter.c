#include "starter.h"

/**
 * \file starter.c
 * \author Gautier Levesque
 * \date 02/03/2022
 * \brief fichier source qui gere le lancement de la simulation
 */

int start_simulations(int argc, char *argv[], Simulation_array *simulation_array){
    
    if(argc > 1){
        
        srand(time(NULL));
        Simulation_array simulation_array;
        
        if(strcmp(argv[1], "-rt") == 0){
            //test rapide console, nombre processus, nombre de cycle CPU
            if(argc != 4){
                
                printf("Format commande mauvaise, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
                return 1;
            }
            if(get_config_commandLine(argv, &simulation_array) == -1){
                
                printf("Erreur chargement configuration\n");
                return 2;
            }
            start_simulation(&simulation_array);
            generate_result_processus("./fichier_resultat_processus.csv", simulation_array);
            generate_result_simulation("./fichier_resultat_processus.csv", &simulation_array);
            print_resultat_console_simulation(simulation_array);
            print_resultat_console_processus(simulation_array);
        }
        else if(strcmp(argv[1], "-rc") == 0){
            //test renseigner avec un fichier configuration
            if(argc == 3){
                //sortis non specifier
                if(get_config_file(open_file(argv[2], "r"), &simulation_array) == -1){
                    
                    printf("Erreur chargement configuration\n");
                    return 2;
                }
                start_simulation(&simulation_array);
                generate_result_processus("./fichier_resultat_processus.csv", simulation_array);
                generate_result_simulation("./fichier_resultat_processus.csv", &simulation_array);
                print_resultat_console_simulation(simulation_array);
                print_resultat_console_processus(simulation_array);
            }
            else if(argc == 4){
                //fichier de sortis specifier
                if(get_config_file(open_file(argv[2], "r"), &simulation_array) == -1){
                    
                    printf("Erreur chargement configuration\n");
                    return 2;
                }
                int path_ok = is_path_ok(argv[3]);
                if(path_ok == 1){
                
                    generate_result_processus(argv[3], simulation_array);
                    generate_result_simulation(argv[3], &simulation_array);
                }
                else{
                    
                    printf("format du fichier non reconnus ou chemin mauvais ecriture des resultats dans le fichier :./fichier_resultat_processus.csv\n"); 
                    generate_result_processus("./fichier_resultat_processus.csv", simulation_array);
                    generate_result_simulation("./fichier_resultat_processus.csv", &simulation_array);
                }
                start_simulation(&simulation_array);
                print_resultat_console_simulation(simulation_array);
                print_resultat_console_processus(simulation_array);
            }
            else{
                
                printf("Format commande mauvaise, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
                return 1;
            }
        }
        else if(strcmp(argv[1], "-h") == 0){
            
            print_help();
        }
        else{
            
            printf("Mauvaise commande, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
            return 1;
        }
    }
    else{
        
        printf("Mauvaise commande, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
        return 1;
    }
    
    return 0;
}

int launch_an_algoritm(Simulation_array *simulation_array){

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

void print_help(void){
    
    printf("Aide du programme\n");
    printf("taper ./prog -rt <nombre de processus> <nombre de cycle CPU> pour lancer un test rapide\n");
    printf("taper ./prog -rc <chemin vers un fichier de configuration> <chemin de sortis(optionnel) en .csv> pour lancer un test avec un fichier de configuration\n");
    printf("Pour plus d'aide consulter la documentation du programme\n");
}