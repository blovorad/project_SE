#ifndef __ROUNDROBIN__H__
#define __ROUNDROBIN__H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#include "simulation.h"
#include "util.h"
#include "resultat.h"
#include "config.h"
#include "ipcTools.h"

/**
 * \file round-robin.h
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief fichier entete associe a l'algorithme d'ordonnancement round-robin
 */

/*! \def CPU_BUSY
    \brief Un signal qu'un processus fils envoie pour dire qu'il occcupe la CPU.
*/ 
#define CPU_BUSY 51

/*! \def CPU_FREE
    \brief Un signal qu'un processus fils envoie pour dire qu'il libere la CPU.
*/
#define CPU_FREE 52

/**
 * \fn void cpu_occupation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_BUSY pour savoir quand un processus occupe la CPU
 * \return void
 */
void cpu_occupation(); 

/**
 * \fn void cpu_liberation(int signal)
 * \author Ouliana Anikienko
 * \date 23/03/2022
 * \brief Fonction de reaction au signal CPU_FREE pour savoir quand un processus libere la CPU
 * \return void
 */
void cpu_liberation();

/**
 * \fn int round_robin(Simulation *simulation)
 * \author Ouliana Anikienko
 * \date 03/03/2022
 * \brief Simulation effectuee avec l'algorithme Round-Robin (ou tourniquet)
 * \param simulation simulation ayant pour algorithme d'ordonnancement Round-Robin
 * \return 0 en temps normal, -1 en cas d'erreur
 */
int round_robin(Simulation *simulation);

#endif