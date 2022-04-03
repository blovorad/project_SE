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
        
        if(strcmp(argv[1], "-rt") == 0){
            //test rapide console, nombre processus, nombre de cycle CPU
            if(argc != 4){
                
                printf("Mauvais format de commande, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
                return 1;
            }
            if(get_config_commandLine(argv, simulation_array) == -1){
                
                printf("Erreur lors du chargement de la configuration\n");
                return 2;
            }
            printf("Lancement de la simulation - celle-ci peut prendre quelques minutes...\n");
            launch_an_algorithm(simulation_array);
            printf("Sauvegarde des resultats dans le fichier de sortie par defaut...\n\n");
            generate_result_processus("./fichier_resultat_processus.csv", *simulation_array);
            generate_result_simulation("./fichier_resultat_processus.csv", *simulation_array);
            print_resultat_console_simulation(*simulation_array);
            print_resultat_console_processus(*simulation_array);
        }
        else if(strcmp(argv[1], "-rc") == 0){
            //test renseigne avec un fichier configuration
            if(argc == 3){
                //sortie non specifiee
                if(get_config_file(open_file(argv[2], "r"), simulation_array) == -1){
                    
                    printf("Erreur lors du chargement de la configuration\n");
                    return 2;
                }
                printf("Lancement de la simulation - celle-ci peut prendre quelques minutes...\n");
                launch_an_algorithm(simulation_array);
                printf("Sauvegarde des resultats dans le fichier de sortie par defaut ./fichier_resultat_processus.csv...\n\n");
                generate_result_processus("./fichier_resultat_processus.csv", *simulation_array);
                generate_result_simulation("./fichier_resultat_processus.csv", *simulation_array);
                print_resultat_console_simulation(*simulation_array);
                print_resultat_console_processus(*simulation_array);
            }
            else if(argc == 4){
                //fichier de sortie specifiee
                if(get_config_file(open_file(argv[2], "r"), simulation_array) == -1){
                    
                    printf("Erreur lors du chargement de la configuration\n");
                    return 2;
                }
                printf("Lancement de la simulation - celle-ci peut prendre quelques minutes...\n");
                launch_an_algorithm(simulation_array);
                int path_ok = is_path_ok(argv[3]);
                if(path_ok == 1){
                
                    printf("Ecriture des resultats dans le fichier %s\n", argv[3]); 
                    generate_result_processus(argv[3], *simulation_array);
                    generate_result_simulation(argv[3], *simulation_array);
                }
                else{
                    
                    printf("Format du fichier non reconnu ou chemin incorrect ; ecriture des resultats dans le fichier : ./fichier_resultat_processus.csv\n\n"); 
                    generate_result_processus("./fichier_resultat_processus.csv", *simulation_array);
                    generate_result_simulation("./fichier_resultat_processus.csv", *simulation_array);
                }
                print_resultat_console_simulation(*simulation_array);
                print_resultat_console_processus(*simulation_array);
            }
            else{
                
                printf("Mauvais format de commande, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
                return 1;
            }
        }
        else if(strcmp(argv[1], "-h") == 0){
            
            print_help();
        }
        else{
            
            printf("Commande incorrecte, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
            return 1;
        }
    }
    else{
        
        printf("Commande incorrecte, taper : ./prog -h pour plus d'information ou consulter la documentation\n");
        return 1;
    }
    
    return 0;
}

int launch_an_algorithm(Simulation_array *simulation_array){

    for(int i = 0; i < simulation_array->nbSimulations;i++){
    
        switch(simulation_array->simulations[i].code_algorithm){
            
            case FIFO: 
            	printf("Lancement de FIFO\n");
            	fifo(&simulation_array->simulations[i]);
            	printf("fin de FIFO\n");
                break;
            case SJF: 
            	printf("lancement de SJF\n");
                sjf(&simulation_array->simulations[i]);
                printf("fin de SJF\n");
                /*for(int j = 0; j < simulation_array->simulations[i].processus_array.nbProcessus; j++){
		
					printf("temps restu : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_to_restue);
					printf("temps time_to_answer : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_to_answer);
					printf("temps time_attempt : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_attempt); 
				}*/
                break;
            case ROUND_ROBIN: 
            	printf("Lancement de round robin\n");
                round_robin(&simulation_array->simulations[i]);
                /*for(int j = 0; j < simulation_array->simulations[i].processus_array.nbProcessus; j++){
		
					printf("temps restu : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_to_restue);
					printf("temps time_to_answer : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_to_answer);
					printf("temps time_attempt : %d\n",simulation_array->simulations[i].processus_array.processus[j].time_attempt); 
				}*/
                printf("fin de round robin\n");
                break;
            default:
                break;
        }
    }

    return 0;
}

void print_help(void){
    
    printf("---- Aide du programme ---\n");
    printf(" - si vous lancez sans interface graphique -\n");
    printf(" - Taper ./prog -rt <nombre de processus> <nombre de cycle CPU> pour lancer un test rapide ;\n");
    printf(" - Taper ./prog -rc <chemin vers un fichier de configuration> [chemin du fichier de sortie (optionnel) en .csv] pour lancer un test avec un fichier de configuration.\n");
    printf(" - si vous lancez avec interface graphique -\n");
    printf(" - Taper ./progGui -rt <nombre de processus> <nombre de cycle CPU> pour lancer un test rapide ;\n");
    printf(" - Taper ./progGui -rc <chemin vers un fichier de configuration> [chemin du fichier de sortie (optionnel) en .csv] pour lancer un test avec un fichier de configuration.\n");
    printf("Pour plus d'informations, consulter la documentation du programme.\n");
}
