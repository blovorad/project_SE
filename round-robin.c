#include "round-robin.h"

/**
 * \file round-robin.c
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier source qui implemente l'algorithme d'ordonnancement round-robin
 */


/**
 * \var sa_cpu_liberation
 * \brief structure permettant de gerer les signaux de liberation de la CPU
 */
struct sigaction sa_cpu_liberation;

/**
 * \var sa_cpu_occupation
 * \brief structure permettant de gerer les signaux d'occupation de la CPU
 */
struct sigaction sa_cpu_occupation;

/**
 * \var cpu_busy
 * \brief booleen indiquant si la CPU est occupee par un processus (true) ou non (false)
 */
int cpu_busy = 0;

/**
 * \var total_occupation_cpu_time
 * \brief temps total d'occupation de la CPU au cours de l'execution de l'algorithme
 */
double total_occupation_cpu_time = 0;

/**
 * \var start_occupation_cpu
 * \brief instant marquant le debut de l'occupation de la CPU par un processus
 */
time_t start_occupation_cpu = 0;

/**
 * \var end_occupation_cpu
 * \brief instant marquant la fin de l'occupation de la CPU par un processus
 */
time_t end_occupation_cpu = 0;

/**
 * \var key
 * \brief clef permettant de creer un semaphore avec semalloc
 */
key_t key;

/**
 * \var mutexCPU
 * \brief mutex permettant de s'assurer qu'un seul processus occupe la CPU a chaque instant t
 */
int mutexCPU;

/**
 * \var actions_list
 * \brief liste d'actions (cycles CPU ou entrée/sortie) d'un processus
 */
Action* actions_list;


/**
 * \fn void cpu_occupation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_BUSY pour savoir quand un processus occupe la CPU
 * \return void
 */
void cpu_occupation() {
    cpu_busy = 1;
    start_occupation_cpu = time(NULL);
}

/**
 * \fn void cpu_liberation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_FREE pour savoir quand un processus libere la CPU
 * \return void
 */
void cpu_liberation() {
    cpu_busy = 0;
    end_occupation_cpu = time(NULL);
    total_occupation_cpu_time += difftime(end_occupation_cpu, start_occupation_cpu);
}

/**
 * \fn int round_robin(Simulation *simulation)
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief Simulation effectuee avec l'algorithme Round-Robin (ou tourniquet)
 * \param simulation simulation ayant pour algorithme d'ordonnancement Round-Robin
 * \return 0 en temps normal, -1 en cas d'erreur
 */
int round_robin(Simulation *simulation) {

    //Activation des fonctions de reaction
    sa_cpu_occupation.sa_handler = cpu_occupation;
    sigaction(CPU_BUSY, &sa_cpu_occupation, 0);
    
    sa_cpu_liberation.sa_handler = cpu_liberation;
    sigaction(CPU_FREE, &sa_cpu_liberation, 0);

    //Initialisation des semaphores et variables partagees

    //MutexCPU : permet de n'avoir qu'un seul processus actif sur la CPU
    if ((key=ftok("/etc/passwd", 1))==-1) { 
        perror("ftok failed");
        exit(-1);
    }
    
    mutexCPU = semalloc(key, 1);

    //Recuperation des parametres de l'algorithme et des processus
    int quantum = simulation->quantum;
    Processus* processus = simulation->processus_array.processus;
    int nbProcessus = simulation->processus_array.nbProcessus;
    
    printf("nbProcessus : %d\n", nbProcessus);

    pid_t* processus_pid = (pid_t*) malloc (sizeof(pid_t)*nbProcessus);
    if (processus_pid == NULL) {
        semfree(mutexCPU);
        perror("Malloc failed for processus_pid");
        exit(-1);
    }

    //Indice du processus courant
    int i = 0;

    //Recuperation des temps d'arrivee
    double* arrival_times = (double*) malloc (sizeof(double)*nbProcessus);
    if (arrival_times == NULL) {
        semfree(mutexCPU);
        perror("Malloc failed for arrival_times");
        exit(-1);
    }
    for (i=0; i < nbProcessus; i++) {
        arrival_times[i] = (double) processus[i].arrive_at;
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
                    actions_list = processus[i].action_cycle;

                    while (actions_list != NULL) {
                        if (actions_list->type == CPU) {
                            time_t start_waiting = time(NULL);

                            P(mutexCPU);

                            time_t end_waiting = time(NULL);
                            processus[i].time_attempt += (int) difftime(end_waiting, start_waiting);

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
                        processus[i].time_to_restue = processus[i].time_execution + processus[i].time_attempt;
                        actions_list = delete_head(actions_list);
                    }
                    return 1;

                default:
                    
                    i++;
                    break;
            }
        }
    }

    cpu_occupation(CPU_BUSY);
    cpu_liberation(CPU_FREE);
 
    time_t end_time = time(NULL);

    double algorithm_execution_time = difftime(end_time, start_time);

    i=0;
    double total_time_attempt = 0;
    double total_time_restitution = 0;
    double total_time_respond = 0; //Considere comme negligeable a l'echelle de la simulation
    
    for (i=0; i<nbProcessus; i++) {
        total_time_attempt += processus[i].time_attempt;
        total_time_restitution += processus[i].time_to_restue;
    }

    simulation->average_time_attempt = total_time_attempt/(double) nbProcessus;
    simulation->average_time_restitution = total_time_restitution/(double)nbProcessus;
    simulation->average_time_respond = total_time_respond/(double)nbProcessus;
    simulation->average_pourcentage_CPU = total_occupation_cpu_time/algorithm_execution_time; //Correct ?
    simulation->time_restitution = algorithm_execution_time;

    //Destruction des ressources IPC allouees
    //MutexCPU
    semfree(mutexCPU);
    
    return 0;

}
