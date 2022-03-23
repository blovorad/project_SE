#include "round-robin.h"

/**
 * \file round-robin.c
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier source qui implemente l'algorithme d'ordonnancement round-robin
 */

    // Envoi de signaux par les fils au père pour savoir si CPU libre : "je suis dans CPU", sleep(), "je suis sorti", dans le mutexCPU pour mettre à jour booléen et calculer taux d'occupation de la CPU (gestion du calcul du temps dans le père - vérifier si le booléen a changé entre temps dans le père)
struct sigaction sa_cpu_free;
struct sigaction sa_cpu_occupy;
int cpu_busy = 0;
int previous_state_cpu = cpu_busy;
double total_occupation_cpu_time = 0;
time_t start_occupation_cpu = 0;
time_t end_occupation_cpu = 0;


/**
 * \fn void cpu_occupation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_BUSY pour savoir quand un processus occupe la CPU
 * \param int signal auquel doit reagir la fonction
 * \return void
 */
void cpu_occupation(int signal) {
    //un processus déclare occuper la CPU : il envoie le signal d'occupation au processus père qui déclare la cpu occupée et lance le chrono pour mesurer le temps do'cuppation (et pour ensuite calculer le pourcentage d'occupation)
    cpu_busy = 1;
    start_occupation_cpu = time(NULL);
}

/**
 * \fn void cpu_liberation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_FREE pour savoir quand un processus libere la CPU
 * \param int signal auquel doit reagir la fonction
 * \return void
 */
void cpu_liberation(int signal) {
    cpu_busy = 0;
    end_occupation_cpu = time(NULL);
    total_occupation_cpu_time += difftime(end_occupation_cpu, start_occupation_cpu);
}

/**
 * \fn int round_robin(Simulation *simulation)
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief Simulation effectuee avec l'algorithme Round-Robin (ou tourniquet)
 * \param Simulation simulation ayant pour algorithme d'ordonnancement Round-Robin
 * \return 0 en temps normal, -1 en cas d'erreur
 */
int round_robin(Simulation *simulation) {

    //Activation des fonctions de reaction
    sa_cpu_occupy.sa_handler = cpu_occupation;
    sigaction(CPU_BUSY, &sa_cpu_occupy, 0);
    
    sa_cpu_free.sa_handler = cpu_liberation;
    sigaction(CPU_FREE, &sa_cpu_liberation, 0);

    //Initialisation des semaphores et variables partagees

    //MutexCPU : permet de n'avoir qu'un seul processus actif sur la CPU
    if ((key=ftokey("/etc/passwd", 1))==-1) { 
        perror("ftok failed");
        exit(-1);
    }
    
    mutexCPU = semalloc(key, 1);

    //Recuperation des parametres de l'algorithme et des processus
    int quantum = simulation->quantum;
    Processus* processus = simulation->processus_array->processus;
    int nbProcessus = simulation->processus_array->nbProcessus;
    pid_t processus_pid[nbProcessus];

    //Indice du processus courant
    int i = 0;

    //Recuperation des temps d'arrivee
    double arrival_times[nbProcessus] = {0};
    for (i=0; i<n; i++) {
        arrival_times[i] = (double) processus[i]->arrive_at;
    }
    i=0;

    //Recuperation du temps de reference
    time_t start_time = time(NULL);

    //Hypothese : processus classes par temps d'arrivee croissant
    while (i < nbProcessus) {

        if (difftime(time(NULL), start_time)==arrival_times[i]) {
            switch(processus_pid[i] = fork()) {
                case -1:
                    perror("Impossible to initiate child processus and simulate algorithm");
                    return -1;

                case 0:
                    Processus current_processus = processus[i];
                    Action* actions_list = current_processus->action_cycle;

                    while (actions_list != NULL) {
                        if (actions_list->type == CPU) {
                            time_t start_waiting = time(NULL);
                            current_processus->time_pause = (int) start_waiting; //Correct ?

                            P(mutexCPU);

                            time_t end_waiting = time(NULL);
                            current_processus->time_attempt += (int) difftime(end_waiting, start_waiting);

                            kill(getppid(), CPU_BUSY);
                            if (actions_list->time_execution < quantum) {
                                sleep(actions_list->time_execution);
                            }
                            else {
                                sleep(quantum);
                            }
                            kill(getppid(), CPU_FREE);

                            V(mutexCPU);

                        }
                        else if (actions_list->type == ES) {
                            sleep(actions_list->time_execution);
                        }
                        current_processus->time_to_restue = current_processus->time_execution + current_processus->time_attempt;
                        actions_list = delete_head(actions_list);
                    }
                    return 0;

                default:
                    i++;
                    break;
            }
        }
    }

    
    time_t end_time = time(NULL);

    double algorithm_execution_time = difftime(end_time, start_time);

    i=0;
    double total_time_attempt = 0;
    double total_time_restitution = 0;
    double total_time_respond = 0; // Comment l'évaluer ?
    
    for (i=0; i<nbProcessus; i++) {
        total_time_attempt += processus[i]->time_attempt;
        total_time_restitution += processus[i]->time_to_restue;
    }

    simulation->average_time_attempt = total_time_attempt/nbProcessus;
    simulation->average_time_restitution = total_time_restitution/nbProcessus;
    simulation->average_time_respond = total_time_respond/nbProcessus;
    simulation->average_pourcentage_CPU = total_occupation_cpu_time/algorithm_execution_time; //Correct ?

    //Destruction des ressources IPC allouees
    //MutexCPU
    semfree(mutexCPU);
    
    return 0;

}
